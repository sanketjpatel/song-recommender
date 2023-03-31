# Song Recommender

You are given a list of song preferences by existing users.
A new user has a list of song preferences.
Recommend songs to this new user.

## Input

First line represents T, the number of test cases.

Each test case consists for N + 2 lines.

First line of a test case represents N, the existing number of users.

Next N lines represent the list of song preferences of each of those existing users.

Last line of a test case represents the song preferences of the new user.

## Expected Output

T lines.

Each line represents the list of recommended songs to be given to the new user for a test case.

Order of the songs in the output is important. First song in the list is the one with highest score.

## Example:

Say your input is
```
1
3
A B C D
B C D
C D E
B C
```
First line says you are going to run `1` test case.

Second line says you have `3` existing users.

Their song preferences are as follows:
```
User 1: [A, B, C, D]
User 2: [B, C, D]
User 3: [C, D, E]
```
The song preferences of the new user are: `[B, C]`

Your output should be the following
```
D A
```

Explanation:
`User1` and `User2` have the songs `B` and `C` in their favorites lists.

So we can recommend songs `A` and `D` to the new user. The order in which we recommend the songs is important. Song `D` belongs to both of `User1` and `User2`'s preferences, however song `A` only belongs to `User1`'s preference list.

Hence, we first recommend `D`, and then recommend `A`.

# Solution

The naive approach that meets the expected output is detailed in [Naive.md](docs/Naive.md).

You can have [a more realistic recommender](docs/RankBased.md) algorithm that combines the correlation score of a preference set and assigns rank to the recommended songs based on these correlations.

# Contributing

Please submit issues/pull requests and we can collaborate :smile:

Cheers!
