/**
 * @file
 * @brief determine no. of areas a circle is divided into by n chords
 * @details
 * This is a code implementation of Moser's Circle Problem
 * The problem asks the total number of sections having non-zero area
 * when a circle is divided by n chords
 *
 * The question relies on two important formulas:
 * Euler's Characteristic Formula: V - E + F = 2
 * Standard Combination formula: nCr = n! / (r! * (n-r)!)
 *
 * A complete explanation of the solution can be found here:
 * https://www.youtube.com/watch?v=YtkIWDE36qU
 *
 * Other methods to solve this problem and related problems can be found here:
 * https://en.wikipedia.org/wiki/Dividing_a_circle_into_areas
 *
 * @author [Vibhor Agrawal](https://github.com/VibhorAgrawal2003)
 */

#include <cassert>
#include <iostream>

/**
 * @brief Class documentation
 * Mosers_circle class describes circles where chords
 * cut the circle into maximum possible non-zero areas
 */
class Mosers_circle {
 private:
    int index;   // number of points that lie on the circle
    int points;  // number of points inside circle formed by intersections
    int chords;  // number of chords drawn on circle
    int areas;   // number of regions circle is split into

 public:
    /**
     * @brief Constructor documentation
     * @param i number of points we place on the circle to draw chords
     */

    Mosers_circle(int i) {
        index = i;
        chords = number_of_chords();
        points = number_of_points();
        areas = number_of_areas();
    }

    /**
     * @brief Function documentation
     * @param n number of choices available
     * @param r number of choices we have to make
     * @returns total ways to make those choices
     */

    int combinations(int n, int r) {
        int com = 1;

        for (int i = n; i > (n - r); i--) {
            com *= i;
        }

        for (int i = r; i > 1; i--) {
            com /= i;
        }

        return com;
    }

    /**
     * @brief Function documentation
     * @returns number of chords we can make from given points
     *
     * In case 1 or less points are placed on circle to draw chords, then zero
     * chords are possible
     */

    int number_of_chords() {
        if (index <= 1) {
            return 0;
        }

        return combinations(index, 2);
    }

    /**
     * @brief Function documentation
     * @returns number of points formed inside circle by intersecting chords
     *
     * In case 3 or less points are placed on circle to draw chords, then no
     * intersection points land inside the circle
     */

    int number_of_points() {
        if (index <= 3) {
            return 0;
        }
        return combinations(index, 4);
    }

    /**
     * @brief Function documentation
     * @returns max number of areas we can divide the circle into by given
     * chords
     */

    int number_of_areas() {
        /**
         * @brief we apply Euler's Characteristic Formula
         *
         * For any planar graph: V - E + F = 2
         * V represents vertices
         * E represents edges
         * F represents faces or closed regions in graph
         * We also include the outer region of space in F
         *
         * E = original chords + new edges formed by inside points + arcs on
         * circle
         * => E = chords + 2*points + index
         *
         * V = points on circle + points inside circle
         * => V = index + points
         *
         * F = 1 + E - V as we are excluding outer region
         * => F = 1 + chords + 2*points + index - index - points
         * => F = 1 + chords + points
         *
         */

        return 1 + chords + points;
    }
};

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /* descriptions of the following test */

    Mosers_circle* M1 = new Mosers_circle(1);
    Mosers_circle* M2 = new Mosers_circle(2);
    Mosers_circle* M3 = new Mosers_circle(3);
    Mosers_circle* M4 = new Mosers_circle(4);
    Mosers_circle* M5 = new Mosers_circle(5);
    Mosers_circle* M6 = new Mosers_circle(6);

    assert(M1->number_of_areas() == 1);
    assert(M2->number_of_areas() == 2);
    assert(M3->number_of_areas() == 4);
    assert(M4->number_of_areas() == 8);
    assert(M5->number_of_areas() == 16);
    assert(M6->number_of_areas() == 31);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char* argv[]) {
    test();  // run self-test implementations
    return 0;
}