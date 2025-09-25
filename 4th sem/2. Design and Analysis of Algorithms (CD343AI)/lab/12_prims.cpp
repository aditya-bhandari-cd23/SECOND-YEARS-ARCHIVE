#include<iostream>
#include<vector>
using namespace std;

int prim(vector<vector<vector<int>>> adjList, int src = 0)
{
    vector<bool> visited(adjList.size());
    int ans{};
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int node = pq.top().second;
        int weight = pq.top().first;
        pq.pop();
        if (!visited[node]) {
            visited[node] = 1;
            ans += weight;
            for (auto& nbr : adjList[node])
                if (!visited[nbr[0]])
                    pq.push({nbr[1], nbr[0]});
        }
    }
    return ans;
}
