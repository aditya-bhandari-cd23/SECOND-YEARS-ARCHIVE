#include<iostream>
#include<vector>
#include<climits>
using namespace std;

void floydWarshall(vector<vector<int>>& adjMat)
{
    int n = adjMat.size();
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (adjMat[i][k] < INT_MAX && adjMat[k][j] < INT_MAX)
                    adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);
}
