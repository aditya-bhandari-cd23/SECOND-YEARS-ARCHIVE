#include<iostream>
#include<vector>
using namespace std;

int knapsack(vector<int>& weights, vector<int>& values, int cap)
{
    vector<vector<int>> dp(values.size(), vector<int>(weights.size()));
    for (int i = 1; i <= values.size(); i++)
        for (int j = 1; j <= weights.size(); j++)
            if (j >= weights[i - 1])
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + values[i - 1]);
            else
                dp[i][j] = dp[i - 1][j];
    return dp[values.size()][weights.size()];
}

