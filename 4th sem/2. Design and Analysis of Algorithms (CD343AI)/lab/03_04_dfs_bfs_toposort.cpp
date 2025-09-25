#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

class Graph
{
    int vertices;
    vector<vector<int>> adjList;

    void bfs(int start, int& cnt, vector<int>& visited)
    {
        queue<int> q;
        q.push(start);
        visited[start] = ++cnt;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int nbr : adjList[v])
                if (!visited[nbr]) {
                    q.push(nbr);
                    visited[nbr] = ++cnt;
                }
        }
    }

    void dfs(int v, int& cnt, vector<int>& visited, stack<int>& stk)
    {
        visited[v] = ++cnt;
        for (int nbr : adjList[v])
            if (!visited[nbr])
                dfs(nbr, cnt, visited, stk);
        stk.push(v);
    }

public:
    Graph(int v) : vertices(v), adjList(v) {}

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        // adjList[v].push_back(u);
    }

    void breadthFirstSearch()
    {
        int cnt{};
        vector<int> visited(vertices);
        for (int v = 0; v < vertices; v++)
            if (!visited[v])
                bfs(v, cnt, visited);

        cout << "BFS order: \n";
        for (int i = 0; i < vertices; i++) 
            cout << "Node " << i << " : " << visited[i] << '\n';
    }

    void topoSort()
    {
        stack<int> stk;
        vector<int> visited(vertices);
        int cnt{};

        for (int v = 0; v < vertices; v++)
            if (!visited[v])
                dfs(v,cnt,visited,stk);

        cout << "Topo sort:\n";
        while (!stk.empty())
            cout << stk.top() << '\n', stk.pop();
    }
};
