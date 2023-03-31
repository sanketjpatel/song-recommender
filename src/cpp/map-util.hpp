#ifndef MAP_UTIL_HPP
#define MAP_UTIL_HPP
#include <map>
#include <vector>

template <typename K, typename V>
const bool valueComparatorDescending(const std::pair<K, V> &key_val_a,
                                     const std::pair<K, V> &key_val_b)
{
    return key_val_a.second > key_val_b.second;
}

template <typename K, typename V>
std::vector<K> sortKeys(std::map<K, V> &keyValueMap, const bool (*comparator)(const std::pair<K, V> &, const std::pair<K, V> &))
{
    std::vector<std::pair<K, V>> entries;
    for (auto &entry : keyValueMap)
    {
        entries.push_back(entry);
    }

    sort(entries.begin(), entries.end(), comparator);

    std::vector<K> result;
    for (auto &entry : entries)
    {
        result.push_back(entry.first);
    }
    return result;
}

#endif