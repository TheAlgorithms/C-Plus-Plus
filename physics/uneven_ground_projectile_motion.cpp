/**
 * @file
 * @brief Uneven ground projectile motion 
 * https://en.wikipedia.org/wiki/Range_of_a_projectile#Uneven_ground
 * @details Uneven ground projectile motion is when the starting
 * height of a projectile is different than its ending height
 * 9.8 m/s^2 = acceleration due to gravity
 * Angles are in degrees
 * @author [nick01as](https://github.com/nick01as)
 */

#include <cassert> /// for assert()
#include <cmath> /// for std::pow(), std::sin(), std::cos()
#include <iostream> /// for I/O

// @brief Set PI equal to 3.141593

#define PI 3.141593

/** 
 * @namespace math
 * @brief Math equations used
 */
namespace math{

	/**
	 * @brief Quadratic formula to solve for time
	 * @param coefficient_a Coefficient of t^2
	 * @param coefficient_b Coefficient of t
	 * @param constant Constant 
	 * @returns Pair containing two roots
	 */
	std::pair<double,double> 
	quadratic_formula (double coefficient_a, double coefficient_b, double constant){

		double discriminant = (double)coefficient_b * (double)coefficient_b 
			- ((double)4.0 * (double)coefficient_a * (double)constant);
				/// Calculate value of b^2 - 4*a*c
		
		if(discriminant < 0) discriminant = 0; /// Handle imaginary numbers
		
		double root_one = ((-1 * coefficient_b) + sqrt(discriminant))
			/ (2*coefficient_a); /// Add discriminant 

			
		double root_two = ((-1 * coefficient_b) - sqrt(discriminant)) 
			/ (2*coefficient_a); /// Substract discriminant
		
		return std::make_pair(root_one,root_two);
	}

} // @namespace math

/**
 * @namespace physics
 * @brief Physics algorithms
 */
namespace physics{

	/**
	 * @namespace uneven_ground_projectile_motion
	 * @brief Calculate uneven ground projectiles
	 */
	namespace uneven_ground_projectile_motion{

		/**
		 * @brief Calculate time of flight
		 * @param initial_height Height of projectile at launch
		 * @param initial_velocity Speed of projectile at launch
		 * @param angle Angle which projectile is launched
		 * @param final_height Height when projectile hits the ground
		 * @returns Time projectile is in the air
		 */
		template <typename T> T 
		time_of_flight (T initial_height, T initial_velocity, T angle, T final_height) {
			
			double delta_height = final_height - initial_height; /// Calculate change in height

			double initial_y_velocity = -1 * std::sin(angle * PI /180) 
				* initial_velocity; /// Calculate initial velocity in y direction
				
			return math::quadratic_formula(4.9,initial_y_velocity,delta_height).first;
		}

		/**
		 * @brief Calculate distance projectile travels
		 * @param initial_height Height of projectile at launch
		 * @param initial_velocity Speed of projectile at launch
		 * @param angle Angle which projectile is launched
		 * @param final_height Height when projectile hits the ground
		 * @returns Distance projectile travels
		 */ 
		template <typename T> T 
		distance_traveled (T initial_height, T initial_velocity, T angle, T final_height){

			double time = time_of_flight(initial_height, initial_velocity, 
				angle, final_height); /// Calculate time projectile travels

			double velocity_x_dir = std::cos(angle * PI / 180) 
				* initial_velocity; /// Calculate x component of initial velocity
				
			return time * velocity_x_dir;
		}

		/**
		 * @brief Calculate maximum height of projectile
		 * @param initial_height Height of projectile at launch
		 * @param initial_velocity Speed of projectile at launch
		 * @param angle Angle which projectile is launched
		 * @returns Maximum height in reference to y = 0
		 */ 
		template <typename T> T 
		max_height(T initial_height, T initial_velocity, T angle){

			double initial_y_velocity = std::sin(angle * PI /180.0)
				* initial_velocity; /// Calculate y component of initial velocity
			
			return initial_height + (pow(initial_y_velocity,2.00) / 19.6);
		}

		/**
		 * @brief Calculate time taken for projectile to reach maximum height
		 * @param initial_height Height of projectile at launch
		 * @param initial_velocity Speed of projectile at launch
		 * @param angle Angle which projectile is launched
		 * @returns Time taken to reach maximum height
		 */ 
		template <typename T> T 
		time_to_max_height(T initial_height, T initial_velocity, T angle){

			double height = max_height
				(initial_height, initial_velocity, angle); /// Calculate maximum height reached

			return time_of_flight(initial_height, initial_velocity, angle, height);
		}

		/**
		 * @brief Calculate position of projectile at
		 * any given time
		 * @param initial_height Height of projectile at launch
		 * @param initial_velocity Speed of projectile at launch
		 * @param angle Angle which projectile is launched
		 * @param final_height Height when projectile hits the ground
		 * @param input_time Time inputed to determine projectile location
		 * @returns A pair with the x and y location of the projectile
		 */ 
		std::pair<double,double> 
		position_at_given_time (double initial_height, double initial_velocity, 
			double angle, double final_height, double input_time){

			double position_x_dir = std::cos(angle * PI / 180) 
				* initial_velocity * input_time; /// Distance traveled in x direction

			double position_y_dir = initial_height + (std::sin(angle * PI / 180) * 
				initial_velocity * input_time) 
					+ (-4.9 * pow(input_time,2)); /// Calculate y position

			return std::make_pair(position_x_dir,position_y_dir);
		}

	} // @namespace uneven_ground_projectile_motion
} // @namespace physics

/**
 * @brief Self-test implementations
 * @returns void
 */

static void test(){

	// Initialize variables
	
	double initial_velocity = 10; /// Initial velocity
	double angle = 60; /// Angle of projectile
	double initial_height = 10; /// Initial height
	double final_height = 3; /// Final height
	double input_time = 2.1; /// Time to determine projectile location
	
	// Test 1
	
	double expected_time_of_flight = 2.37; /// Expected time

	double time_taken = std::round(physics::uneven_ground_projectile_motion::
		time_of_flight(initial_height, initial_velocity, angle, final_height) 
			* 1000)/1000; /// Calculate time taken

	std::cout<<"TEST 1"<<std::endl;
	std::cout<<"Projectile Flight Time"<<std::endl<<std::endl;
	std::cout<<"Initial Height: "<<initial_height<<std::endl;
	std::cout<<"Initial Velocity: "<<initial_velocity<<std::endl;
	std::cout<<"Angle: "<<angle<<std::endl;
	std::cout<<"Final Height: "<<final_height<<std::endl<<std::endl;
	std::cout<<"Expected Output: "<<expected_time_of_flight<<std::endl;
	std::cout<<"Output: "<<time_taken<<std::endl<<std::endl;
	assert(expected_time_of_flight == time_taken);
	std::cout<<"TEST PASSED"<<std::endl<<std::endl<<std::endl;

	// Test 2

	double expected_distance_traveled = 11.851; /// Expected distance traveled

	double distance_traveled = std::round(physics::uneven_ground_projectile_motion::
		distance_traveled(initial_height, initial_velocity, angle, final_height) 
			* 1000)/1000; /// Calculate distance traveled
	
	std::cout<<"TEST 2"<<std::endl;
	std::cout<<"Distance Projectile Travels"<<std::endl<<std::endl;
	std::cout<<"Initial Height: "<<initial_height<<std::endl;
	std::cout<<"Initial Velocity: "<<initial_velocity<<std::endl;
	std::cout<<"Angle: "<<angle<<std::endl;
	std::cout<<"Final Height: "<<final_height<<std::endl<<std::endl;
	std::cout<<"Expected Output: "<<expected_distance_traveled<<std::endl;
	std::cout<<"Output: "<<distance_traveled<<std::endl<<std::endl;
	assert(expected_distance_traveled == distance_traveled);
	std::cout<<"TEST PASSED"<<std::endl<<std::endl<<std::endl;

	// Test 3

	double expected_max_height = 13.827; /// Expected maximum height

	double max_height = std::round(physics::uneven_ground_projectile_motion::
		max_height(initial_height, initial_velocity, angle) 
			* 1000)/1000; /// Calculated maximum height
	
	std::cout<<"TEST 3"<<std::endl;
	std::cout<<"Maximum Height of Projectile"<<std::endl<<std::endl;
	std::cout<<"Initial Height: "<<initial_height<<std::endl;
	std::cout<<"Initial Velocity: "<<initial_velocity<<std::endl;
	std::cout<<"Angle: "<<angle<<std::endl;
	std::cout<<"Expected Output: "<<expected_max_height<<std::endl;
	std::cout<<"Output: "<<max_height<<std::endl<<std::endl;
	assert(expected_max_height == max_height);
	std::cout<<"TEST PASSED"<<std::endl<<std::endl<<std::endl;

	// Test 4

	double expected_time_to_max_height = 0.884; /// Expected time to maximum height

	double max_height_time = std::round(physics::uneven_ground_projectile_motion::
		time_to_max_height(initial_height, initial_velocity, angle) 
			* 1000)/1000; /// Calculated time to maximum height

	std::cout<<"TEST 4"<<std::endl;
	std::cout<<"Time at Maximum Height of Projectile"<<std::endl<<std::endl;
	std::cout<<"Initial Height: "<<initial_height<<std::endl;
	std::cout<<"Initial Velocity: "<<initial_velocity<<std::endl;
	std::cout<<"Angle: "<<angle<<std::endl;
	std::cout<<"Expected Output: "<<expected_time_to_max_height<<std::endl;
	std::cout<<"Output: "<<max_height_time<<std::endl<<std::endl;
	assert(expected_time_to_max_height == max_height_time);
	std::cout<<"TEST PASSED"<<std::endl<<std::endl<<std::endl;

	// Test 5

	double expected_x_position_at_given_time = 10.5; /// Expected x position
	double expected_y_position_at_given_time = 6.578; /// Expected y position

	double x_position_at_given_time = std::round(physics::uneven_ground_projectile_motion::
		position_at_given_time(initial_height, initial_velocity, angle, final_height, input_time).first 
			* 1000)/1000; /// Calculated x position

	double y_position_at_given_time = std::round(physics::uneven_ground_projectile_motion::
		position_at_given_time(initial_height, initial_velocity, angle, final_height, input_time).second 
			* 1000)/1000; /// Calculated y position
		
	std::cout<<"TEST 5"<<std::endl;
	std::cout<<"Position of Projectile at Given Time"<<std::endl<<std::endl;
	std::cout<<"Initial Height: "<<initial_height<<std::endl;
	std::cout<<"Initial Velocity: "<<initial_velocity<<std::endl;
	std::cout<<"Angle: "<<angle<<std::endl;
	std::cout<<"Final Height: "<<final_height<<std::endl;
	std::cout<<"Inputted Time: "<<input_time<<std::endl;
	std::cout<<"Expected X Position: "<<expected_x_position_at_given_time<<std::endl;
	std::cout<<"Expected Y Position: "<<expected_y_position_at_given_time<<std::endl;
	std::cout<<"Output X Position: "<<x_position_at_given_time<<std::endl;
	std::cout<<"Output Y Position: "<<y_position_at_given_time<<std::endl<<std::endl;
	assert(expected_x_position_at_given_time == x_position_at_given_time && expected_y_position_at_given_time == y_position_at_given_time);
	std::cout<<"TEST PASSED"<<std::endl<<std::endl<<std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */

int main() {
	test(); // run self-test implementations
	return 0;
}
