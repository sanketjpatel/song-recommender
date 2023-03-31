#ifndef SONG_RECOMMENDER_HPP
#define SONG_RECOMMENDER_HPP

#include <tuple>
#include <vector>
#include <set>
#include <string>
#include <fstream>

std::set<std::string> createPreferenceSet(const std::string &line, const char delim);
std::tuple<std::vector<std::set<std::string>>, std::set<std::string>> getPreferences(std::fstream &inputFile);
std::vector<std::string> recommendSongsNaive(const std::vector<std::set<std::string>> &knownPreferences, const std::set<std::string> &givenPreference);
std::vector<std::string> recommendSongsRankBased(const std::vector<std::set<std::string>> &knownPreferences, const std::set<std::string> &givenPreference);
void writeRecommendations(std::fstream &outputFile, std::vector<std::string> &recommendations);

#endif