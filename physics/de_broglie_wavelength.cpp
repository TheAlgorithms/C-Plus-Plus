/**
 * @file
 * @brief de Broglie Wavelength [Matter
 * Waves](https://en.wikipedia.org/wiki/Matter_wave) implementations
 *
 * @details Matter waves are a central part of the theory of quantum mechanics,
 * being half of wave–particle duality. At all scales where measurements have
 * been practical, matter exhibits wave-like behavior.
 *
 * The concept that matter behaves like a wave was proposed by French
 * physicist Louis de Broglie in 1924, and so matter waves are also known as de
 * Broglie waves.
 * This implementation finds the de Broglie wavelength of these matter waves
 *
 * Relevant Formulas:
 *
 * Non-Relativistic Formula (when Kinetic Energy is \f$< 1\%\f$ of rest mass
 * energy):
 * \f[\lambda = \frac{h}{\sqrt{2meV}}\f]
 *
 * Relativistic Formula (when Kinetic Energy is \f$\ge 1\%\f$ of rest mass
 * energy):
 * \f[\lambda = \frac{hc}{\sqrt{eV(eV + 2mc^2)}}\f]
 *
 * Non-Relativistic Formula (when velocity is \f$< 10\%\f$ of the speed of
 * light):
 * \f[\lambda = \frac{h}{mv}\f]
 *
 * Relativistic Formula (when velocity is \f$\ge 10\%\f$ of the speed of light):
 * \f[\lambda = \frac{h\sqrt{1 - \frac{v^2}{c^2}}}{mv}\f]
 *
 * @note The relativistic formulas are valid at all speeds. The non-relativistic
 * ones are low-speed approximations. The tests use common rule-of-thumb cutoffs
 * to choose between them: kinetic energy below 1% of the rest mass energy
 * (accelerating voltage case), or velocity below 0.1c (velocity case).
 *
 * @author [SomrajBanik](https://github.com/SomrajBanik)
 */

#include <cassert>    /// for assert()
#include <cmath>      /// for std::sqrt, std::abs
#include <iostream>   /// for std::cout
#include <stdexcept>  /// for std::invalid_argument, std::domain_error
#include <string>     /// for std::string

/**
 * @namespace physics
 * @brief Physics algorithms
 */
namespace physics {
/**
 * @namespace de_Broglie_Wavelength
 * @brief Functions for de Broglie Wavelength Equations [Matter
 * waves](https://en.wikipedia.org/wiki/Matter_wave)
 */
namespace de_Broglie_Wavelength {

// constants
static constexpr double ELEMENTARY_CHARGE =
    1.602176634e-19;  ///< Elementary charge (e) in Coulombs
static constexpr double SPEED_OF_LIGHT =
    2.99792458e8;  ///< Speed of light (c) in m/s
static constexpr double PLANCK_CONSTANT =
    6.62607015e-34;  ///< Planck's constant (h) in Js
static constexpr double ELECTRON_MASS = 9.1093837e-31;  ///< Electron mass in kg

/**
 * @brief Kinetic Energy when accelerating voltage given
 * @param acc_Voltage Accelerating voltage used to accelerate the particle
 * @returns Kinetic Energy KE
 */
double KE_calculation(double acc_Voltage) {
    if (acc_Voltage < 0.0) {
        throw std::invalid_argument("Accelerating voltage cannot be negative.");
    }
    double KE = ELEMENTARY_CHARGE * acc_Voltage;
    return KE;
}

/**
 * @brief Calculate rest mass energy of the particle
 * @param mass Mass of the particle
 * @returns Rest mass energy (E_not)
 */
double rest_mass_energy_calculation(double mass) {
    if (mass <= 0.0) {
        throw std::invalid_argument(
            "Mass of the particle cannot be 0 or less.");
    }
    double E_not = mass * SPEED_OF_LIGHT * SPEED_OF_LIGHT;
    return E_not;
}

/**
 * @brief Calculates the Wavelength when the accelerating voltage is given to
 * us (non-relativistic case)
 * @param mass mass of the particle
 * @param acc_Voltage voltage used to accelerate the particle
 * @returns wavelength (lambda1)
 */
double lambda_Vol_given_non_rel(double mass, double acc_Voltage) {
    if (mass <= 0.0 || acc_Voltage <= 0.0) {
        throw std::invalid_argument(
            "Mass and accelerating voltage must be positive and non-zero.");
    }
    double lambda1 =
        PLANCK_CONSTANT / std::sqrt(2 * mass * ELEMENTARY_CHARGE * acc_Voltage);
    return lambda1;
}

/**
 * @brief Calculates the Wavelength when the accelerating voltage is given to
 * us (relativistic case)
 * @param mass mass of the particle
 * @param acc_Voltage voltage used to accelerate the particle
 * @returns wavelength (lambda2)
 */
double lambda_Vol_given_rel(double mass, double acc_Voltage) {
    if (mass <= 0.0 || acc_Voltage <= 0.0) {
        throw std::invalid_argument(
            "Mass and accelerating voltage must be positive and non-zero.");
    }
    double lambda2 = (PLANCK_CONSTANT * SPEED_OF_LIGHT) /
                     std::sqrt((ELEMENTARY_CHARGE * acc_Voltage) *
                               ((ELEMENTARY_CHARGE * acc_Voltage) +
                                (2 * mass * SPEED_OF_LIGHT * SPEED_OF_LIGHT)));
    return lambda2;
}

/**
 * @brief Calculates the Wavelength when the velocity is given to us
 * (non-relativistic case)
 * @param mass mass of the particle
 * @param velocity Velocity of the particle
 * @returns wavelength (lambda3)
 */
double lambda_Vel_given_non_rel(double mass, double velocity) {
    if (mass <= 0.0 || velocity <= 0.0) {
        throw std::invalid_argument(
            "Mass and velocity must be strictly positive.");
    }
    if (velocity >= SPEED_OF_LIGHT) {
        throw std::domain_error(
            "Velocity cannot be greater than or equal to the speed of light.");
    }
    double lambda3 = PLANCK_CONSTANT / (mass * velocity);
    return lambda3;
}

/**
 * @brief Calculates the Wavelength when the velocity is given to us
 * (relativistic case)
 * @param mass mass of the particle
 * @param velocity Velocity of the particle
 * @returns wavelength (lambda4)
 */
double lambda_Vel_given_rel(double mass, double velocity) {
    if (mass <= 0.0 || velocity <= 0.0) {
        throw std::invalid_argument(
            "Mass and velocity must be strictly positive.");
    }
    if (velocity >= SPEED_OF_LIGHT) {
        throw std::domain_error(
            "Velocity cannot be greater than or equal to the speed of light.");
    }
    double lorentz_factor =
        1 / std::sqrt(1 - ((velocity * velocity) /
                           (SPEED_OF_LIGHT * SPEED_OF_LIGHT)));
    double lambda4 = PLANCK_CONSTANT / (lorentz_factor * mass * velocity);
    return lambda4;
}
}  // namespace de_Broglie_Wavelength
}  // namespace physics

/**
 * @brief Helper utility function to check floating point result proximity
 * @param actual Calculated value
 * @param expected Expected value
 * @returns true if the relative difference is below 1e-5
 */
static bool is_close(double actual, double expected) {
    return std::abs(actual - expected) < (1e-5 * std::abs(expected));
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    using physics::de_Broglie_Wavelength::ELECTRON_MASS;
    using physics::de_Broglie_Wavelength::KE_calculation;
    using physics::de_Broglie_Wavelength::lambda_Vel_given_non_rel;
    using physics::de_Broglie_Wavelength::lambda_Vel_given_rel;
    using physics::de_Broglie_Wavelength::lambda_Vol_given_non_rel;
    using physics::de_Broglie_Wavelength::lambda_Vol_given_rel;
    using physics::de_Broglie_Wavelength::rest_mass_energy_calculation;
    using physics::de_Broglie_Wavelength::SPEED_OF_LIGHT;

    double lambda =
        0.0;  // declaring lambda variable to be used in all the tests
    bool thrown = false;  // used by the error handling tests

    std::cout << "\n";
    std::cout << "\n";

    // Test Case 1:
    std::cout << "Test Case 1" << "\n";
    std::cout << "Accelerating voltage given: 100.0 V" << "\n";
    std::cout << "Mass of the Particle: 9.1093837e-31 kg (Electron)"
              << "\n";
    // check whether it is relativistic or non-relativistic case:
    if (KE_calculation(100.0) <
        (0.01 * rest_mass_energy_calculation(ELECTRON_MASS))) {
        // non-relativistic case
        lambda = lambda_Vol_given_non_rel(ELECTRON_MASS, 100.0);
    } else {
        // relativistic case
        lambda = lambda_Vol_given_rel(ELECTRON_MASS, 100.0);
    }
    assert(is_close(lambda, 1.22643e-10));
    std::cout << "Expected Wavelength: 1.22643e-10" << " meters"
              << "\n";
    std::cout << "Result Wavelength: " << lambda << " meters" << "\n";
    std::cout << "----TEST PASSED----" << "\n" << "\n";

    // Test Case 2:
    std::cout << "Test Case 2" << "\n";
    std::cout << "Accelerating voltage given: 100000.0 V" << "\n";
    std::cout << "Mass of the Particle: 9.1093837e-31 kg (Electron)"
              << "\n";

    // check whether it is relativistic or non-relativistic case:
    if (KE_calculation(100000.0) <
        (0.01 * rest_mass_energy_calculation(ELECTRON_MASS))) {
        // non-relativistic case
        lambda = lambda_Vol_given_non_rel(ELECTRON_MASS, 100000.0);
    } else {
        // relativistic case
        lambda = lambda_Vol_given_rel(ELECTRON_MASS, 100000.0);
    }
    assert(is_close(lambda, 3.70144e-12));
    std::cout << "Expected Wavelength: 3.70144e-12" << " meters"
              << "\n";
    std::cout << "Result Wavelength: " << lambda << " meters" << "\n";
    std::cout << "----TEST PASSED----" << "\n" << "\n";

    // Test Case 3:
    std::cout << "Test Case 3" << "\n";
    std::cout << "Velocity given: 2.19e6 m/s" << "\n";
    std::cout << "Mass of the Particle: 9.1093837e-31 kg (Electron)"
              << "\n";
    // check whether it is relativistic or non-relativistic case:
    if (2.19e6 < (0.1 * SPEED_OF_LIGHT)) {
        // non relativistic case
        lambda = lambda_Vel_given_non_rel(ELECTRON_MASS, 2.19e6);

    } else {
        // relativistic case
        lambda = lambda_Vel_given_rel(ELECTRON_MASS, 2.19e6);
    }
    assert(is_close(lambda, 3.32141e-10));
    std::cout << "Expected Wavelength: 3.32141e-10" << " meters"
              << "\n";
    std::cout << "Result Wavelength: " << lambda << " meters" << "\n";
    std::cout << "----TEST PASSED----" << "\n" << "\n";

    // Test Case 4:
    std::cout << "Test Case 4" << "\n";
    std::cout << "Velocity given: 2.4e8 m/s" << "\n";
    std::cout << "Mass of the Particle: 9.1093837e-31 kg (Electron)"
              << "\n";
    // check whether it is relativistic or non-relativistic case:
    if (2.4e8 < (0.1 * SPEED_OF_LIGHT)) {
        // non relativistic case
        lambda = lambda_Vel_given_non_rel(ELECTRON_MASS, 2.4e8);

    } else {
        // relativistic case
        lambda = lambda_Vel_given_rel(ELECTRON_MASS, 2.4e8);
    }
    assert(is_close(lambda, 1.81623e-12));
    std::cout << "Expected Wavelength: 1.81623e-12" << " meters"
              << "\n";
    std::cout << "Result Wavelength: " << lambda << " meters" << "\n";
    std::cout << "----TEST PASSED----" << "\n" << "\n";

    // Test Case 5:
    std::cout << "Test Case 5" << "\n";
    std::cout << "Velocity given: 120 m/s" << "\n";
    std::cout << "Mass of the Particle: 0.5 kg (Say A Ball)" << "\n";
    // check whether it is relativistic or non-relativistic case:
    if (120 < (0.1 * SPEED_OF_LIGHT)) {
        // non relativistic case
        lambda = lambda_Vel_given_non_rel(0.5, 120);

    } else {
        // relativistic case
        lambda = lambda_Vel_given_rel(0.5, 120);
    }
    assert(is_close(lambda, 1.10435e-35));
    std::cout << "Expected Wavelength: 1.10435e-35" << " meters"
              << "\n";
    std::cout << "Result Wavelength: " << lambda << " meters" << "\n";
    std::cout << "----TEST PASSED----" << "\n" << "\n";

    // Test case 6: (invalid argument test)
    std::cout << "Test Case 6" << "\n";
    std::cout << "Accelerating voltage given: -50.0 V (Invalid)"
              << "\n";
    std::cout << "Mass of the Particle: 9.1093837e-31 kg (Electron)"
              << "\n";
    thrown = false;
    try {
        lambda = lambda_Vol_given_non_rel(ELECTRON_MASS, -50.0);
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught Exception Message: " << e.what() << "\n";
        assert(std::string(e.what()) ==
               "Mass and accelerating voltage must be positive and "
               "non-zero.");
        thrown = true;
    }
    assert(thrown);
    std::cout << "----TEST PASSED----" << "\n" << "\n";

    // Test Case 7: (domain error test)
    std::cout << "Test Case 7" << "\n";
    std::cout << "Velocity given: 4.55e8 m/s (greater than the speed of light)"
              << "\n";
    std::cout << "Mass of the Particle: 1.67262192e-27 "
                 "kg (Proton)"
              << "\n";
    thrown = false;
    try {
        lambda = lambda_Vel_given_rel(1.67262192e-27, 4.55e8);
    } catch (const std::domain_error& e) {
        std::cout << "Caught Exception Message: " << e.what() << "\n";
        assert(std::string(e.what()) ==
               "Velocity cannot be greater than or equal to the speed of "
               "light.");
        thrown = true;
    }
    assert(thrown);
    std::cout << "----TEST PASSED----" << "\n" << "\n";
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
