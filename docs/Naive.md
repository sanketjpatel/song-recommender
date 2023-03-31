# Solution using Naive approach

Treat each user's preference list as a set.

If the new user's preference list is a subset of any existing set, add all the remaining items from the superset to the recommendations set.

Create a map of the recommended songs, with their count (how many times a recommended song appeared in the matching supersets).

Sort the songs in the results vector based on their counts in the map.

## Limitations

If the given preference set of the new user is large, it is likely that none of the existing preferences are a superset. Thereby, rendering no recommendations. This can be avoided using a [rank based approach](RankBased.md)