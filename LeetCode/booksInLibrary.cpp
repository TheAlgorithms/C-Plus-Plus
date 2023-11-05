/*Chef has books in the library where the number of pages in the 
ℎi th book is Bi. These numbers are given to you. Chef will allocate all these N books to A students in contiguous order, which means that the student will be allocated a contiguous set of books (ie. 
B j,B j+1, j+k, for some j and k). Every student should be allocated at least one book. Minimize the maximum sum of pages allocated to a student. Find that minimum value.

Input Format
The first line of input will contain a single integer 
T, denoting the number of test cases.
The first line of each test case contains two space-separated integers 
N, A — the number books and students.
The second line of each test case contains 
N space-separated integers 
Output Format
For each test case, output on a new line the answer.*/

#include <iostream>
using namespace std;

bool couldBe(long a[], long students, long result, long noOfBook) {
    long sum = 0;
    long studentsCalculated = 1;
    for (long i = 0; i < noOfBook; i++) {
        if (sum + a[i] <= result) {
            sum += a[i];
        } else {
            studentsCalculated++;
            sum = a[i];
        }
    }
    return studentsCalculated <= students;
}

int main() {
    int T;
    cin >> T;
    while (T != 0) {
        long noOfBook, students;
        cin >> noOfBook >> students;
        long books[noOfBook];
        long min = 0;
        long max = 0;
        for (long i = 0; i < noOfBook; i++) {
            cin >> books[i];
            if (min < books[i]) min = books[i];
            max = max + books[i];
        }
        long result = max;
        while (min <= max) {
            long mid = min + (max - min) / 2;
            if (couldBe(books, students, mid, noOfBook)) {
                result = mid;
                max = mid - 1;
            } else {
                min = mid + 1;
            }
        }
        cout << result << endl;
        T--;
    }
    return 0;
}

