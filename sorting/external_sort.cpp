/**
 * C++ program to sort a file data using external sorting
 * External sorting is required when the data being sorted do not fit into the
 * memory (RAM)
 */

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

using namespace std;

// buff data which fit in memory to sort
constexpr auto BUFF_SIZE = 100000;

struct ChunkFile {
    ifstream file;
    int currentVal;
    string line;
};

/**
   Prepare 1M rows data (int) data being sorted and write to text file.
 */
void mockData() {
    cout << "Preparing data" << endl;

    // change to absolutely path if u want
    ofstream data_file("data.txt", ofstream::trunc);  // overwite

    // use to get a random number
    mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(0, 999999);

    for (int i = 0; i < 1000000; i++) {
        // do random number
        int randomNumber = distribution(generator);
        data_file << randomNumber << "\n";
    }
    data_file.close();

    cout << "End preparing data" << endl;
}

void externalSort(char* data_file) {
    ifstream input_file(data_file);

    string line;
    int line_number = 0;
    vector<int> chunk;
    vector<string> chunk_file_names;

    cout << "Do sort chunks" << endl;

    // read chunk and sort each chunk
    while (getline(input_file, line)) {
        line_number++;
        // convert line to number and add to chunk
        chunk.push_back(stoi(line));
        if (line_number == BUFF_SIZE) {
            // if have enough buffer data then do sort the chunk
            // note: i am using a built-in <algorithm> sort function,
            // you can use any other in-memory sort algorithms such as bubble
            // sort or quick sort
            sort(chunk.begin(), chunk.end());  // asc

            // write sort result to temporary file. use index as file name
            string temp_file_name = to_string(chunk_file_names.size());
            ofstream data_file(temp_file_name, ofstream::trunc);
            for (int val : chunk) {
                data_file << val << "\n";
            }
            data_file.close();
            chunk_file_names.push_back(temp_file_name);

            chunk.clear();
            line_number = 0;
        }
    }
    // sort the last chunk
    if (line_number != 0) {
        sort(chunk.begin(), chunk.end());

        // write sort result to temporary file. use index as file name
        string temp_file_name = to_string(chunk_file_names.size());
        ofstream data_file(temp_file_name, ofstream::trunc);
        for (int val : chunk) {
            data_file << val << "\n";
        }
        data_file.close();
        chunk_file_names.push_back(temp_file_name);
    }

    cout << "End sort chunks" << endl;
    cout << "Merge sorted chunks using k-way merging" << endl;

    // merge all sorted chunks to the final result, using K-Way merging
    vector<ChunkFile*> chunk_files;

    // change to absolutely path if u want
    ofstream result_file("sort_result.txt", ofstream::trunc);

    // open chunk files and read the first value
    for (string f_name : chunk_file_names) {
        ChunkFile* tmp_chunk_file = new ChunkFile();
        tmp_chunk_file->file = ifstream(f_name);
        getline(tmp_chunk_file->file, tmp_chunk_file->line);
        tmp_chunk_file->currentVal = stoi(tmp_chunk_file->line);
        chunk_files.push_back(tmp_chunk_file);
    }

    while (true) {
        // find min value (asc sort)
        int min_index = 0;

        for (int i = 1; i < chunk_files.size(); i++) {
            if (chunk_files[min_index]->currentVal >
                chunk_files[i]->currentVal) {
                min_index = i;
            }
        }
        // write min value to result
        result_file << chunk_files[min_index]->currentVal << "\n";
        // read new value
        if (getline(chunk_files[min_index]->file,
                    chunk_files[min_index]->line)) {
            chunk_files[min_index]->currentVal =
                stoi(chunk_files[min_index]->line);
        } else {
            delete chunk_files[min_index];
            chunk_files.erase(chunk_files.begin() + min_index);
        }

        // if all files are read, then stop
        if (chunk_files.size() == 0)
            break;
    }

    cout << "End merge sorted chunks" << endl;
    result_file.close();

    // delete temporary files
    for (string temp_file : chunk_file_names) {
        remove(temp_file.c_str());
    }
}

/**
 * Test the sort result. This method only works when the mock data fit in
 * memory. (in most real cases, it doesn't)
 */
void test() {
    cout << "Testing" << endl;

    string line;

    // read all mock data
    vector<int> mock_data;
    ifstream mock_file("data.txt");
    while (getline(mock_file, line)) {
        mock_data.push_back(stoi(line));
    }
    // sort mock data by built-in function
    sort(mock_data.begin(), mock_data.end());

    // read all sorted data
    vector<int> sorted_data;
    ifstream sorted_file("sort_result.txt");
    while (getline(sorted_file, line)) {
        sorted_data.push_back(stoi(line));
    }

    // do compare
    assert(mock_data == sorted_data);

    cout << "Test result: OK" << endl;
}

int main() {
    mockData();
    externalSort("data.txt");
    test();
    return 0;
}