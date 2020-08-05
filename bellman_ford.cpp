#include <iostream>
#include <vector>
#include <cmath>
using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost)
{
    //write your code here
    vector<double> dist(adj.size(), INFINITY);
    dist[0] = 0;
    bool relax = true;
    for (int i = 1; i <= (adj.size() - 1); i++)
    {
        if (!relax)
            break;
        relax = false;
        for (int j = 0; j < adj.size(); j++)
            for (int k = 0; k < adj[j].size(); k++)
            {
                if (dist[adj[j][k]] > (dist[j] + cost[j][k])) //relax
                {
                    dist[adj[j][k]] = (dist[j] + cost[j][k]);
                    relax = true;
                }
                else if ((dist[adj[j][k]] == INFINITY) && (dist[j] == INFINITY))
                {
                    dist[adj[j][k]] = (cost[j][k]);
                    relax = true;
                }

            }
    }
    if (relax) // V-1 iteration result in relax, so possible negative cycle. Check in last iteration.
        for (int j = 0; j < adj.size(); j++)
            for (int k = 0; k < adj[j].size(); k++)
                if (dist[adj[j][k]] > (dist[j] + cost[j][k])) //relax
                    return 1;
    return 0;
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    vector < vector<int> > adj(n, vector<int>());
    vector < vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cout << negative_cycle(adj, cost);
}
