# Solution using a rank based approach

Treat each user's preference list as a set.

Compare an existing preference set with the new user's preference set to calculate its correlation score.

Create a map of the recommended songs, with their scores based on the correlation scores of each preference set.

Return a vector of songs, sorted by their scores in the above map.

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

# Future Work

Instead of having a preference set for a user, we could have a map of songs with their corresponding scores for a given user.
This score could be based on attributes like genre, number of times played, etc.

The correlationFactor will now be calculated from maps with song scores, instead of the sets.

People are diverse. Why not make our recommendation engine more inclusive? :smile:
