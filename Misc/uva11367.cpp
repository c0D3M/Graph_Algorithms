#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
const int INF = 1e9;
int main(int argc, char*argv[])
{
    
	{
        int n , m;
        cin >> n >> m;
        // Fuel prices of all n cities
        vector<int> p(n);
        for(int i =0; i < n; ++i)
            cin >> p[i];
        
        // Adj List <dest, weight>
        vector<vector<pair<int, int>>> adj(n);
        for(int i =0; i <m; ++i)
        {
            int u, v, w;
            cin >> u >> v>> w;
            adj[u].push_back(make_pair(v, w));
			adj[v].push_back(make_pair(u, w));
        }
        
        int k ; // queries
        cin >> k;
        while(k--)
        {
            int c, s, t; // consumption, source, target
            cin >> c >> s >> t;
            vector<vector<int>> d(n, vector<int>(c+1, INF)); // cost matrix with second state as fuel
            // Initially cost to reach each station with any fuel is INF
            d[s][0] = 0;  // when we start with 0 fuel we spent 0 dollar
            priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>> pq;
            pq.push(make_pair(0, make_pair(s, 0)));// 
            while(!pq.empty())
            {
                // What node we are at and whats the fuel there
                int u = pq.top().second.first;
                int f = pq.top().second.second;
                pq.pop();

                // Now see if you can go to any of your neighbors with this 'f' fuel ?
                for(int i = 0;  i < adj[u].size(); ++i)
                {
                    // What fuel is required to reach 
                    int f_required = adj[u][i].second;
                    if(f_required > f) continue;
                    int v = adj[u][i].first;
                    
                    // relax and push to queue
                    // If the cost to reach v is cheaper with fuel f-f_required ?
                    if(d[v][f-f_required] > d[u][f])
                    {
                        d[v][f-f_required]  = d[u][f];
                        pq.push(make_pair( -d[v][f-f_required], make_pair(v, f-f_required)));
                    }
                }

                // Another option is fuel up 1 unit of gas if we can 
                if((f+1) <= c)
                {
                    if(d[u][f+1] > d[u][f] + p[u])
                    {
                        d[u][f+1] = d[u][f] + p[u];
                        pq.push(make_pair(-d[u][f+1], make_pair(u, f+1)));
                    }
                }
            }
			if(d[t][0]==INF)
				cout <<"impossible\n";
			else
				cout<<d[t][0]<< "\n";
        }// k query loop ends here
    }// Test case loop ends here
    return 0;
}