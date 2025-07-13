/**
 * @file
 * @brief Warshall 算法实现：用于计算有向图的传递闭包
 *
 * Warshall 算法是一种经典的图算法，用于判断图中任意两个点之间是否存在路径。
 * 它通过邻接矩阵进行布尔运算，最终生成一个表示可达关系的传递闭包矩阵。
 *
 * 时间复杂度为 O(V^3)，其中 V 是图中的顶点数。
 */

 #include <iostream>
 #include <vector>
 #include <cassert>
 
 /**
  * @brief 使用 Warshall 算法计算图的传递闭包
  * 
  * @param graph 输入图的邻接矩阵（0/1表示）
  * @return 返回一个传递闭包矩阵，表示任意两个点是否可达
  */
 std::vector<std::vector<int>> warshall(const std::vector<std::vector<int>>& graph) {
     int V = graph.size();  // 顶点个数
     std::vector<std::vector<int>> reach = graph;  // 创建一个副本用于处理
 
     // 三层循环：以每个节点 k 为中介，更新所有 i → j 的可达性
     for (int k = 0; k < V; ++k) {
         for (int i = 0; i < V; ++i) {
             for (int j = 0; j < V; ++j) {
                 // 如果 i 能到 k，且 k 能到 j，那么 i 也能到 j
                 reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
             }
         }
     }
 
     return reach;
 }
 
 /**
  * @brief 输出二维矩阵的函数（用于显示邻接矩阵或传递闭包）
  * 
  * @param matrix 要输出的矩阵
  */
 void print_matrix(const std::vector<std::vector<int>>& matrix) {
     for (const auto& row : matrix) {
         for (auto val : row) {
             std::cout << val << " ";
         }
         std::cout << "\n";
     }
 }
 
 /**
  * @brief 主函数：提供一个测试图，并验证算法结果
  */
 int main() {
     // 示例图（4 个点）：构成一个环形路径 0→1→2→3→0
     std::vector<std::vector<int>> graph = {
         {0, 1, 0, 0},
         {0, 0, 1, 0},
         {0, 0, 0, 1},
         {1, 0, 0, 0}
     };
 
     // 预期结果：任意一点都能到任意其他点，闭包矩阵应全为 1
     std::vector<std::vector<int>> expected = {
         {1, 1, 1, 1},
         {1, 1, 1, 1},
         {1, 1, 1, 1},
         {1, 1, 1, 1}
     };
 
     // 调用算法函数，计算传递闭包
     auto result = warshall(graph);
 
     // 输出结果矩阵
     std::cout << "传递闭包矩阵如下：\n";
     print_matrix(result);
 
     // 简单验证算法正确性（使用断言）
     assert(result == expected);
     std::cout << "测试通过！\n";
 
     return 0;
 }
 