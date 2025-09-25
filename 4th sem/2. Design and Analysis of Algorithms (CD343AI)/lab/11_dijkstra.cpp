#include<iostream>
#include<vector>
using namespace std;

vector<int> dijkstra(vector<vector<vector<int>>>& adjList, int vertices, int start)
{
    vector<int> dist(vertices, INT_MAX);
    dist[start] = 0;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        int node = pq.top().second;
        int weight = pq.top().first;
        pq.pop();
        if (weight <= dist[node])
            for (auto& nbr : adjList[node]) {
                int n = nbr[0];
                int w = nbr[1];
                if (dist[node] + w < dist[n]) {
                    dist[n] = dist[node] + w;
                    pq.push({dist[n], n});
                }
            }
    }
    return dist;
}