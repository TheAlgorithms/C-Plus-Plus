/**
 * @file
 * @brief Find the biggest area of a slice within a matrix with cuts
 */
#include <iostream>
#include <vector>
#include <cassert>

/** Move through vectors of cuts to find the largest slice
 * \param [in] h number of rows
 * \param [in] w number of columns
 * \param [in] horizontalCuts vector to read cuts from
 * \param [in] verticalCuts vector to read cuts from
 */
int maxArea(int h, int w, std::vector<int>& horizontalCuts, std::vector<int>& verticalCuts) {

    ///Find the largest horizontal slice
    int maxH = horizontalCuts[0]-0;

    for(int i = 1; i < horizontalCuts.size(); i ++){
        maxH = std::max(maxH,horizontalCuts[i]-horizontalCuts[i-1]);
    }

    maxH = std::max(maxH,h-horizontalCuts[horizontalCuts.size()-1]);

    ///Find the largest vertical slice
    int maxV = verticalCuts[0]-0;

    for(int i = 1; i < verticalCuts.size(); i ++){
        maxV = std::max(maxV,verticalCuts[i]-verticalCuts[i-1]);
    }

    maxV = std::max(maxV,w-verticalCuts[verticalCuts.size()-1]);

    /// Multiply the largest vertical and horizontal slices to find the biggest total slice
    int ans = (maxV)*(maxH);
    return int(ans);
}
static void test() {
    /* This test verifies that the biggest slice is correctly identified */
    std::vector<int> verticalCuts{1,3};
    std::vector<int> horizontalCuts{1,2,4};
    assert(maxArea(5,4,verticalCuts,horizontalCuts) == 4); // this ensures that the algorithm works as expected
}

/** main function */
int main() {
    test();

    int h, w,input;///Defines the height, width and input variables

    /// Read in the total height and width
    std::cout<<"Input Height" <<std::endl;
    std::cin >> h;
    std::cout<<"Input Width" <<std::endl;
    std::cin >> w;

    /// Read in the vertical slices using -1 as a delimiter
    std::vector<int> verticalCuts;
    std::cout<<"Input vertical cuts then -1 at the end" <<std::endl;
    while ((std::cin >> input) && input != -1)
        verticalCuts.push_back(input);

    /// Read in the horizontal slices using -1 as a delimiter
    std::vector<int> horizontalCuts;
    std::cout<<"Input horizontal cuts then -1 at the end" <<std::endl;
    while (std::cin >> input && input != -1)
        horizontalCuts.push_back(input);

    std::cout << "The maximum slice size is " << maxArea(h, w, horizontalCuts, verticalCuts);

    return 0;
}



