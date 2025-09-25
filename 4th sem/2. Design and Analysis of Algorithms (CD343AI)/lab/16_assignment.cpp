#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Node
{
    vector<bool> assigned;
    int cost, workerID, jobID;
    vector<vector<int>> costMatrix;

    int calculateBound()
    {
        int bound = cost;
        int n = costMatrix.size();

        for (int i = workerID + 1; i < n; ++i) {
            int minCost = INT_MAX;
            for (int j = 0; j < n; ++j) {
                if (!assigned[j])
                    minCost = min(minCost, costMatrix[i][j]);
            }
            bound += minCost;
        }

        return bound;
    }

    bool operator>(const Node& other) const
    {
        return cost > other.cost;
    }
};

struct Compare
{
    bool operator()(const Node& a, const Node& b) {
        return a.calculateBound() > b.calculateBound();
    }
};

int solveAssignment(vector<vector<int>>& costMatrix)
{
    int n = costMatrix.size();
    priority_queue<Node, vector<Node>, Compare> pq;

    Node root;
    root.assigned = vector<bool>(n, false);
    root.cost = 0;
    root.workerID = -1;
    root.costMatrix = costMatrix;

    pq.push(root);
    int minCost = INT_MAX;

    while (!pq.empty()) {
        Node minNode = pq.top();
        pq.pop();

        int i = minNode.workerID + 1;

        if (i == n) {
            minCost = min(minCost, minNode.cost);
            continue;
        }

        for (int j = 0; j < n; ++j) {
            if (!minNode.assigned[j]) {
                Node child = minNode;
                child.workerID = i;
                child.jobID = j;
                child.cost += costMatrix[i][j];
                child.assigned[j] = true;

                if (child.cost < minCost)
                    pq.push(child);
            }
        }
    }

    return minCost;
}

int main() {
    vector<vector<int>> costMatrix = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };

    int result = solveAssignment(costMatrix);
    cout << "Minimum cost using Branch and Bound: " << result << endl;

    return 0;
}

