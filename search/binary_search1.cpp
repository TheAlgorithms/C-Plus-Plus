/**
 * @file
 * @brief [Binary search
 * algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm)
 * @author [Mohammad Golzar](https://github.com/m-golzar)
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <array>
#include <cassert>
/**
* @namespace search
* @brief Searching algorithms
*/
namespace search {

	/**
	 * @namespace sublist_search
	 * @brief Functions for the [binary_search]
	 * implementation
	 */
	namespace binary_search {

		/** binary_search function
		 * \tparam Container type of a container to search, Container must support ([]) operator and size() method
		 * \tparam Key the key type, Key must support (== && <) operators
		 * \param container a container to search in it's elements
		 * \returns -1 there is no matched key in the container
		 * \returns index of the key in the container if found.
		 */
		template <typename Container, typename Key>
		int binary_search(const Container& container, const Key& key) {
			int right_limit = container.size() - 1;
			int left_limit = 0;
			while (left_limit <= right_limit) {
				/// calculate middle index of the range in current iteration.
				int middle = left_limit + (right_limit - left_limit) / 2;
				/// in case we have found the key, just return the index.
				if (key == container[middle])
					return middle;
				/// if desired key is less than the key at the middle index, it should be located in left side of the middle index
				/// so adjust the range right limit to search left side in the next iteration.
				else if (key < container[middle])
					right_limit = middle - 1;
				/// if desired key is grater than the key at the middle index, it should be located in right side of the middle index
				/// so adjust the range left limit to search right side in the next iteration.
				else
					left_limit = middle + 1;
			}
			/// return -1 in case we did not find the key.
			return -1;
		}
	}
}

/**
* @namespace test_classes
* @brief classes for testing the [binary_search] algorithm
* implementation
*/
namespace binary_search_test {

	/**
	*@brief sample class implemented to show the usage of algorithm with user defined types.
	*
	* ContainerClass class is a simple user defined container to show the usage of binary_search algorithm.
	* please note that ContainerClass class is implemented just for test purposes.
	*/
	template<typename T>
	class ContainerClass {
	public:
		ContainerClass() :m_elements{} {};
		void push_back(const T& element) {
			m_elements.push_back(element);
		}
		size_t size() const {
			return m_elements.size();
		}
		T& operator[](size_t index) {
			return m_elements[index];
		}
		const T& operator[](size_t index) const {
			return m_elements[index];
		}
	private:
		std::vector<T> m_elements;
	};

	/**
	*@brief sample class implemented to show the usage of algorithm with user defined types.
	*
	* KeyClass class is a simple user defined data type to show the usage of binary_search algorithm.
	* please note that KeyClass class is implemented just for test purposes.
	*/
	class KeyClass {
		friend std::ostream& operator<<(const KeyClass& key, std::ostream& rhs);
		friend bool operator==(const KeyClass& lhs, const KeyClass& rhs);
		friend bool operator< (const KeyClass& lhs, const KeyClass& rhs);
	public:
		KeyClass(int value = 0) :m_value(value) {};
		int get() const {
			return m_value;
		}
	private:
		int m_value = 0;
	};

	std::ostream & operator<<(const KeyClass& key, std::ostream& rhs)
	{
		return rhs << key.get();
	}

	bool operator==(const KeyClass & lhs, const KeyClass & rhs)
	{
		return (lhs.get() == rhs.get());
	}

	bool operator<(const KeyClass & lhs, const KeyClass & rhs)
	{
		return (lhs.get() < rhs.get());
	}

	using namespace search::binary_search;

	/**
	*@brief this class is implemented to encapsulate sample test cases
	*/
	class TestCases {
	private:
		void log(const std::string& msg) {
			std::cout << msg << std::endl;
		}
	public:
		/**
		*@brief running test cases one by one
		*/
		void run_tests() {
			test_case1();
			test_case2();
			test_case3();
			test_case4();
		}
		/**
		*@brief test case for running the binary_search algorithm on 'std::array' with integer keys
		*/
		void test_case1() {
			using Array = std::array<int, 10>;
			Array array = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			int key = 5;
			int result = binary_search<Array, int>(array, key);
			log("Checking assert expression...");
			assert(result == 4);
			log("Assertion check passed!");
			log("[PASS] : TEST CASE 1_1 PASS!");
			key = 20;
			result = binary_search<Array, int>(array, key);
			log("Checking assert expression...");
			assert(result == -1);
			log("Assertion check passed!");
			log("[PASS] : TEST CASE 1_2 PASS!");
			log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		}
		/**
		*@brief test case for running the binary_search algorithm on 'std::vector' with integer keys
		*/
		void test_case2() {
			using Vector = std::vector<int>;
			Vector vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			int key = 5;
			int result = binary_search<Vector, int>(vec, key);
			log("Checking assert expression...");
			assert(result == 4);
			log("Assertion check passed!");
			log("[PASS] : TEST CASE 2_1 PASS!");
			key = 20;
			result = binary_search<Vector, int>(vec, key);
			log("Checking assert expression...");
			assert(result == -1);
			log("Assertion check passed!");
			log("[PASS] : TEST CASE 2_2 PASS!");
			log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		}
		/**
		*@brief test case for running the binary_search algorithm on 'std::vector' with user defined 'KeyClass' keys
		*/
		void test_case3() {
			using Vector = std::vector<KeyClass>;
			Vector vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			KeyClass key = 5;
			int result = binary_search<Vector, KeyClass>(vec, key);
			log("Checking assert expression...");
			assert(result == 4);
			log("Assertion check passed!");
			log("[PASS] : TEST CASE 3_1 PASS!");
			key = 20;
			result = binary_search<Vector, KeyClass>(vec, key);
			log("Checking assert expression...");
			assert(result == -1);
			log("Assertion check passed!");
			log("[PASS] : TEST CASE 3_2 PASS!");
			log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		}

		/**
		*@brief test case for running the binary_search algorithm on user defined 'ContainerClass' container with 'std::string' keys
		*/
		void test_case4() {
			using Container = ContainerClass<std::string>;
			std::vector<std::string> strings{ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
			Container container;
			for (const auto& str : strings)
				container.push_back(str);
			std::string key = "E";
			int result = binary_search<Container, std::string>(container, key);
			log("Checking assert expression...");
			assert(result == 4);
			log("Assertion check passed!");
			log("[PASS] : TEST CASE 4_1 PASS!");
			key = "O";
			result = binary_search<Container, std::string>(container, key);
			log("Checking assert expression...");
			assert(result == -1);
			log("Assertion check passed!");
			log("[PASS] : TEST CASE 4_2 PASS!");
			log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		}	

	};

}
/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char const* argv[]) {
	binary_search_test::TestCases test;
	test.run_tests();  // run self-test implementations
	return 0;
}
