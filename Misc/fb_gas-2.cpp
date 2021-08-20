#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
int main(int argc, char*argv[])
{
	int t;
	cin >> t;
	for(int i =1; i<=t; ++i)
	{
		int n, m, s, t;
		cin >> n >> m >> s>> t;
		vector<vector<long long>> adj(1+n);
		vector<long long> p(n+1); // cost matrix
		for(int i =1; i <=n ; ++i)
		{
			int u;
			cin >> u >> p[i];
			if(u)
			{
				adj[u].push_back(i);
				adj[i].push_back(u);
			}
		}
		// key is cheapest cost and value is (node, fuel)
		priority_queue<pair<long long, pair<long long, long long>>, vector<pair<long long, pair<long long, long long>>>> pq;
		pq.push(make_pair(0, make_pair(s, m)));
		vector<vector<long long>> d(1+n, vector<long long>(1+m, LLONG_MAX));
		d[s][m] = 0; // price reach s with m fuel tank is 0, start node
		while(!pq.empty())
		{
			int u = pq.top().second.first;
			long long f = pq.top().second.second;
			pq.pop();
			
			// Each node is 1 unit away but do we have enough fuel ?
			if(f>=1)
			for(size_t i =0; i < adj[u].size(); ++i)
			{
				
				int v = adj[u][i];
				if(d[v][f-1] > d[u][f] )
				{
					d[v][f-1] = d[u][f];
					pq.push(make_pair(-d[v][f-1], make_pair(v , f-1) ));
				}
			}
			// 2nd option is remain at this node and fill up if possible?
			if(f < m)
			{
				// Fuel station is available ?
				if(p[u] and (d[u][f+1] > d[u][f]+p[u]))
				{
					d[u][m] = d[u][f]+p[u];
					pq.push(make_pair(-d[u][m], make_pair(u, m)));
				}
			}
		}
		long long ans = LLONG_MAX;
		for(int i = 0; i <=m ; ++i)
			ans = min(ans, d[t][i]); 
		if(ans==LLONG_MAX)
			cout <<"Case #" << i <<": "<< -1<<"\n"; 
		else
			cout <<"Case #" << i <<": "<<ans<<"\n"; 
	}
}