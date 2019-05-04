#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#define ONE_BASE // use this to define if input uses nodes start from 1, default 0-based nodes
/*
 * Topological Sort: returns lex-smallest ordering
 * Input: DAG
*/

using std::vector;
using std::pair;
using std::stack;
bool sortBySize(vector<int> a, vector<int> b)
{
	return a.size() > b.size();
}
size_t n, m;
vector<bool> visited;
stack<int> nodes;
vector< pair<int, int>> inDegree; // node index and its inDegree;
void toposort(vector<vector<int> > &adj, int s) {
	for(int i=0; i<adj[s].size(); i++)
	{
		if(!visited[adj[s][i]])
			toposort(adj, adj[s][i]);
	}
	// Push the node on stack if either its leaf nodes or all its branch nodes are visited.
	nodes.push(s); 
	visited[s] = true; // Mark the node as visited
}
bool sortByDegree(pair<int , int> a, pair<int, int> b)
{
	if(a.second==b.second) // same in degree
	   return a.first > b.first; // return smaller index first
	else
		a.second < b.second;
}
int main() {
  std::cin >> n >> m;
  visited.reserve(n);
  inDegree.reserve(n);
  for (int i=0; i< n;i++)
  {
	  pair<int, int> t;
	  t.first = i;
	  t.second =0;
	  inDegree.push_back(t);
  }
  visited.assign(n, 0);
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
	#ifdef ONE_BASE
		adj[x-1].push_back(y-1);
		inDegree[y-1].second++;
	#else
		adj[x].push_back(y);
		inDegree[y].second++;
	#endif
  }
  for (int i =0; i< n; i++) // Sort adjList of each node in decreasing order.
	sort(adj[i].begin(), adj[i].end(), std::greater<int>());
	  
  // This sorting decide which node to begin with, nodes with least inDegree should start first
  // in case of tie, the one with least index should be processed last. This is lex-smallest topological ordering
  sort(inDegree.begin(), inDegree.end(), sortByDegree);
  for(int i=0; i<n; i++)
	  if(!visited[inDegree[i].first])
			toposort(adj, inDegree[i].first);
  
  for(int i=0; i<n; i++)
  {
	#ifdef ONE_BASE
	 std::cout <<nodes.top()+1<<" ";
	#else
	 std::cout <<nodes.top()<<" ";
	#endif
	nodes.pop();
  }
}