/**
 * @file
 * @brief [Binary to Decimal conversion]
 * @details
 * Given a binary number (string), convert it to decimal format.
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * @author [Vishwa Krishnan](https://github.com/vishwakrishnan02)
 */

#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>


 /**
  * @namespace others
  * @brief Other algorithms (conversions, etc.)
  */


namespace others {

    /**
     * @namespace binary_to_decimal
     * @brief Function for converting binary to decimal
     */

    namespace binary_to_decimal {
        /**
        * @brief The main function checks if the binary number is properly converted to decimal
        * @param "binary" string is the binary number to be converted
        * @returns a decimal after converting binary string
        */



        int binary_to_decimal(std::string binary)
        {

            reverse(binary.begin(), binary.end());
            //Reverses binary string for easier calculation compatibility (Ex: 1010 reversed to 0101)
            int decimal = 0, i = 0, binarySize = binary.size();

            //Goes through entire string and for every instance of "1", decimal variable is updated
            while (binarySize--) {
                if (binary[i] == '1') {
                    decimal += pow(2, i);
                }
                i++;
            }

            return decimal;
        }
    }
}


static void test() {

    //Input: 0 | Output: 0
    assert(others::binary_to_decimal::binary_to_decimal("0") == 0);

    //Input: 1 | Output: 1
    assert(others::binary_to_decimal::binary_to_decimal("1") == 1);

    //Input: 1010 | Output: 10
    assert(others::binary_to_decimal::binary_to_decimal("1010") == 10);

    //Input: 0101 | Output: 5
    assert(others::binary_to_decimal::binary_to_decimal("0101") == 5);

    //Input: 11111111 | Output: 255
    assert(others::binary_to_decimal::binary_to_decimal("11111111") == 255);

    //Input: 00000001 | Output: 1
    assert(others::binary_to_decimal::binary_to_decimal("00000001") == 1);

    std::cout << "Test cases passed." << std::endl;

}

int main()
{
    test(); //Runs all the self-implemented test cases.
    return 0;
}
