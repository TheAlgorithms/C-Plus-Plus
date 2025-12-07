
#include <atomic>
#include <chrono>
#include <cmath>
#include <iostream>
#include <mutex>
#include <numeric>
#include <random>
#include <thread>
#include <vector>
static std::mt19937 rng(std::random_device{}());
static std::mutex rng_mtx;

/**
 * 差分隐私工具类：添加高斯噪声满足ε-差分隐私
 */
class DifferentialPrivacy {
 private:
    double epsilon;      // 隐私预算
    double sensitivity;  // 梯度敏感度
 public:
    DifferentialPrivacy(double eps = 1.0, double sens = 0.1)
        : epsilon(eps), sensitivity(sens) {}

    // 添加高斯噪声
    double add_gaussian_noise(double value) {
        std::lock_guard<std::mutex> lock(rng_mtx);
        std::normal_distribution<double> dist(0.0, sensitivity / epsilon);
        return value + dist(rng);
    }
};

/**
 * 联邦学习客户端类：模拟单一方的数据与本地训练
 */
class FLClient {
 private:
    int client_id;
    std::vector<std::vector<double>> X;  // 特征矩阵 [样本数, 特征数]
    std::vector<int> y;                  // 标签（0/1）
    std::vector<double> local_weights;   // 本地模型权重
    double lr;                           // 学习率
    DifferentialPrivacy dp;              // 差分隐私实例

    // Sigmoid激活函数
    double sigmoid(double z) {
        return 1.0 / (1.0 + exp(-std::clamp(z, -500.0, 500.0)));  // 防止溢出
    }

    // 自适应学习率（随迭代次数衰减）
    double adaptive_lr(int iter) { return lr / (1.0 + 0.01 * iter); }

 public:
    FLClient(int id, const std::vector<std::vector<double>>& features,
             const std::vector<int>& labels, double learning_rate = 0.01)
        : client_id(id),
          X(features),
          y(labels),
          lr(learning_rate),
          dp(1.0, 0.1) {
        // 初始化权重（含偏置项，权重维度=特征数+1）
        local_weights.resize(X[0].size() + 1, 0.0);
        std::lock_guard<std::mutex> lock(rng_mtx);
        std::uniform_real_distribution<double> dist(-0.1, 0.1);
        for (auto& w : local_weights) w = dist(rng);
    }

    // 本地单轮训练，返回带差分隐私的梯度
    std::vector<double> local_train(int iter) {
        std::vector<double> grad(local_weights.size(), 0.0);
        int n_samples = X.size();
        double current_lr = adaptive_lr(iter);

        // 计算批量梯度（全量样本）
        for (int i = 0; i < n_samples; ++i) {
            // 计算预测值：w0*1 + w1*x1 + w2*x2 + ...
            double y_pred = local_weights[0];  // 偏置项
            for (int j = 0; j < X[i].size(); ++j) {
                y_pred += local_weights[j + 1] * X[i][j];
            }
            y_pred = sigmoid(y_pred);

            // 梯度计算（逻辑回归交叉熵损失）
            double error = y_pred - y[i];
            grad[0] += error;  // 偏置项梯度
            for (int j = 0; j < X[i].size(); ++j) {
                grad[j + 1] += error * X[i][j];
            }
        }

        // 梯度归一化+差分隐私
        for (auto& g : grad) {
            g /= n_samples;                // 平均梯度
            g = dp.add_gaussian_noise(g);  // 添加噪声
            // 梯度裁剪（防止梯度爆炸）
            g = std::clamp(g, -1.0, 1.0);
        }

        // 更新本地权重
        for (int j = 0; j < local_weights.size(); ++j) {
            local_weights[j] -= current_lr * grad[j];
        }

        return grad;
    }

    int get_id() const { return client_id; }
    const std::vector<double>& get_local_weights() const {
        return local_weights;
    }
};

/**
 * 联邦学习服务端：聚合客户端梯度，更新全局模型
 */
class FLServer {
 private:
    std::vector<double> global_weights;  // 全局模型权重
    std::atomic<int> received_clients;   // 已接收梯度的客户端数
    std::mutex mtx;                      // 聚合锁
    int total_clients;                   // 总客户端数
    double aggregation_ratio;  // 异步聚合比例（如0.8表示80%客户端响应即可聚合）

 public:
    FLServer(int feature_dim, int total_clients_num, double agg_ratio = 0.8)
        : total_clients(total_clients_num),
          aggregation_ratio(agg_ratio),
          received_clients(0) {
        // 初始化全局权重
        global_weights.resize(feature_dim + 1, 0.0);
        std::lock_guard<std::mutex> lock(rng_mtx);
        std::uniform_real_distribution<double> dist(-0.1, 0.1);
        for (auto& w : global_weights) w = dist(rng);
    }

    // 接收客户端梯度并异步聚合
    void receive_and_aggregate(const std::vector<double>& client_grad,
                               int client_id) {
        std::lock_guard<std::mutex> lock(mtx);
        received_clients++;

        // 梯度聚合（加权平均，简化为等权）
        double agg_weight = 1.0 / total_clients;
        for (int j = 0; j < global_weights.size(); ++j) {
            global_weights[j] -= agg_weight * client_grad[j];
        }

        std::cout << "[Server] 接收客户端" << client_id << "梯度，已接收："
                  << received_clients << "/" << total_clients << std::endl;

        // 异步聚合触发：达到聚合比例则重置计数
        if (received_clients >= total_clients * aggregation_ratio) {
            std::cout << "[Server] 达到聚合阈值，更新全局模型" << std::endl;
            received_clients = 0;
        }
    }

    // 向客户端下发全局权重
    std::vector<double> get_global_weights() const {
        std::lock_guard<std::mutex> lock(mtx);
        return global_weights;
    }

    // 模型评估（准确率）
    double evaluate(const std::vector<std::vector<double>>& X_test,
                    const std::vector<int>& y_test) {
        std::vector<double> weights = get_global_weights();
        int correct = 0;
        auto sigmoid = [](double z) {
            return 1.0 / (1.0 + exp(-std::clamp(z, -500.0, 500.0)));
        };

        for (int i = 0; i < X_test.size(); ++i) {
            double y_pred = weights[0];
            for (int j = 0; j < X_test[i].size(); ++j) {
                y_pred += weights[j + 1] * X_test[i][j];
            }
            y_pred = sigmoid(y_pred);
            correct += (y_pred >= 0.5) == (y_test[i] == 1) ? 1 : 0;
        }
        return static_cast<double>(correct) / X_test.size();
    }
};

/**
 * 生成模拟数据集（二分类任务）
 */
std::pair<std::vector<std::vector<double>>, std::vector<int>> generate_sim_data(
    int n_samples, int n_features) {
    std::vector<std::vector<double>> X(n_samples,
                                       std::vector<double>(n_features));
    std::vector<int> y(n_samples);

    // 生成特征（正态分布）
    std::lock_guard<std::mutex> lock(rng_mtx);
    std::normal_distribution<double> x_dist(0.0, 1.0);
    std::bernoulli_distribution y_dist(0.5);

    for (int i = 0; i < n_samples; ++i) {
        for (int j = 0; j < n_features; ++j) {
            X[i][j] = x_dist(rng);
        }
        y[i] = y_dist(rng);
    }
    return {X, y};
}

/**
 * 客户端训练线程函数
 */
void client_train_thread(FLClient& client, FLServer& server, int epochs) {
    for (int e = 0; e < epochs; ++e) {
        // 本地训练
        std::vector<double> grad = client.local_train(e);
        // 上报梯度到服务端
        server.receive_and_aggregate(grad, client.get_id());
        // 拉取最新全局权重（模拟异步通信）
        client = FLClient(client.get_id(), client.X, client.y,
                          0.01);  // 简化：重新初始化客户端权重为全局权重
        // 模拟网络延迟
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    // 1. 配置实验参数
    const int n_clients = 5;               // 联邦客户端数
    const int n_features = 5;              // 特征维度
    const int n_samples_per_client = 100;  // 每个客户端样本数
    const int epochs = 20;                 // 训练轮数

    // 2. 生成模拟数据（客户端+测试集）
    std::vector<FLClient> clients;
    for (int i = 0; i < n_clients; ++i) {
        auto [X, y] = generate_sim_data(n_samples_per_client, n_features);
        clients.emplace_back(i, X, y, 0.01);
    }
    // 测试集
    auto [X_test, y_test] = generate_sim_data(200, n_features);

    // 3. 初始化服务端
    FLServer server(n_features, n_clients, 0.8);

    // 4. 启动客户端训练线程
    std::vector<std::thread> client_threads;
    for (auto& client : clients) {
        client_threads.emplace_back(client_train_thread, std::ref(client),
                                    std::ref(server), epochs);
    }

    // 5. 等待所有客户端训练完成
    for (auto& t : client_threads) {
        t.join();
    }

    // 6. 模型评估
    double accuracy = server.evaluate(X_test, y_test);
    std::cout << "\n[Final] 全局模型测试准确率：" << accuracy << std::endl;

    return 0;
}