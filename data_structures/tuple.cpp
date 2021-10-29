/**
 * @file
 * @brief Tuple implementation
 * @author [jay-tux](https://github.com/jay-tux)
 */

#include <cassert>   /// for assert
#include <stdexcept> /// for std::runtime_error

namespace data_structures {
namespace tuple {

/**
 * @brief Tuple type (recursively defined, with multiple arguments)
 * @tparam T the type of the first value in the tuple
 * @tparam TRest the types of the other values
 */
template <typename T, typename T2, typename ... TRest>
struct tuple {
  static const bool has_next = true;
  T val;
  tuple<T2, TRest...> rest;
  tuple(T val, T2 v2, TRest ... rest) : val{val}, rest{tuple<T2, TRest...>(v2, rest...)} {}
};

/**
 * @brief Tuple type (base case, one argument left)
 * @tparam T the type of the value in the tuple
 */
template <typename T, typename T2>
struct tuple<T, T2> {
  static const bool has_next = false;
  T val;
  T2 rest;
  //nullptr_t rest;
  tuple(T val, T2 rest) : val{val}, rest{rest} {}
};

/**
 * @brief Gets the n-th element in the given tuple
 * @tparam index index of the element to get
 * @tparam T the type of the first value in the tuple
 * @tparam TRest the types of the other values in the tuple (if any)
 * @param tp the tuple to search
 * @returns the n-th element in the tuple
 * @throws std::runtime_error on out of bounds
 */
template <size_t index, typename T, typename ... TRest>
constexpr auto get(tuple<T, TRest...> tp) {
  if constexpr(index == 0) { return tp.val; }
  else if constexpr(!tp.has_next) {
    if constexpr(index != 1) throw std::runtime_error("Invalid index");
    return tp.rest;
  }
  else return get<index - 1>(tp.rest);
}

} // namespace tuple
} // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    using data_structures::tuple::tuple;

    tuple<int, float, char> tp(7, 0.5f, 'a');

    assert(data_structures::tuple::get<0>(tp) == 7);
    assert(data_structures::tuple::get<1>(tp) == 0.5f);
    assert(data_structures::tuple::get<2>(tp) == 'a');

    try {
	    data_structures::tuple::get<3>(tp);
      assert("Invalid index not caught" && false);
    }
    catch(std::runtime_error) {}
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    return 0;
}
