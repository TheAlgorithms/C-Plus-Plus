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
 * Broglie waves. This implementation finds the de Broglie wavelength of these
 * matter waves
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
#include <iostream>   /// for std::cout, std::endl
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
static constexpr double ELECTRON_MASS = 
    9.1093837e-31;  ///< Electron mass in kg

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
 * @brief Calculates the Wave length when the accelerating voltage is given to
 * us for (non-relativistic case)
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
 * @brief Calculates the Wave length when the accelerating voltage is given to
 * us (for relativistic case)
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
 * @brief Calculates the Wave length when the velocity is given to us (for
 * non-relativistic case)
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
 * @brief Calculates the Wave length when the velocity is given to us (for
 * relativistic case)
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
 * @param actual calculated value
 * @param expected expected value
 * @returns true if the relative difference is below 1e-5
 */
static bool is_close(double actual, double expected) {
    return std::abs(actual - expected) < (1e-5 * expected);
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

    std::cout << std::endl;
    std::cout << std::endl;

    // Test Case 1:
    try {
        std::cout << "Test Case 1" << std::endl;
        std::cout << "Accelerating voltage given: 100.0 V" << std::endl;
        std::cout << "Mass of the Particle: 9.1093837e-31 kg (Electron)"
                  << std::endl;
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
                  << std::endl;
        std::cout << "Result Wavelength: " << lambda << " meters" << std::endl;
        std::cout << "----TEST PASSED----" << std::endl << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test 1 Unexpected Exception: " << e.what() << std::endl;
        assert(false);
    }

    // Test Case 2:
    try {
        std::cout << "Test Case 2" << std::endl;
        std::cout << "Accelerating voltage given: 100000.0 V" << std::endl;
        std::cout << "Mass of the Particle: 9.1093837e-31 kg (Electron)"
                  << std::endl;

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
                  << std::endl;
        std::cout << "Result Wavelength: " << lambda << " meters" << std::endl;
        std::cout << "----TEST PASSED----" << std::endl << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test 2 Unexpected Exception: " << e.what() << std::endl;
        assert(false);
    }

    // Test Case 3:
    try {
        std::cout << "Test Case 3" << std::endl;
        std::cout << "Velocity = 2.19e6 m/s" << std::endl;
        std::cout << "Mass of the Particle: 9.1093837e-31 kg (Electron)"
                  << std::endl;
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
                  << std::endl;
        std::cout << "Result Wavelength: " << lambda << " meters" << std::endl;
        std::cout << "----TEST PASSED----" << std::endl << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test 3 Unexpected Exception: " << e.what() << std::endl;
        assert(false);
    }

    // Test Case 4:
    try {
        std::cout << "Test Case 4" << std::endl;
        std::cout << "Velocity = 2.4e8 m/s" << std::endl;
        std::cout << "Mass of the Particle: 9.1093837e-31 kg (Electron)"
                  << std::endl;
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
                  << std::endl;
        std::cout << "Result Wavelength: " << lambda << " meters" << std::endl;
        std::cout << "----TEST PASSED----" << std::endl << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test 4 Unexpected Exception: " << e.what() << std::endl;
        assert(false);
    }

    // Test Case 5:
    try {
        std::cout << "Test Case 5" << std::endl;
        std::cout << "Velocity = 120 m/s" << std::endl;
        std::cout << "Mass of the Particle: 0.5 kg (Say A Ball)" << std::endl;
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
                  << std::endl;
        std::cout << "Result Wavelength: " << lambda << " meters" << std::endl;
        std::cout << "----TEST PASSED----" << std::endl << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test 5 Unexpected Exception: " << e.what() << std::endl;
        assert(false);
    }

    // Test case 6: (error handling test)
    try {
        std::cout << "Test Case 6" << std::endl;
        std::cout << "Accelerating voltage given: -50.0 V (Invalid)"
                  << std::endl;
        std::cout << "Mass of the Particle: 9.1093837e-31 kg (Electron)"
                  << std::endl;

        // Trying to calculate with invalid negative input
        lambda = lambda_Vol_given_non_rel(ELECTRON_MASS, -50.0);

        std::cout << "Result Wavelength: " << lambda << " meters" << std::endl;
        std::cout << "ERROR: Code allowed a negative voltage input"
                  << std::endl;
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught Exception Message: " << e.what() << std::endl;
        std::string expected_error =
            "Mass and accelerating voltage must be positive and non-zero.";
        assert(std::string(e.what()) == expected_error);

        std::cout << "Expected Behavior: Exception successfully verified!"
                  << std::endl;
        std::cout << "----TEST PASSED----" << std::endl << std::endl;
    }
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
