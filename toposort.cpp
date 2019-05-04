#include <bits/stdc++.h>
#include <algorithm>
#define ONE_BASE // use this to define if input uses nodes start from 1, default 0-based nodes
/*
 * Topological Sort: returns lex-smallest ordering
 * Input: DAG
*/

using namespace std;
size_t n, m;
vector<int> inDegree; // node index and its inDegree;
priority_queue<int, vector<int>, greater<int>> pq;

void toposort(vector<vector<int> > &adj, int s) 
{
	for(int i=0; i<adj[s].size(); i++)
	{
		{
			inDegree[adj[s][i]]--;
			if(!inDegree[adj[s][i]])
				pq.push(adj[s][i]);
		}
	}
	#ifdef ONE_BASE
	cout <<s+1<<" ";
	#else
		cout <<s<<" ";
	#endif
}
int main() 
{
  std::cin >> n >> m;
  inDegree.reserve(n);
  inDegree.assign(n, 0);
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
	#ifdef ONE_BASE
		adj[x-1].push_back(y-1);
		inDegree[y-1]++;
	#else
		adj[x].push_back(y);
		inDegree[y]++;
	#endif
  }
  // Put nodes with 0 in-degree in priority_queue i.e. nodes with higher value is on top.
  for (int i=0; i< n; i++)
	if(inDegree[i]==0)
		pq.push(i);
  
  if(pq.size()==0)
  {
	  cout <<"Sandro fails."<<"\n";
      return 0;
  }
  while(!pq.empty())
  {
	int t = pq.top();
	pq.pop();
	toposort(adj, t);
  }	  
}