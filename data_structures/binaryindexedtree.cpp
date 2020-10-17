/**
 * Binary Indexed Tree = Fenwick Tree
 */

/*
 * Variables that may be needed
 */
const int MAXIMUMSIZE = 1001;
int bit[MAXIMUMSIZE];
int bit2[MAXIMUMSIZE][MAXIMUMSIZE];

/**
* Updates binary indexed tree by a value
* @param index = index to update
* @param value = value to update by
*/
void update(int index, int value) {
    for (int i = index; i < MAXIMUMSIZE; i += (i & -i)) {
        bit[i] += value;
    }
}

/**
 * Queries sum to index
 * @param index = index to query to
 * @return query to index
 */
int query(int index) {
    int answer = 0;
    for (int i = index; i > 0; i -= (i & -i)) {
        answer += bit[i];
    }
    return answer;
}

/**
 * Queries inclusive sum of two indices
 * @param index1 = lowerbound index
 * @param index2 = upperbound index
 * @return query of inclusive sum between index1 and index2
 */
int query(int index1, int index2) {
    return query(index2) - query(index1 - 1);
}

//2D Binary Indexed Tree

/**
 * Updates binary indexed tree by a value
 * @param indexI = x index to update
 * @param indexJ = y index to update
 * @param value = value to update by
 */
void update(int indexI, int indexJ, int value) {
    for (int i = indexI; i < MAXIMUMSIZE; i += (i & -i)) {
        for (int j = indexJ; j < MAXIMUMSIZE; j += (j & -j)) {
            bit2[i][j] += value;
        }
    }
}

/**
 * Queries sum to index
 * @param indexI = x index to query to
 * @param indexJ = y index to query to
 * @return query to index
 */
int query2D(int indexI, int indexJ) {
    int answer = 0;
    for (int i = indexI; i > 0; i -= (i & -i)) {
        for (int j = indexJ; j > 0; j -= (j & -j)) {
            answer += bit2[i][j];
        }
    }
    return answer;
}

/**
 * Queries inclusive sum of two sets of indices
 * @param indexI1 = lowerbound x index
 * @param indexJ1 = lowerbound y index
 * @param indexI2 = upperbound x index
 * @param indexJ2 = upperbound y index
 * @return query of the inclusive sum of the two sets of indices
 */
int query2D(int indexI1, int indexJ1, int indexI2, int indexJ2) {
    return (query2D(indexI2, indexJ2) + query2D(indexI1 - 1, indexJ1 - 1) - query2D(indexI1 - 1, indexJ2) - query2D(indexI2, indexJ1 - 1));
}
