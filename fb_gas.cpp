#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
int main(int argc, char*argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n , m;
	cin >> n >> m;
	vector<vector<pair<int, int>>> adj(n+1);
	for(int i = 1; i<=m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back(make_pair(v, w) );
	}
	// source city is 1 and destination is n;
	// graph state will be cost and whether coupon available to use or not.
	priority_queue< pair<long long, pair<int, bool>>, vector<pair<long long, pair<int, bool>>> > pq;
	pq.push(make_pair(0, make_pair(1, true)));// cost to reach is 0 and we are at 1st node and coupon can be used
	vector<vector<long long>> dist (1+n, vector<long long>(2, LLONG_MAX));
	dist[1][0] = 0; // to reach first city without coupon
	dist[1][1] = 0;// to reach first city with coupon
	while(!pq.empty())
	{
		int u = pq.top().second.first;
		bool coupon_available = pq.top().second.second;
		pq.pop();
		
		for(size_t i = 0; i < adj[u].size(); ++i)
		{
			int v = adj[u][i].first;
			int w = adj[u][i].second;
			// Without coupon travel
			if(dist[v][coupon_available] > dist[u][coupon_available] + w)
			{
				dist[v][coupon_available] = dist[u][coupon_available] + w;
				pq.push(make_pair(-(dist[u][coupon_available] + w), make_pair( v, coupon_available)));
			}
			
			// With coupon travel
			if(coupon_available and (dist[v][0] > dist[u][1] + w/2))
			{
				dist[v][0] = dist[u][1] + w/2;
				pq.push(make_pair(-(dist[u][1] + w/2), make_pair( v, false)));
			}
		}
	}
	cout << min(dist[n][0], dist[n][1]) << "\n";
}
