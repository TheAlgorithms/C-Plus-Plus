/**
 * @file
 * @brief Ground to ground [projectile
 * motion](https://en.wikipedia.org/wiki/Projectile_motion) equation
 * implementations
 * @details Ground to ground projectile motion is when a projectile's trajectory
 * starts at the ground, reaches the apex, then falls back on the ground.
 *
 * @author [Focusucof](https://github.com/Focusucof)
 */

#include <cassert>   /// for assert()
#include <cmath>     /// for std::pow(), std::sin(), and std::cos()
#include <iostream>  /// for IO operations

/**
 * @namespace physics
 * @brief Physics algorithms
 */
namespace physics {
/**
 * @namespace ground_to_ground_projectile_motion
 * @brief Functions for the Ground to ground [projectile
 * motion](https://en.wikipedia.org/wiki/Projectile_motion) equation
 */
namespace ground_to_ground_projectile_motion {
/**
 * @brief Convert radians to degrees
 * @param radian Angle in radians
 * @param PI The definition of the constant PI
 * @returns Angle in degrees
 */
double degrees_to_radians(double radian, double PI = 3.14) {
    return (radian * (PI / 180));
}

/**
 * @brief Calculate the time of flight
 * @param initial_velocity The starting velocity of the projectile
 * @param angle The angle that the projectile is launched at in degrees
 * @param gravity The value used for the gravity constant
 * @returns The time that the projectile is in the air for
 */
template <typename T>
T time_of_flight(T initial_velocity, T angle, double gravity = 9.81) {
    double Viy = initial_velocity *
                 (std::sin(degrees_to_radians(
                     angle)));  // calculate y component of the initial velocity
    return 2.0 * Viy / gravity;
}

/**
 * @brief Calculate the horizontal distance that the projectile travels
 * @param initial_velocity The starting velocity of the projectile
 * @param time The time that the projectile is in the air
 * @returns Horizontal distance that the projectile travels
 */
template <typename T>
T horizontal_range(T initial_velocity, T angle, T time) {
    double Vix = initial_velocity *
                 (std::cos(degrees_to_radians(
                     angle)));  // calculate x component of the initial velocity
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
T max_height(T initial_velocity, T angle, double gravity = 9.81) {
    double Viy = initial_velocity *
                 (std::sin(degrees_to_radians(
                     angle)));  // calculate y component of the initial velocity
    return (std::pow(Viy, 2) / (2.0 * gravity));
}
}  // namespace ground_to_ground_projectile_motion
}  // namespace physics

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // initial input variables
    double initial_velocity = 5.0;  // double initial_velocity input
    double angle = 40.0;            // double angle input

    // 1st test
    double expected_time_of_flight = 0.655;  // expected time output
    double flight_time_output =
        std::round(physics::ground_to_ground_projectile_motion::time_of_flight(
                       initial_velocity, angle) *
                   1000.0) /
        1000.0;  // round output to 3 decimal places

    std::cout << "Projectile Flight Time (double)" << std::endl;
    std::cout << "Input Initial Velocity: " << initial_velocity << std::endl;
    std::cout << "Input Angle: " << angle << std::endl;
    std::cout << "Expected Output: " << expected_time_of_flight << std::endl;
    std::cout << "Output: " << flight_time_output << std::endl;
    assert(flight_time_output == expected_time_of_flight);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 2nd test
    double expected_horizontal_range = 2.51;  // expected range output
    double horizontal_range_output =
        std::round(
            physics::ground_to_ground_projectile_motion::horizontal_range(
                initial_velocity, angle,
                flight_time_output) *
            100.0) /
        100.0;  // round output to 2 decimal places

    std::cout << "Projectile Horizontal Range (double)" << std::endl;
    std::cout << "Input Initial Velocity: " << initial_velocity << std::endl;
    std::cout << "Input Angle: " << angle << std::endl;
    std::cout << "Input Time Of Flight: " << flight_time_output << std::endl;
    std::cout << "Expected Output: " << expected_horizontal_range << std::endl;
    std::cout << "Output: " << horizontal_range_output << std::endl;
    assert(horizontal_range_output == expected_horizontal_range);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 3rd test
    double expected_max_height = 0.526;  // expected height output
    double max_height_output =
        std::round(physics::ground_to_ground_projectile_motion::max_height(
                       initial_velocity, angle) *
                   1000.0) /
        1000.0;  // round output to 3 decimal places

    std::cout << "Projectile Max Height (double)" << std::endl;
    std::cout << "Input Initial Velocity: " << initial_velocity << std::endl;
    std::cout << "Input Angle: " << angle << std::endl;
    std::cout << "Expected Output: " << expected_max_height << std::endl;
    std::cout << "Output: " << max_height_output << std::endl;
    assert(max_height_output == expected_max_height);
    std::cout << "TEST PASSED" << std::endl << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
