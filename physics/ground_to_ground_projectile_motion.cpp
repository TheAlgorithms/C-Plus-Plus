/**
* @file
* @brief Ground to ground [projectile motion](https://en.wikipedia.org/wiki/Projectile_motion) equation implementations
* @details Ground to ground projectile motion is when a projectile's trajectory starts at the ground, reaches the apex, then falls back on the ground.
* 
* @author [Focusucof](https://github.com/Focusucof)
*/

#include <cassert>  /// for assert()
#include <cmath>    /// for std::pow(), std::sin(), and std::cos()
#include <iostream> /// for IO operations

/**
* @namespace Physics
* @brief Physics algorithms
*/
namespace physics {

/**
* @brief Convert radians to degrees
* @param radian Angle in radians
* @param PI The definition of the constant PI
* @returns Angle in degrees
*/
float radians_to_degrees(float radian, float PI = 3.14) {
    return (radian * (180 / PI));
}

/**
* @brief Calculate the time of flight
* @param initial_velocity The starting velocity of the projectile
* @param angle The angle that the projectile is launched at in degrees
* @param gravity The value used for the gravity constant
* @returns The time that the projectile is in the air for
*/
template <typename T>
T time_of_flight(T initial_velocity, T angle, float gravity = 9.81) {
    float Viy = initial_velocity * (radians_to_degrees(std::sin(angle));
    return 2.0 * Viy / gravity;
}
	
/**
 * @brief Calculate the horizontal distance that the projectile travels
 * @param initial_velocity The starting velocity of the projectile
 * @param time The time that the projectile is in the air
 * @returns Horizontal distance that the projectile travels
 */
template <typename T>
T horizontal_range(T initial_velocity, T time) {
    float Vix = initial_velocity * (radians_to_degrees(std::cos(angle));
    return Vix * time;
}

/**
* @brief Calculate the max height of the projectile
* @param initial_velocity The starting velocity of the projectile
* @param angle The angle that the projectile is launched at in degrees
* @param gravity The value used for the gravity constant
* @returns The max height that the projectile reaches
*/
template <typename T>
T max_height(T initial_velocity, T angle, float gravity = 9.81) {
    float Viy = initial_velocity * (radians_to_degrees(std::sin(angle));
    return (std::pow(Viy, 2)/(2.0 * gravity);
}
} // namespace physics

/**
* @brief Self-test implementations
* @returns void
*/
static void test() { 
    std::cout << physics::time_of_flight(5.0, 40); 
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test(); // run self-test implementations
    return 0;
}