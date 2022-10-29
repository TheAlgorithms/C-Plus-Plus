/**
 * @file
 * @brief Implementation of the [External
 * Sort](https://en.wikipedia.org/wiki/External_sorting)
 * @details
 * External sorting is a class of sorting algorithms that can handle massive
 * amounts of data. External sorting is required when the data being sorted do
 * not fit into the main memory of a computing device (usually RAM) and instead
 * they must reside in the slower external memory, usually a disk drive and its
 * time complexity is approximately equal to O(nlogn).
 * @author [Dawood Wasif](https://github.com/dawoodwasif)
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
using namespace std;

class Compare {
 public:
    // Ascending order sort
    bool operator()(pair<int, int> pair1, pair<int, int> pair2) {
        return pair1.first > pair2.first;
    }
};

string ToString(int val) {
    stringstream stream;
    stream << val;
    return stream.str();
}

// merge all sorted files into one
string mergeFiles(int counter) {
    string fileA, fileB;

    std::priority_queue<pair<int, int>, std::vector<pair<int, int> >, Compare>
        minHeap;
    ifstream* handles = new ifstream[counter];

    for (int i = 1; i <= counter; i++) {
        string sortedInputFileName = "output" + ToString(i) + ".txt";
        handles[i - 1].open(sortedInputFileName.c_str());
        int firstValue;
        handles[i - 1] >>
            firstValue;  // first value in the file (minimum in the file)
        minHeap.push(pair<int, int>(
            firstValue, i - 1));  // second value in pair keeps track of the
                                  // file from which the number was drawn
    }

    string outputFileName = "output.txt";
    ofstream outputFile(outputFileName.c_str());

    while (minHeap.size() > 0) {
        pair<int, int> minPair = minHeap.top();
        minHeap.pop();
        outputFile << minPair.first << '\n';
        int nextValue;
        flush(outputFile);
        if (handles[minPair.second] >> nextValue) {
            minHeap.push(pair<int, int>(nextValue, minPair.second));
        }
    }

    // clean up
    for (int i = 1; i <= counter; i++) {
        handles[i - 1].close();
    }
    outputFile.close();
    delete[] handles;  // free memory

    return outputFileName;
}

void sortAndWrite(int* values, int size, int numberOfChunks) {
    sort(values, values + size);
    string outputFileName = "output" + ToString(numberOfChunks) + ".txt";
    ofstream outputFile(outputFileName.c_str());  // output file
    for (int i = 0; i < size; i++) {
        outputFile << values[i] << '\n';
    }
    outputFile.close();
}

int main() {
    // divide file into chunks of size that fits in your memory
    int numberOfChunks = 1;
    int maxSizeofMemory = 32;                       // in bytes
    int chunkSize = maxSizeofMemory / sizeof(int);  //(4 bytes for integer)
    int* inputValues = new int[chunkSize];
    int readValue = 0;
    int currentCount = 0;
    bool unprocessedData = true;
    ifstream inputFile("input.txt");

    while (inputFile >> readValue) {
        unprocessedData = true;
        inputValues[currentCount++] = readValue;
        if (currentCount == chunkSize) {
            sortAndWrite(inputValues, currentCount, numberOfChunks);
            numberOfChunks++;
            currentCount = 0;
            unprocessedData = false;
        }
    }
    if (unprocessedData) {
        sortAndWrite(inputValues, currentCount, numberOfChunks);
    } else {
        numberOfChunks--;
    }

    inputFile.close();
    delete[] inputValues;  // free memory
    if (numberOfChunks != 0) {
        std::priority_queue<pair<int, int>, std::vector<pair<int, int> >,
                            Compare>
            minHeap;
        cout << "output is in file : " << mergeFiles(numberOfChunks);
    }

    return 0;
}