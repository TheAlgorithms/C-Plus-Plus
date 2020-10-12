#include <iostream>
#include <cstring>

int main() {
    char str1[] = "DEFBCD";
    char str2[] = "ABDEFJ";
    int i, j, k;
    size_t n = strlen(str1) + 1;
    size_t m = strlen(str2) + 1;
    int a[m][n];

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (i == 0 || j == 0)
                a[i][j] = 0;

            else if (str1[i - 1] == str2[j - 1])
                a[i][j] = a[i - 1][j - 1] + 1;

            else
                a[i][j] = 0;
        }
    }

    /*for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
                std::cout<<a[i][j]<<" ";
            std::cout<< std::endl;
        }*/

    int ma = -1;
    int indi, indj;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (a[i][j] > ma) {
                ma = a[i][j];
                indi = i;
                indj = j;
            }
        }
    }

    std::cout << str1 <<  std::endl;
    std::cout << str2 <<  std::endl;

    std::cout << "longest string size = " << ma /*<<" "<<indi<<" "<<indj*/ << std::endl;
    for (i = indi - 3; i < indi; i++) std::cout << str1[i];
    std::cout <<  std::endl;
}
