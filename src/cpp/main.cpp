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

void writeResults(const string &filepath, const vector<vector<string>> &results)
{
    fstream outputFile;
    outputFile.open(filepath, ios::out);
    if (outputFile.is_open())
    {
        for (auto &recommendations : results)
        {
            writeRecommendations(outputFile, recommendations);
        }
        outputFile.close();
    }
}

int main()
{
    int T;
    vector<vector<string>> resultsNaive;
    vector<vector<string>> resultsRankBased;
    const string inputFilePath = "resources/input.txt";

    const string outputNaiveFilePath = "outputs/output-cpp-naive.txt";
    const string outputRankBasedFilePath = "outputs/output-cpp-rank-based.txt";

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

    writeResults(outputNaiveFilePath, resultsNaive);
    writeResults(outputRankBasedFilePath, resultsRankBased);

    return 0;
}