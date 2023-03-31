# Solution using a rank based approach

Treat each user's preference list as a set.

Compare an existing preference set with the new user's preference set to calculate its correlation score. If the existing set is a superset of new user's preferences, the correlation score is `1`. Otherwise, it is `0`.

<details>
  <summary>Calculating Correlation for expected output</summary>
  

  ### song-recommender.cpp
  ```cpp
// ...

float calculateCorrelationFactor(const std::set<std::string> &existingPreference, const std::set<std::string> &newUserPreference)
{
    if (includes(existingPreference.begin(), existingPreference.end(),
                 newUserPreference.begin(), newUserPreference.end()))
    {
        return 1.0;
    }
    return 0;
}

// ...
```
</details>
<br>

Create a map of the recommended songs, with their scores based on the correlation scores of each preference set.
<details>
  <summary>Calculating scores for recommended songs</summary>
  

  ### song-recommender.cpp
  ```cpp
// ...
// Create a map of recommended songs, with their scores
    std::map<std::string, float> songScores;
    for (auto const &preference : knownPreferences)
    {
        float correlationFactor = calculateCorrelationFactor(preference, givenPreference);
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
// ...
   ```
</details>
<br>

Return a vector of songs, sorted by their scores in the above map.

<br>

## Avoiding the limitation in Naive Approach

If the given preference set of the new user is large, it is likely that none of the existing preferences are a superset. Thereby, rendering no recommendations.

Let's see this with following example input:
```
3
A B C D
B C D
C D E
B C X Y Z
```

There will be no songs recommended to the new user.

However, we can slightly tweak how the correlation factor is calculated.
For an existing user's preference, 

`correlation = (no. of songs from existing user's preference in new user's preferences) / (no. of songs in new user's preferences)`

This gives us the following for the new user's preferences of `B C X Y Z`

| Preferences     | Matching Songs | CorrelationFactor |
| --------------- | -------------- | ----------------- | 
| A B C D         | B C            | 0.4               |
| B C D           | B C            | 0.4               |
| C D E           | C              | 0.2               |

Scores for recommended songs will now be the following:

| Song | Score |
| ---- | ----- |
| D    | 0.8   |
| A    | 0.4   |
| E    | 0.2   |

Thus the output will now be - `D A E`

<details>
  <summary>Snippet for calculating this CorrelationFactor</summary>
  

  ### song-recommender.cpp
  ```cpp
// ...

float calculateCorrelationFactor(const std::set<std::string> &existingPreference, const std::set<std::string> &newUserPreference)
{
    int matchingSongCount = 0;
    for(auto const& song: existingPreference) {
        if (newUserPreference.find(song) != newUserPreference.end()) {
            matchingSongCount++;
        }
    }
    return (float)matchingSongCount/(float)newUserPreference.size();
}

// ...
```
</details>
<br>

# Future Work

Instead of having a preference set for a user, we could have a map of songs with their corresponding scores for a given user.
This score could be based on attributes like genre, number of times played, etc.

The correlationFactor will now be calculated from maps with song scores, instead of the sets.

People are diverse. Why not make our recommendation engine more inclusive? :smile:
