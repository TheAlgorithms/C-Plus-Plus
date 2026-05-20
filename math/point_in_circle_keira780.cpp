#include <iostream>
#include <cmath>

/**
 * @brief 判断一个点 (x, y) 是否在以 (cx, cy) 为圆心、r 为半径的圆内
 * @param x 点的横坐标
 * @param y 点的纵坐标
 * @param cx 圆心横坐标
 * @param cy 圆心纵坐标
 * @param r 圆的半径
 * @return true 如果在圆内或圆上, false 如果在圆外
 */
bool isPointInCircle(double x, double y, double cx, double cy, double r) {
    // 计算点到圆心的欧几里得距离的平方，避免开方运算提高效率
    double distanceSquared = std::pow(x - cx, 2) + std::pow(y - cy, 2);
    double radiusSquared = std::pow(r, 2);
    
    return distanceSquared <= radiusSquared;
}

int main() {
    double cx, cy, r, x, y;
    std::cout << "--- 圆形位置关系判定工具 ---" << std::endl;
    std::cout << "请输入圆心坐标 (cx cy) 和半径 r: ";
    if (!(std::cin >> cx >> cy >> r)) return 0;
    
    std::cout << "请输入待检测点的坐标 (x y): ";
    if (!(std::cin >> x >> y)) return 0;

    if (isPointInCircle(x, y, cx, cy, r)) {
        std::cout << "结果：点 (" << x << ", " << y << ") 在圆内或圆周上。" << std::endl;
    } else {
        std::cout << "结果：点 (" << x << ", " << y << ") 在圆外。" << std::endl;
    }

    return 0;
}
