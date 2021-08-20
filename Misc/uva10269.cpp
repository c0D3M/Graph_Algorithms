#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
const int INF = 1e9;
int main(int argc, char*argv[])
{
	int T;
	cin >> T;
	for(int i =1; i<=T; ++i){
		int A, B, M, L, K;
		cin >> A >> B >> M>> L>>K;
		// Total Nodes 
		int N = A + B;
		vector<vector<int>> path(1+N, vector<int>(1+N, INT_MAX));
		vector<vector<pair<int, int>>> adj(1+N);
		for (int i =1 ; i<=M; ++i)
		{
			int u, v, w;
			cin >> u >> v >> w;
			adj[u].push_back(make_pair(v, w));
			adj[v].push_back(make_pair(u, w));
			path[u][v] = path[v][u] = w; // shortest path between adjacent node .
		}
		
		// First Apply Fllyod-Warshall algorithm to get all pair shortest path
		// Since boot can only be used in Villages, use that to calculate min distance
		for(int k = 1 ;  k<=A; ++k)
			for(int i =1; i <= N; ++i)
				for(int j =1; j <= N; ++j)
					if (path [i][k]!= INT_MAX && path [k][j] != INT_MAX)
						path[i][j] = min(path[i][j], path[i][k] + path[k][j]);
		// Now apply dikstra from s=A+B and t =1
		vector<vector<int>> dist(1+N, vector<int>(1 +K, INT_MAX));
		dist[N][0] = 0;
		// Sorted by distance and store (Node, K) k is how many times accelraton show is used
		priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>> > pq;
		pq.push(make_pair(0, make_pair(N, 0))); // when we start from N , we havent used any accelration shoes
		while(!pq.empty())
		{
			int u = pq.top().second.first;
			int k = pq.top().second.second;
			pq.pop();
			
			// Normal mode
			for(size_t i = 0; i < adj[u].size(); ++i)
			{
				int v = adj[u][i].first;
				int w = adj[u][i].second;
				if(dist[v][k] > dist[u][k] + w)
				{
					dist[v][k] = dist[u][k] + w;
					pq.push(make_pair(-dist[v][k], make_pair(v, k)));
				}
			}
			
			// Accelration Mode
			if(k<K) // can we use ?
			{
				// Now here we haev to use path because here we have zip through the villages and select whose size is <=L
				// For current node 'u' what all N node we can go whose path length <=L 
				for(int i = 1; i <=N ; ++i)
					if(i!=u) // exclude self nodee
					{
						if ( (path[u][i] <=L )	and dist[i][k+1] > dist[u][k])
						{
							dist[i][k+1] = dist[u][k];
							pq.push(make_pair(-dist[i][k+1], make_pair(i, k+1)));
						}
					}
			}
		}// while loop of pq ends here
		int ans = INF;
		for (int i = 0; i <= K; i ++)
          ans = min (ans, dist [1] [i]);
		cout <<ans<<"\n";
	}// End of test case loop
	return 0;
}