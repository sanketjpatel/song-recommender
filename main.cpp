#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "song-recommender.hpp"

using namespace std;

int main()
{
    int T;
    vector<vector<string>> results;
    const string inputFilePath = "resources/input.txt";
    const string outputNaiveFilePath = "resources/output-cpp-naive.txt";

    fstream inputFile;

    inputFile.open(inputFilePath, ios::in);
    if (inputFile.is_open())
    {
        string t;
        getline(inputFile, t);
        T = stoi(t);
        for (int i = 0; i < T; i++)
        {
            vector<set<string>> knownPreferences;
            set<string> givenPreference;
            tie(knownPreferences, givenPreference) = getPreferences(inputFile);
            results.push_back(recommendSongs(knownPreferences, givenPreference));
        }
        inputFile.close();
    }

    fstream outputNaiveFile;
    outputNaiveFile.open(outputNaiveFilePath, ios::out);
    if (outputNaiveFile.is_open())
    {
        for (auto const &result : results)
        {
            for (auto const &song : result)
            {
                outputNaiveFile << song << ' ';
            }
            outputNaiveFile << endl;
        }
        outputNaiveFile.close();
    }

    return 0;
}