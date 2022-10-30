/**
 * @file
 * @brief [Newton's Second Law](https://en.wikipedia.org/wiki/Newton%27s_laws_of_motion) implementation
 * @details Newton's second law states that the force of an object is equal to its mass x its acceleration (F=Ma)
 * 
 * @author [Focusucof](https://github.com/Focusucof)
 */

#include <cassert>  /// for assert
#include <iostream> /// for IO operations

/**
 * @namespace physics
 * @brief Physics algorithms
 */
namespace physics {
/**
 * @namespace newtons_second_law
 * @brief Functions for the [Newton's Second Law](https://en.wikipedia.org/wiki/Newton%27s_laws_of_motion) equation
 */
namespace newtons_second_law {
/**
 * @brief The calculation for [Newton's Second Law](https://en.wikipedia.org/wiki/Newton%27s_laws_of_motion) F=Ma equation
 * @param mass The mass of the object in kg
 * @param acceleration The acceleration of the object in m/s^2
 * @returns The force of the object in Newtons
 */
template <typename T>
T newtons_second_law_of_motion(T mass, T acceleration) {
    return mass * acceleration; // return F=Ma
}

} // namespace newtons_second_law
} // namespace physics

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st test

    // initial input variables
    float float_mass = 68.0; // float mass input
    float float_acceleration = 3.5; // float acceleration input

    float float_expected_force = 238.0; // expected float output
    float float_force_output = physics::newtons_second_law::newtons_second_law_of_motion(float_mass, float_acceleration); // force output

    std::cout << "Force of object (float)" << std::endl;
    std::cout << "Input mass (kg): " << float_mass << std::endl;
    std::cout << "Input acceleration (m/s^2): " << float_acceleration << std::endl;
    std::cout << "Expected Output: " << float_expected_force << std::endl;
    std::cout << "Output: " << float_force_output << std::endl;
    assert(float_force_output == float_expected_force);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 2nd test

    //initial input variables
    int int_mass = 14; // int mass input
    int int_acceleration = 4; // int acceleration input

    int int_expected_force = 56; // expected int output
    int int_force_output = physics::newtons_second_law::newtons_second_law_of_motion(int_mass, int_acceleration); // force output

    std::cout << "Force of object (int)" << std::endl;
    std::cout << "Input mass (kg): " << int_mass << std::endl;
    std::cout << "Input acceleration (m/s^2): " << int_acceleration << std::endl;
    std::cout << "Expected Output: " << int_expected_force << std::endl;
    std::cout << "Output: " << int_force_output << std::endl;
    assert(int_force_output == int_expected_force);
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
