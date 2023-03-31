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

// TODO: Convert this to generic templates / use lambdas / std::less
bool valueComparatorDescending(std::pair<std::string, int> &key_val_a,
                               std::pair<std::string, int> &key_val_b);

bool valueComparatorDescending(std::pair<std::string, float> &key_val_a,
                               std::pair<std::string, float> &key_val_b);

std::vector<std::string> sortKeysByValue(std::map<std::string, int> &countMap, bool (*comparator)(std::pair<std::string, int> &, std::pair<std::string, int> &));
std::vector<std::string> sortKeysByValue(std::map<std::string, float> &countMap, bool (*comparator)(std::pair<std::string, float> &, std::pair<std::string, float> &));

// Function to return a set of songs from a string separated by a delimiter
// Input String = "MySong 1,MySong 2,Some song 3"
// Delimiter = ","
// Output Set = ["MySong 1", "MySong 2", "Some song 3"]
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

// If the existing preference set contains all the songs of the new user's preferences, return 1. Otherwise return 0.
// A more advanced correlation factor could evaluate how closely an existing user's preferences and the new user's preference match.
// We could assign scores to the recommended songs based on that.
float calculateCorrelationFactor(const std::set<std::string> &existingPreference, const std::set<std::string> &newUserPreference)
{
    if (includes(existingPreference.begin(), existingPreference.end(),
                 newUserPreference.begin(), newUserPreference.end()))
    {
        return 1.0;
    }
    return 0;
}

float calculateCorrelationFactorMatching(const std::set<std::string> &existingPreference, const std::set<std::string> &newUserPreference)
{
    int matchingSongCount = 0;
    for (auto const &song : existingPreference)
    {
        if (newUserPreference.find(song) != newUserPreference.end())
        {
            matchingSongCount++;
        }
    }
    return (float)matchingSongCount / (float)newUserPreference.size();
}

bool valueComparatorDescending(std::pair<std::string, int> &key_val_a,
                               std::pair<std::string, int> &key_val_b)
{
    return key_val_b.second < key_val_a.second;
}

bool valueComparatorDescending(std::pair<std::string, float> &key_val_a,
                               std::pair<std::string, float> &key_val_b)
{
    return key_val_b.second < key_val_a.second;
}

// Function to sort the keys in a map based on their values, returns a vector of the keys
std::vector<std::string> sortKeysByValue(std::map<std::string, int> &countMap, bool (*comparator)(std::pair<std::string, int> &, std::pair<std::string, int> &))
{
    // Declare a vector of pairs
    std::vector<std::pair<std::string, int>> entries;

    // Copy key,value pair from the map to the vector of pairs
    for (auto &entry : countMap)
    {
        entries.push_back(entry);
    }

    // Sort using the comparator function
    sort(entries.begin(), entries.end(), comparator);

    std::vector<std::string> result;

    // Add keys of the sorted entries to the result
    for (auto &entry : entries)
    {
        result.push_back(entry.first);
    }
    return result;
}

// Function to sort the keys in a map based on their values, returns a vector of keys. Similar to above, but with float values
std::vector<std::string> sortKeysByValue(std::map<std::string, float> &countMap, bool (*comparator)(std::pair<std::string, float> &, std::pair<std::string, float> &))
{
    std::vector<std::pair<std::string, float>> entries;

    for (auto &entry : countMap)
    {
        entries.push_back(entry);
    }

    sort(entries.begin(), entries.end(), comparator);

    std::vector<std::string> result;

    for (auto &entry : entries)
    {
        result.push_back(entry.first);
    }
    return result;
}

std::vector<std::string> recommendSongsNaive(const std::vector<std::set<std::string>> &knownPreferences, const std::set<std::string> &givenPreference)
{
    // Create a map of recommended songs, with their count of occurrences in matched existing preferences
    std::map<std::string, int> songCount;

    for (auto const &preference : knownPreferences)
    {
        // New user's preferences are a subset of this existing preference.
        if (includes(preference.begin(), preference.end(),
                     givenPreference.begin(), givenPreference.end()))
        {
            // Collect all the recommended songs by doing a set difference.
            std::vector<std::string> recommendedSongs;
            set_difference(preference.begin(), preference.end(), givenPreference.begin(), givenPreference.end(), back_inserter(recommendedSongs));

            for (auto const &song : recommendedSongs)
            {
                songCount[song] += 1;
            }
        }
    }
    // Sort the recommended songs based on their count of occurrences.
    return sortKeysByValue(songCount, valueComparatorDescending);
}

std::vector<std::string> recommendSongsRankBased(const std::vector<std::set<std::string>> &knownPreferences, const std::set<std::string> &givenPreference)
{
    // Create a map of recommended songs, with their scores
    std::map<std::string, float> songScores;
    for (auto const &preference : knownPreferences)
    {
        float correlationFactor = calculateCorrelationFactorMatching(preference, givenPreference);
        if (correlationFactor > 0)
        {
            for (const auto &song : preference)
            {
                // A song in the existing preference is not found in the set of new user's preferences.
                if (givenPreference.find(song) == givenPreference.end())
                {
                    // Add the correlation factor to the song's score.
                    songScores[song] += correlationFactor;
                }
            }
        }
    }
    // Sort recommended songs based on their scores.
    return sortKeysByValue(songScores, valueComparatorDescending);
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

void writeRecommendations(std::fstream &outputFile, std::vector<std::string> &recommendations)
{
    for (auto const &song : recommendations)
    {
        outputFile << song << ' ';
    }
    outputFile << std::endl;
}
