#include <iostream>
#include <vector>
using namespace std;
template<class Type> inline void do_rotate(Type* rotated_matrix, const pair<uint8_t, uint8_t>& position, const unsigned &row, const unsigned &columm, const uint8_t inside_row, const uint8_t inside_columm, const uint8_t rotation_position, const Type* const element) {
        int*rotated_matrix_walker = (rotated_matrix + position.first * columm + (position.second));
        int offset = 1, element_index = -1;
        while (true)
        {
                if (++element_index == rotation_position) {
                        *rotated_matrix_walker = *element;
                        return;
                }
                rotated_matrix_walker += offset;
                if (rotated_matrix + ((position.first * columm) + position.second + inside_columm - 1) == rotated_matrix_walker) offset = columm;
                else if (rotated_matrix + ((position.first * columm) + position.second + ((inside_row - 1) * columm) + inside_columm - 1) == rotated_matrix_walker) offset = -1;
        else if (rotated_matrix + ((position.first * columm) + position.second + ((inside_row - 1) * columm)) == rotated_matrix_walker) offset = -1 * columm;
        }
}
template<class Type> Type* matrix_rotation(Type * const matrix, const unsigned row, const unsigned column, const unsigned rotation) {
        pair<uint8_t, uint8_t> position = make_pair(0, 0);
        Type *rotated_matrix = new Type[row * column];
        int offset = 1;
        int *matrix_walker = matrix;
        uint8_t inside_row = row, inside_column = column;
        int32_t array_lenght(0), element_index(0);
        while (inside_row > 0 && inside_column > 0)
        {
                array_lenght = (2 * inside_column + ((inside_row - 2) * 2));
                do
                {
                        do_rotate(rotated_matrix, position, row, column, inside_row, inside_column, (rotation + element_index) % array_lenght, matrix_walker);
                        matrix_walker += offset;
                        element_index++;
                        if (matrix + ((position.first * column) + position.second + inside_column - 1) == matrix_walker) offset = column;
                        else if (matrix + ((position.first * column) + position.second + ((inside_row - 1) * column) + inside_column - 1) == matrix_walker) offset = -1;
                        else if (matrix + ((position.first * column) + position.second + ((inside_row - 1) * column)) == matrix_walker) offset = -1 * column;
                } while ((matrix + (position.first * column + position.second)) != matrix_walker);
                position.first++;
                position.second++;
                inside_row -= 2;
                inside_column -= 2;
                offset = 1;
                matrix_walker = matrix + (position.first * column) + (position.second);
        }
        return rotated_matrix;
}
int main()
{
    int *matrix = new int[16]{7,20,31,90,9,10,40,8,50,2,70,10,10,20,25,49};
    int*rotated_matrix = matrix_rotation(matrix,4,4,1);
    return 0;
}
