#include <iostream>
#include <vector>

using namespace std;

/* function to takes boolean the matrix of
    [i, j] is true if there is a road between from i to j */
bool hamilton_cycle(bool **routes, int n){
    int height = 1 << n, width = n;
    bool dp[(1 << n)][n];
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            dp[i][j] = false;
        }
    }

    dp[1][0] = true;
    for (int i=1; i<height; i++){
        vector <int> zeros, ones;
        /* finding positions with 1s and 0s and separate them */
        for (int pos=0; pos < width; ++pos){
            if ((1 << pos) & i){
                ones.push_back(pos);
            } else {
                zeros.push_back(pos);
            }
        }

        for (int pos = 0; pos < ones.size(); ++pos){
            int o = ones[pos];
            if (!dp[i][o])
                continue;

            for (int inner_pos = 0; inner_pos < zeros.size(); inner_pos++){
                int z = zeros[inner_pos];
                if (!routes[o][z])
                    continue;
                dp[i + (1 << z)][z] = 1;
            }
        }
    }

    bool is_cycle = false;
    for (int i=0; i<width; i++){
        is_cycle |= dp[height - 1][i];
    }
    return is_cycle;
}