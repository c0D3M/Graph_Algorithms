#include <bits/stdc++.h>
#include <algorithm>
#define INDEX 1 //set this to 1 if graph input starts with 1 as first node.
//#define UNDIRECTED  // define this to process the input for undirected graph test case

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
    vector<bool> visited[MAX];
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

        visited[FORWARD].assign(n, 0);
        visited[REVERSE].assign(n, 0);
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

        visited[FORWARD].assign(n, 0);
        visited[REVERSE].assign(n, 0);
    }
    void AddNode(int s, int t, int w)
    {
        G[FORWARD][s- INDEX].push_back(t- INDEX);
        G[REVERSE][t- INDEX].push_back(s- INDEX);
        cost[FORWARD][s- INDEX].push_back(w);
        cost[REVERSE][t- INDEX].push_back(w);
#ifdef UNDIRECTED
        G[FORWARD][t- INDEX].push_back(s- INDEX);
        G[REVERSE][s- INDEX].push_back(t- INDEX);
        cost[FORWARD][t- INDEX].push_back(w);
        cost[REVERSE][s- INDEX].push_back(w);
#endif
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
                if (visited[d][n])
                    continue;
                Process(n, d);
                visited[d][n] = true;
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
        s = s - INDEX;
        t = t - INDEX;
        cout << b.FindPath(s, t) << "\n";
        b.Reset();
    }
}
