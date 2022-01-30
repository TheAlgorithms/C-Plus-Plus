#include <iostream>
#include <string.h>
#include <unordered_map>
#include <utility>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <vector>

using namespace std;

//pulled from: https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
//generate a random string of a certain length
string gen_random(const int len)
{
    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
    {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

pair<string, double> HCS(double penalty, string first, string second,
                         unordered_map<char, double> weights)
{
    int str1_len = first.length();
    int str2_len = second.length();

    // this array is going to hold the suffixes and their weights
    pair<string, double> HCS_arr[str1_len + 1][str2_len + 1];

    pair<string, double> hcs("", 0.0); //heaviest common substring

    for (int i = 0; i <= str1_len; i++)
    {
        for (int j = 0; j <= str2_len; j++)
        {
            if (i == 0 || j == 0)
            {
                HCS_arr[i][j].first = "";
                HCS_arr[i][j].second = 0;
                continue; // skip the rest
            }

            HCS_arr[i][j].first = HCS_arr[i - 1][j - 1].first + first.at(i - 1);
            //default to adding characters from the first string in case of mismatch

            // if the characters match add the weight
            if (first.at(i - 1) == second.at(j - 1))
            {
                HCS_arr[i][j].second = HCS_arr[i - 1][j - 1].second + weights[first.at(i - 1)];
            }
            // if they don't match subtract the penalty
            else
            {
                HCS_arr[i][j].second = HCS_arr[i - 1][j - 1].second - penalty;
            }
            // updating the heaviest substring
            if (HCS_arr[i][j].second > hcs.second)
            {
                hcs = HCS_arr[i][j];
            }
        }
    }
    return hcs;
}

void getFreqencies(unordered_map<char, double> &weights)
{
    //frequencies pulled from https://www3.nd.edu/~busiforc/handouts/cryptography/letterfrequencies.html
    //based off the frequencies of letters in the english language
    weights['E'] = 11.1607;
    weights['A'] = 8.4966;
    weights['R'] = 7.5809;
    weights['I'] = 7.5448;
    weights['O'] = 7.1635;
    weights['T'] = 6.9509;
    weights['N'] = 6.6544;
    weights['S'] = 5.7351;
    weights['L'] = 5.4893;
    weights['C'] = 4.5388;
    weights['U'] = 3.6308;
    weights['D'] = 3.3844;
    weights['P'] = 3.1671;
    weights['M'] = 3.0129;
    weights['H'] = 3.0034;
    weights['G'] = 2.4705;
    weights['B'] = 2.0720;
    weights['F'] = 1.8121;
    weights['Y'] = 1.7779;
    weights['W'] = 1.2899;
    weights['K'] = 1.1016;
    weights['V'] = 1.0074;
    weights['X'] = 0.2902;
    weights['Z'] = 0.2722;
    weights['J'] = 0.1965;
    weights['Q'] = 0.1962;
}

double average(vector<double> weights)
{
    double total = 0;
    for (double i : weights)
    {
        total += i;
    }
    return (total / weights.size());
}

int main()
{
    srand (static_cast <unsigned> (time(0)));
    unordered_map<char, double> weights;
    vector<pair<int, double>> times;
    vector<double> for_averages;

    for (char c = 'A'; c <= 'Z'; c++)
    {
        weights[c] = 1.0; // setting all characters with a weight of 1
    }

    //it seems that since the penalty is so much higher than the weight, the best common substring is usually
    //just the first letter they have in common becuase any mismatch after that destroys 10 letters.

    cout << "Testing with all weights = 1 and penalty = 10..." << endl;

    for (unsigned int i = 1; i < 250; i += 2)
    {
        auto start = chrono::high_resolution_clock::now();
        pair<string, double> hcs = HCS(10.0, gen_random(i), gen_random(i), weights);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        times.push_back(make_pair(i, duration.count()));
        for_averages.push_back(hcs.second);
    }
    cout << "Average weight of HCS with all weights = 1 and penalty = 10: " << average(for_averages) << endl;
    cout << "Testing with all weights = 1 and penalty = 10 complete.\n" << endl;

    weights.clear();
    times.clear();
    for_averages.clear();

    getFreqencies(weights);

    for (double penalty = .1962; penalty < 11.1607; penalty += 1)
    {
        cout << "Testing with frequency-weights and penalty = " << penalty << "..." << endl;

        for (unsigned int i = 1; i < 250; i += 2)
        {
            auto start = chrono::high_resolution_clock::now();
            pair<string, double> hcs = HCS(penalty, gen_random(i), gen_random(i), weights);
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            times.push_back(make_pair(i, duration.count()));
            for_averages.push_back(hcs.second);
        }
        cout << "Average weight of HCS with frequency-weights and penalty = " << to_string(penalty) << ": " 
        << average(for_averages) << endl;
        cout << "Testing with frequency-weights and penalty = " << penalty << " complete.\n" << endl;
        times.clear();
        for_averages.clear();
    }

    cout << "Testing with frequency-weights and penalty = 11.1607..." << endl;
    for (unsigned int i = 1; i < 250; i += 2)
    {
        auto start = chrono::high_resolution_clock::now();
        pair<string, double> hcs = HCS(11.1607, gen_random(i), gen_random(i), weights);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        times.push_back(make_pair(i, duration.count()));
        for_averages.push_back(hcs.second);
    }
    cout << "Average weight of HCS with frequency-weights and penalty = 11.1607: " << average(for_averages) << endl;
    cout << "Testing with frequency-weights and penalty = 11.1607 complete." << endl;
    times.clear();
    for_averages.clear();
    return 0;
}
