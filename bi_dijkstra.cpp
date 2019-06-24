#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
/*
 * Bi-directional Dijkstra Algorithm
 * Input format is based on Course Graph Assignment Week_6
 */
typedef enum
{
    FORWARD, REVERSE
} direction;
#define MAX 2
typedef unsigned long long ull;
class Compare
{
public:
    bool operator()(pair<int, int> a, pair<int, int> b)
    {
        return a.second > b.second;
    }
};
class BiDijkstra
{
private:
    int n; // nodes
    int m; // edges
    vector<double> dist[MAX]; //Distance of each node from s,t
    vector<int> prev[MAX]; //Path trace
    set<int> proc[MAX]; // Processed set
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq[MAX]; // Priority Q
    vector<vector<int> > G[MAX]; // Adj List
    vector<vector<int> > cost[MAX]; // Cost
public:
    BiDijkstra(int n, int m)
    {
        this->n = n;
        this->m = m;
        //Adjacency List
        G[FORWARD].assign(n, vector<int>());
        G[REVERSE].assign(n, vector<int>());

        //Adjacency List
        cost[FORWARD].assign(n, vector<int>());
        cost[REVERSE].assign(n, vector<int>());

        dist[FORWARD].assign(n, INFINITY);
        dist[REVERSE].assign(n, INFINITY);

        prev[FORWARD].assign(n, -1);
        prev[REVERSE].assign(n, -1);
    }
    void Reset()
    {
        pq[FORWARD] = priority_queue<pair<int, int>, vector<pair<int, int>>,
                Compare>(); // reset it
        pq[REVERSE] = priority_queue<pair<int, int>, vector<pair<int, int>>,
                Compare>(); // reset it

        proc[FORWARD].clear();
        proc[REVERSE].clear();

        dist[FORWARD].assign(n, INFINITY);
        dist[REVERSE].assign(n, INFINITY);
    }
    void AddNode(int s, int t, int w)
    {
        G[FORWARD][s - 1].push_back(t - 1);
        G[REVERSE][t - 1].push_back(s - 1);
        cost[FORWARD][s - 1].push_back(w);
        cost[REVERSE][t - 1].push_back(w);
    }
    void Process(int node, direction d)
    {
        for (int i = 0; i < G[d][node].size(); i++)
        {
            if (dist[d][G[d][node][i]] > (dist[d][node] + cost[d][node][i])) //Relax
            {
                dist[d][G[d][node][i]] = (dist[d][node] + cost[d][node][i]);
                pq[d].push(make_pair(G[d][node][i], dist[d][G[d][node][i]]));
            }
        }
        proc[d].insert(node);
    }
    int ShortestPath()
    {
        //Logic for set union
        vector<int> v(proc[FORWARD].size() + proc[REVERSE].size());
        vector<int>::iterator it;
        it = set_union(proc[FORWARD].begin(), proc[FORWARD].end(),
                proc[REVERSE].begin(), proc[REVERSE].end(), v.begin());
        v.resize(it - v.begin());

        double distance = INFINITY;
        int u_best = -1;
        for (auto &i : v)
        {
            if ((dist[FORWARD][i] + dist[REVERSE][i]) < distance)
            {
                u_best = i;
                distance = (dist[FORWARD][i] + dist[REVERSE][i]);
            }
        }
        return distance;
    }
    int FindPath(int s, int t)
    {
        dist[FORWARD][s] = 0;
        dist[REVERSE][t] = 0;
        pq[FORWARD].push(make_pair(s, 0));
        pq[REVERSE].push(make_pair(t, 0));
        while (pq[FORWARD].size() && pq[REVERSE].size())
        {
            for (int i = FORWARD; i < MAX; i++)
            {
                direction d = static_cast<direction>(i);
                //ExtractMin
                int n = pq[i].top().first;
                pq[i].pop();
                Process(n, d);
                bool other = (d == FORWARD) ? 1 : 0;
                if (proc[other].find(n) != proc[other].end()) // Found in other-set
                    return ShortestPath();
            }
        }
        return -1;
    }
};
int main()
{
    int n, m;
    std::cin >> n >> m;
    BiDijkstra b(n, m);
    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        b.AddNode(x, y, w);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int s, t;
        cin >> s >> t;
        cout << b.FindPath(s - 1, t - 1) << "\n";
        b.Reset();
    }
}
