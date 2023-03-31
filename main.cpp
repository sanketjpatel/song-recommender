/*  main.cpp
 *  Author: Sanket Patel
 *  Date: 03/30/2023
 */
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "song-recommender.hpp"

using namespace std;

int main()
{
    int T;
    vector<vector<string>> resultsNaive;
    vector<vector<string>> resultsRankBased;
    const string inputFilePath = "resources/input.txt";
    const string outputNaiveFilePath = "resources/output-cpp-naive.txt";
    const string outputRankBasedFilePath = "resources/output-cpp-rank-based.txt";

    fstream inputFile;
    inputFile.open(inputFilePath, ios::in);
    if (inputFile.is_open())
    {
        string t;
        getline(inputFile, t);
        T = stoi(t);
        // Loop through each test case and calculate its results
        for (int i = 0; i < T; i++)
        {
            vector<set<string>> knownPreferences;
            set<string> givenPreference;
            tie(knownPreferences, givenPreference) = getPreferences(inputFile);
            resultsNaive.push_back(recommendSongsNaive(knownPreferences, givenPreference));
            resultsRankBased.push_back(recommendSongsRankBased(knownPreferences, givenPreference));
        }
        inputFile.close();
    }

    fstream outputNaiveFile;
    outputNaiveFile.open(outputNaiveFilePath, ios::out);
    if (outputNaiveFile.is_open())
    {
        for (auto const &result : resultsNaive)
        {
            for (auto const &song : result)
            {
                outputNaiveFile << song << ' ';
            }
            outputNaiveFile << endl;
        }
        outputNaiveFile.close();
    }

    fstream outputRankBasedFile;
    outputRankBasedFile.open(outputRankBasedFilePath, ios::out);
    if (outputRankBasedFile.is_open())
    {
        for (auto const &result : resultsRankBased)
        {
            for (auto const &song : result)
            {
                outputRankBasedFile << song << ' ';
            }
            outputRankBasedFile << endl;
        }
        outputRankBasedFile.close();
    }

    return 0;
}