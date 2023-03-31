/*  song-recommender.cpp
 *  Author: Sanket Patel
 *  Date: 03/30/2023
 */
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <set>
#include <vector>
#include <map>
#include "song-recommender.hpp"

bool valueComparatorDescending(std::pair<std::string, int> &key_val_a,
                               std::pair<std::string, int> &key_val_b);

std::vector<std::string> sortKeysByValue(std::map<std::string, int> &countMap, bool (*comparator)(std::pair<std::string, int> &, std::pair<std::string, int> &));

// Function to return a std::set of songs from a std::string separated by a delimiter
std::set<std::string> createPreferenceSet(const std::string &line, const char delim)
{
    std::set<std::string> preferenceSet;

    std::stringstream ss(line);
    std::string song;
    while (getline(ss, song, delim))
    {
        preferenceSet.insert(song);
    }
    return preferenceSet;
}

bool valueComparatorDescending(std::pair<std::string, int> &key_val_a,
                               std::pair<std::string, int> &key_val_b)
{
    return key_val_b.second < key_val_a.second;
}

// Function to sort the keys in a std::map based on their values, returns a std::vector of keys.
std::vector<std::string> sortKeysByValue(std::map<std::string, int> &countMap, bool (*comparator)(std::pair<std::string, int> &, std::pair<std::string, int> &))
{
    // Declare std::vector of pairs
    std::vector<std::pair<std::string, int>> entries;

    // Copy key-value std::pair from std::map to std::vector of pairs
    for (auto &entry : countMap)
    {
        entries.push_back(entry);
    }

    // Sort using comparator function
    sort(entries.begin(), entries.end(), comparator);

    std::vector<std::string> result;

    // Print the sorted value
    for (auto &entry : entries)
    {
        result.push_back(entry.first);
    }
    return result;
}

std::vector<std::string> recommendSongs(const std::vector<std::set<std::string>> &knownPreferences, const std::set<std::string> &givenPreference)
{
    std::map<std::string, int> songCount;
    for (auto const &preference : knownPreferences)
    {
        if (includes(preference.begin(), preference.end(),
                     givenPreference.begin(), givenPreference.end()))
        {

            std::vector<std::string> recommendedSongs;
            set_difference(preference.begin(), preference.end(), givenPreference.begin(), givenPreference.end(), back_inserter(recommendedSongs));

            for (auto const &song : recommendedSongs)
            {
                songCount[song] += 1;
            }
        }
    }
    std::vector<std::string> result = sortKeysByValue(songCount, valueComparatorDescending);

    return result;
}

std::tuple<std::vector<std::set<std::string>>, std::set<std::string>> getPreferences(std::fstream &inputFile)
{
    std::vector<std::set<std::string>> knownPreferences;

    std::string temp;
    getline(inputFile, temp);
    int N = stoi(temp);

    for (int i = 0; i < N; i++)
    {
        getline(inputFile, temp);
        knownPreferences.push_back(createPreferenceSet(temp, ' '));
    }

    getline(inputFile, temp);
    std::set<std::string> givenPreference = createPreferenceSet(temp, ' ');

    return std::tuple(knownPreferences, givenPreference);
}
