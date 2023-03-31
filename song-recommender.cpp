/*  Song Recommender
 *  Author: Sanket Patel
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <set>
#include <vector>
#include <map>

using namespace std;

// Function to return a set of songs from a string separated by a delimiter
set<string> createPreferenceSet(const string &line, const char delim)
{
    set<string> preferenceSet;

    stringstream ss(line);
    string song;
    while (getline(ss, song, delim))
    {
        preferenceSet.insert(song);
    }
    return preferenceSet;
}

bool valueComparatorDescending(pair<string, int> &key_val_a,
                               pair<string, int> &key_val_b)
{
    return key_val_b.second < key_val_a.second;
}

// Function to sort the keys in a map based on their values, returns a vector of keys.
vector<string> sortKeysByValue(map<string, int> &countMap, bool (*comparator)(pair<string, int> &, pair<string, int> &))
{
    // Declare vector of pairs
    vector<pair<string, int>> entries;

    // Copy key-value pair from Map to vector of pairs
    for (auto &entry : countMap)
    {
        entries.push_back(entry);
    }

    // Sort using comparator function
    sort(entries.begin(), entries.end(), comparator);

    vector<string> result;

    // Print the sorted value
    for (auto &entry : entries)
    {
        result.push_back(entry.first);
    }
    return result;
}

vector<string> recommendSongs(const vector<set<string>> &knownPreferences, const set<string> &givenPreference)
{
    map<string, int> songCount;
    for (auto const &preference : knownPreferences)
    {
        if (includes(preference.begin(), preference.end(),
                     givenPreference.begin(), givenPreference.end()))
        {

            vector<string> recommendedSongs;
            set_difference(preference.begin(), preference.end(), givenPreference.begin(), givenPreference.end(), back_inserter(recommendedSongs));

            for (auto const &song : recommendedSongs)
            {
                songCount[song] += 1;
            }
        }
    }
    vector<string> result = sortKeysByValue(songCount, valueComparatorDescending);

    return result;
}

tuple<vector<set<string>>, set<string>> getPreferences(fstream &inputFile)
{
    vector<set<string>> knownPreferences;

    string temp;
    getline(inputFile, temp);
    int N = stoi(temp);

    for (int i = 0; i < N; i++)
    {
        getline(inputFile, temp);
        knownPreferences.push_back(createPreferenceSet(temp, ' '));
    }

    getline(inputFile, temp);
    set<string> givenPreference = createPreferenceSet(temp, ' ');

    return tuple(knownPreferences, givenPreference);
}

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
    if (outputNaiveFile.is_open()) {
        for (auto const& result: results) {
            for (auto const& song: result) {
                outputNaiveFile << song << ' ';
            }
            outputNaiveFile << endl;
        }
    }

    return 0;
}