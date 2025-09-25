#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

const int INF = INT_MAX;

int n;
vector<vector<int>> dist;
int bestCost = INF;
vector<int> bestPath;

int reduceMatrix(vector<vector<int>>& matrix, vector<int>& rowRed, vector<int>& colRed) {
    int cost = 0;
    for (int i = 0; i < n; i++) {
        rowRed[i] = INF;
        for (int j = 0; j < n; j++)
            rowRed[i] = min(rowRed[i], matrix[i][j]);
        if (rowRed[i] != INF && rowRed[i] != 0) {
            cost += rowRed[i];
            for (int j = 0; j < n; j++)
                if (matrix[i][j] != INF)
                    matrix[i][j] -= rowRed[i];
        }
    }

    for (int j = 0; j < n; j++) {
        colRed[j] = INF;
        for (int i = 0; i < n; i++)
            colRed[j] = min(colRed[j], matrix[i][j]);
        if (colRed[j] != INF && colRed[j] != 0) {
            cost += colRed[j];
            for (int i = 0; i < n; i++)
                if (matrix[i][j] != INF)
                    matrix[i][j] -= colRed[j];
        }
    }
    return cost;
}

void tspBranchAndBound(vector<vector<int>> matrix, vector<bool> visited, vector<int> path, int level, int cost, int bound) {
    if (level == n) {
        if (dist[path.back()][path[0]] != INF) {
            int totalCost = cost + dist[path.back()][path[0]];
            if (totalCost < bestCost) {
                bestCost = totalCost;
                bestPath = path;
                bestPath.push_back(path[0]);
            }
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && matrix[path.back()][i] != INF) {
            vector<vector<int>> tempMatrix = matrix;
            for (int j = 0; j < n; j++) {
                tempMatrix[path.back()][j] = INF;
                tempMatrix[j][i] = INF;
            }
            tempMatrix[i][path[0]] = INF;

            vector<int> rowRed(n), colRed(n);
            int reductionCost = reduceMatrix(tempMatrix, rowRed, colRed);
            int newCost = cost + matrix[path.back()][i] + reductionCost;

            if (newCost < bestCost) {
                visited[i] = true;
                path.push_back(i);
                tspBranchAndBound(tempMatrix, visited, path, level + 1, cost + matrix[path[level - 1]][i], bound + reductionCost);
                path.pop_back();
                visited[i] = false;
            }
        }
    }
}

int main()
{
    dist = {
        {INF, 10, 15, 20},
        {10, INF, 35, 25},
        {15, 35, INF, 30},
        {20, 25, 30, INF}
    };

    n = dist.size();
    vector<vector<int>> initialMatrix = dist;
    vector<int> rowRed(n), colRed(n);
    int bound = reduceMatrix(initialMatrix, rowRed, colRed);

    vector<bool> visited(n, false);
    visited[0] = true;
    vector<int> path = {0};

    tspBranchAndBound(initialMatrix, visited, path, 1, 0, bound);

    cout << "Minimum cost: " << bestCost << endl;
    cout << "Path: ";
    for (int city : bestPath)
        cout << city << " ";
    cout << endl;

    return 0;
}

