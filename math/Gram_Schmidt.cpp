#include <iostream>
#include <cassert>
#include <cmath>
#include <array>

/*
    dot_product() function. Storing maths vector in Array
    and calculating it here.
*/

double dot_product(std::array<double, 10> &x, std::array<double, 10> &y,
                   int c) {
  double sum = 0;
  for (int i = 0; i < c; i++) {
    sum += x[i] * y[i];
  }
  return sum;
}

/*
    The dot product of two vectors is taken and the norm of the second vector
    is taken. Then, dot product value is divided by the norm and stored in
   factor.
    Then, multiply that factor with every element in a third vector, whose
   initial values are
    same as the 2nd vector. This vector will then be the projection of 2nd
   vector over 1st vector.
 */

void projection(std::array<double, 10> &x, std::array<double, 10> &y,
                std::array<double, 10> &temp, int c) {
  double dot = dot_product(x, y, c);
  double anorm = dot_product(y, y, c);
  double factor = dot / anorm;
  for (int i = 0; i < c; i++) {
    temp[i] = y[i] * factor;
  }
}

/*
   Function to print the orthogonalised vector
 */

void display(int r, int c, std::array<std::array<double, 10>, 20> &B) {
  for (int i = 0; i < r; i++) {
    std::cout << "Vector " << i + 1 << ": ";
    for (int j = 0; j < c; j++) {
      std::cout << B[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

/*
   Function for the process of Gram Schimdt Process.
   First, we check whether appropriate dimensions are given or not.
   Then, we take a second 2-D array. This will store orthogonalised vectors
   of the input vectors.
   First vector is copied as it is. Then, from 2nd vector onwards,
   we take the projection with all the previous vector and add them.
   Then, twe subtract total projection vector from the input vector
 */

void gram_schmidt(int r, int c, std::array<std::array<double, 10>, 20> &A,
                  std::array<std::array<double, 10>, 20> &B) {
  if (c < r) {
    std::cout
        << "Dimension of vector is less than number of vector, hence \n first "
        << c << " vectors are orthogonalised" << std::endl;
    r = c;
  }

  int k = 1;

  while (k <= r) {
    if (k == 1) {
      for (int j = 0; j < c; j++) B[0][j] = A[0][j];
    }

    else {
      std::array<double, 10> all_projection;
      for (int i = 0; i < c; i++) {
        all_projection[i] = 0;
      }

      int l = 1;
      while (l < k) {
        std::array<double, 10> temp;
        projection(A[k - 1], B[l - 1], temp, c);
        for (int j = 0; j < c; j++) {
          all_projection[j] = all_projection[j] + temp[j];
        }
        l++;
      }
      for (int i = 0; i < c; i++) {
        B[k - 1][i] = A[k - 1][i] - all_projection[i];
      }
    }
    k++;
  }
  display(r, c, B);
}

static void test() {
  std::array<std::array<double, 10>, 20> a1 = {
      {{1, 0, 1, 0}, {1, 1, 1, 1}, {0, 1, 2, 1}}};
  std::array<std::array<double, 10>, 20> b1 = {{0}};
  double dot1;
  gram_schmidt(3, 4, a1, b1);
  int flag = 1;
  for (int i = 0; i < 2; i++)
    for (int j = i + 1; j < 3; j++) {
      dot1 = fabs(dot_product(b1[i], b1[j], 4));
      if (dot1 > 0.1) {
        flag = 0;
        break;
      }
    }
  if (flag == 0) std::cout << "Vectors are linearly dependent " << std::endl;
  assert(flag == 1);
  std::cout << "Passed Test Case 1 " << std::endl;

  std::array<std::array<double, 10>, 20> a2 = {{{3, 1}, {2, 2}}};
  std::array<std::array<double, 10>, 20> b2 = {{0}};
  double dot2;
  gram_schmidt(2, 2, a2, b2);
  flag = 1;
  for (int i = 0; i < 1; i++)
    for (int j = i + 1; j < 2; j++) {
      dot2 = fabs(dot_product(b2[i], b2[j], 2));
      if (dot2 > 0.1) {
        flag = 0;
        break;
      }
    }
  if (flag == 0) std::cout << "Vectors are linearly dependent " << std::endl;
  assert(flag == 1);
  std::cout << "Passed Test Case 2 " << std::endl;

  std::array<std::array<double, 10>, 20> a3 = {{{1, 2, 2}, {-4, 3, 2}}};
  std::array<std::array<double, 10>, 20> b3 = {{0}};
  double dot3;
  gram_schmidt(2, 3, a3, b3);
  flag = 1;
  for (int i = 0; i < 1; i++)
    for (int j = i + 1; j < 2; j++) {
      dot3 = fabs(dot_product(b3[i], b3[j], 3));
      if (dot3 > 0.1) {
        flag = 0;
        break;
      }
    }
  if (flag == 0) std::cout << "Vectors are linearly dependent " << std::endl;
  assert(flag == 1);
  std::cout << "Passed Test Case 3 " << std::endl;
}

int main() {
  int r, c;
  test();
  std::cout << "Enter the dimension of your vectors" << std::endl;
  std::cin >> c;
  std::cout << "Enter the number of vectors you will enter " << std::endl;
  std::cin >> r;

  std::array<std::array<double, 10>, 20>
      A;  // a 2-D array for storing all vectors
  std::array<std::array<double, 10>, 20> B = {
      {0}};  // a 2-D array for storing orthogonalised vectors
  // storing vectors in array A
  for (int i = 0; i < r; i++) {
    std::cout << "Enter vector " << i + 1 << std::endl;
    for (int j = 0; j < c; j++) {
      std::cout << "Value " << j + 1 << "th of vector: ";
      std::cin >> A[i][j];
    }
    std::cout << std::endl;
  }

  gram_schmidt(r, c, A, B);

  double dot = 0;
  int flag = 1;
  for (int i = 0; i < r - 1; i++) {
    for (int j = i + 1; j < r; j++) {
      dot = fabs(dot_product(B[i], B[j], c));
      if (dot > 1) {
        flag = 0;
        break;
      }
    }
  }
  if (flag == 0) std::cout << "Vectors are linearly dependent " << std::endl;
}
