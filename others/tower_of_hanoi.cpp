/**
 * @file
 * @brief Solve the [Tower of
 * Hanoi](https://en.wikipedia.org/wiki/Tower_of_Hanoi) problem.
 */
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

/**
 * Define the state of tower
 */
struct tower {
    //! Values in the tower
    int values[10];
    //! top tower ID
    int top;
};

/**
 * @brief Display the current state of the three towers (F, U, T).
 * @param F pointer to the "From" tower (input)
 * @param T pointer to the "To" tower (input)
 * @param U pointer to the "Using" (auxiliary) tower (input)
 * @returns void (returns nothing; prints formatted state to std::cout)
 *
 * Boundary Specification:
 * | Group | Condition | Source Line Justification |
 * | :--- | :--- | :--- |
 * | Valid boundary (smallest) | top == 0 (all towers empty) | tower_of_hanoi.cpp:19,35,39,43 |
 * | Valid interior (ordinary) | 1 <= top <= 9 (normal disc arrangement) | tower_of_hanoi.cpp:17,19 |
 * | Valid boundary (largest)  | top == 10 (maximum array capacity) | tower_of_hanoi.cpp:17 (values[10]) |
 * | Unsupported / undefined   | top > 10, top < 0, or nullptr | tower_of_hanoi.cpp:17,32 |
 *
 * @note This function does not mutate any of the towers (read-only).
 */
void show(const struct tower *const F, const struct tower *const T,
          const struct tower *const U) {
    std::cout << "\n\n\tF : ";
    for (int i = 0; i < F->top; i++) {
        std::cout << F->values[i] << "\t";
    }
    std::cout << "\n\tU : ";
    for (int i = 0; i < U->top; i++) {
        std::cout << U->values[i] << "\t";
    }
    std::cout << "\n\tT : ";
    for (int i = 0; i < T->top; i++) {
        std::cout << T->values[i] << "\t";
    }
}

/** Move one disc from one tower to another
 * \param [in,out] From tower to move disk *from*
 * \param [in,out] To  tower to move disk *to*
 */
void mov(tower *From, tower *To) {
    --From->top;
    To->values[To->top] = From->values[From->top];
    ++To->top;
}

/**
 * Recursive algorithm to solve the puzzle
 * \param [in] n starting number of disks
 * \param [in,out] From  tower to move disks from
 * \param [in,out] Using temporary tower for the puzzle
 * \param [in,out] To  tower to move disk to
 */
void TH(int n, tower *From, tower *Using, tower *To) {
    if (n == 1) {
        mov(From, To);
        show(From, To, Using);
    } else {
        TH(n - 1, From, To, Using);
        mov(From, To);
        show(From, To, Using);
        TH(n - 1, Using, From, To);
    }
}

/**
 * @brief Helper function to capture the std::cout output of show() into a string.
 * @param F pointer to the From tower
 * @param T pointer to the To tower
 * @param U pointer to the Using tower
 * @returns std::string captured console output
 */
static std::string capture_show(const struct tower *const F,
                                const struct tower *const T,
                                const struct tower *const U) {
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
    show(F, T, U);  // tower_of_hanoi.cpp:32 call show with F, T, U
    std::cout.rdbuf(old);
    return buffer.str();
}

/**
 * @brief Test smallest boundary case: all towers empty (top = 0).
 */
static void test_show_smallest_boundary() {
    struct tower F{}, U{}, T{};
    F.top = 0;  // tower_of_hanoi.cpp:19 top initialized to 0 (smallest boundary)
    U.top = 0;  // tower_of_hanoi.cpp:19 top initialized to 0
    T.top = 0;  // tower_of_hanoi.cpp:19 top initialized to 0

    std::string expected = "\n\n\tF : \n\tU : \n\tT : ";  // tower_of_hanoi.cpp:33-44 empty towers print headers only
    std::string actual = capture_show(&F, &T, &U);

    if (actual != expected) {
        std::cerr << "test_show_smallest_boundary failed!\nExpected:\n[" << expected
                  << "]\nActual:\n[" << actual << "]\n";
        std::exit(1);
    }
    assert(actual == expected);  // tower_of_hanoi.cpp:33 assert exact match
}

/**
 * @brief Test just above smallest boundary: tower F has exactly 1 disc (top = 1).
 */
static void test_show_just_above_smallest() {
    struct tower F{}, U{}, T{};
    F.top = 1;        // tower_of_hanoi.cpp:19 top is 1 (just above smallest boundary)
    F.values[0] = 1;  // tower_of_hanoi.cpp:17 values[0] holds first disc
    U.top = 0;        // tower_of_hanoi.cpp:19 empty tower
    T.top = 0;        // tower_of_hanoi.cpp:19 empty tower

    std::string expected = "\n\n\tF : 1\t\n\tU : \n\tT : ";  // tower_of_hanoi.cpp:35 prints disc followed by tab
    std::string actual = capture_show(&F, &T, &U);

    if (actual != expected) {
        std::cerr << "test_show_just_above_smallest failed!\nExpected:\n[" << expected
                  << "]\nActual:\n[" << actual << "]\n";
        std::exit(1);
    }
    assert(actual == expected);  // tower_of_hanoi.cpp:35 assert exact match
}

/**
 * @brief Test ordinary interior case: discs 2 and 1 on tower F (top = 2), others empty.
 */
static void test_show_ordinary() {
    struct tower F{}, U{}, T{};
    F.top = 2;        // tower_of_hanoi.cpp:19 top is 2 (interior case)
    F.values[0] = 2;  // tower_of_hanoi.cpp:17 bottom disc is 2
    F.values[1] = 1;  // tower_of_hanoi.cpp:17 top disc is 1
    U.top = 0;        // tower_of_hanoi.cpp:19 empty tower
    T.top = 0;        // tower_of_hanoi.cpp:19 empty tower

    std::string expected = "\n\n\tF : 2\t1\t\n\tU : \n\tT : ";  // tower_of_hanoi.cpp:35 prints each disc with tab
    std::string actual = capture_show(&F, &T, &U);

    if (actual != expected) {
        std::cerr << "test_show_ordinary failed!\nExpected:\n[" << expected
                  << "]\nActual:\n[" << actual << "]\n";
        std::exit(1);
    }
    assert(actual == expected);  // tower_of_hanoi.cpp:35 assert exact match
}

/**
 * @brief Test just below largest boundary: tower F has 9 discs (top = 9).
 */
static void test_show_just_below_largest() {
    struct tower F{}, U{}, T{};
    F.top = 9;  // tower_of_hanoi.cpp:19 top is 9 (one below maximum capacity of 10)
    for (int i = 0; i < 9; i++) {
        F.values[i] = 9 - i;  // tower_of_hanoi.cpp:17 populate values[0..8]
    }
    U.top = 0;  // tower_of_hanoi.cpp:19 empty tower
    T.top = 0;  // tower_of_hanoi.cpp:19 empty tower

    std::string expected =
        "\n\n\tF : 9\t8\t7\t6\t5\t4\t3\t2\t1\t\n\tU : \n\tT : ";  // tower_of_hanoi.cpp:35 prints 9 discs with tabs
    std::string actual = capture_show(&F, &T, &U);

    if (actual != expected) {
        std::cerr << "test_show_just_below_largest failed!\nExpected:\n[" << expected
                  << "]\nActual:\n[" << actual << "]\n";
        std::exit(1);
    }
    assert(actual == expected);  // tower_of_hanoi.cpp:35 assert exact match
}

/**
 * @brief Test largest boundary case: full tower capacity (10 discs on tower F, top = 10).
 */
static void test_show_largest_boundary() {
    struct tower F{}, U{}, T{};
    F.top = 10;  // tower_of_hanoi.cpp:17,19 values[10] array boundary limit
    for (int i = 0; i < 10; i++) {
        F.values[i] = 10 - i;  // tower_of_hanoi.cpp:17 populate values[0..9]
    }
    U.top = 0;  // tower_of_hanoi.cpp:19 empty tower
    T.top = 0;  // tower_of_hanoi.cpp:19 empty tower

    std::string expected =
        "\n\n\tF : 10\t9\t8\t7\t6\t5\t4\t3\t2\t1\t\n\tU : \n\tT : ";  // tower_of_hanoi.cpp:35 prints all 10 discs
    std::string actual = capture_show(&F, &T, &U);

    if (actual != expected) {
        std::cerr << "test_show_largest_boundary failed!\nExpected:\n[" << expected
                  << "]\nActual:\n[" << actual << "]\n";
        std::exit(1);
    }
    assert(actual == expected);  // tower_of_hanoi.cpp:35 assert exact match
}

/**
 * @brief Test repeated call and mutation invariance: show does not alter tower states.
 */
static void test_show_repeated_call_mutation_invariance() {
    struct tower F{}, U{}, T{};
    F.top = 2;        // tower_of_hanoi.cpp:19 initial top is 2
    F.values[0] = 2;  // tower_of_hanoi.cpp:17 values[0] is 2
    F.values[1] = 1;  // tower_of_hanoi.cpp:17 values[1] is 1
    U.top = 0;        // tower_of_hanoi.cpp:19 empty tower
    T.top = 0;        // tower_of_hanoi.cpp:19 empty tower

    std::string first_call = capture_show(&F, &T, &U);   // tower_of_hanoi.cpp:32 first call
    std::string second_call = capture_show(&F, &T, &U);  // tower_of_hanoi.cpp:32 second call

    if (first_call != second_call) {
        std::cerr << "test_show_repeated_call_mutation_invariance failed (output changed)!\n";
        std::exit(1);
    }
    assert(first_call == second_call);  // tower_of_hanoi.cpp:32 outputs must be identical

    // tower_of_hanoi.cpp:17,19 confirm tower states were not mutated
    assert(F.top == 2);
    assert(F.values[0] == 2);
    assert(F.values[1] == 1);
    assert(U.top == 0);
    assert(T.top == 0);
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    test_show_smallest_boundary();
    test_show_just_above_smallest();
    test_show_ordinary();
    test_show_just_below_largest();
    test_show_largest_boundary();
    test_show_repeated_call_mutation_invariance();
    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
