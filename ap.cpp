#include <bits/stdc++.h>
#include <algorithm>
/*
Articulation Point  algorithm using Tarjan's Algorithm 
Vertex by disconnecting that , increases SCC
Root node > 2 children is AP.
*/
struct N
{
	N()
	{
		index = lowlink = -1;
		outEdge = 0;
	}
	int index;
	int lowlink;
	int outEdge;
};
using namespace std;
class AP
{
	vector<struct N> n; // Graph node
	vector<vector<int> > adj;
	int index ; // free index
	vector<int> res; //result containing AP list
	vector<pair<int, int> > bridge;// to-from nodes of bridges where low-link value differs
	vector<bool> visited;
	
	public:
	AP(vector<vector<int> > adj); // construct the class with # of nodes
	void findAP(void); // pass adjacency list and it return AP list
	vector<int> getAP(void);
	vector<pair<int, int> > getBridge(void);
	void dfs(int root, int at, int parent);
};
AP::AP(vector<vector<int> > a)
{
	adj = a;
	index =0;  // initialize the index 
	//populate nodes.
	n.reserve(a.size());
	visited.reserve(a.size());
	visited.assign(a.size(), 0);
	for (unsigned int i=0; i<a.size(); i++)
	{
		N t;
		n.push_back(t);
	}
}
void AP::dfs(int root, int at, int parent)
{
	visited[at] = true;
	if(root==parent)
		n[parent].outEdge++;
	n[at].index = n[at].lowlink = index++;
	for(int i=0; i< adj[at].size(); i++)
	{
		if(adj[at][i]==parent)
			continue;
		if(!visited[adj[at][i]])
		{
			dfs(root, adj[at][i], at);
			n[at].lowlink = min(n[at].lowlink, n[adj[at][i]].lowlink); // Upon return update lowlink value
			if((parent==-1) && (n[at].outEdge>1)) // If the root node, only add a AP if child >1
				res.push_back(at);
			if((parent!=-1) && (n[at].index <= n[adj[at][i]].lowlink))
				res.push_back(at);
			if(n[at].index < n[adj[at][i]].lowlink)
				bridge.push_back(make_pair(at, adj[at][i]));
		}
		else
			n[at].lowlink = min(n[at].lowlink, n[adj[at][i]].index); // Found a cycle
		
	}
}
void AP::findAP(void)
{
	for (unsigned int i=0; i<adj.size() ; i++)
	{
		if(!visited[i])
			dfs(i, i, -1);
	}
	sort(res.begin(), res.end()); 
	sort(bridge.begin(), bridge.end()); 
}
vector<int>  AP::getAP(void)
{
	return res;
}
vector<pair<int, int> > AP::getBridge(void)
{
	return bridge;
}
int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
	adj[x].push_back(y);
	adj[y].push_back(x);
  }
  AP s(adj);
  s.findAP();
  
  vector<int> a = s.getAP();
  cout << a.size()<<"\n";;
  for (auto &i:a)
	  cout<<i<<" ";
  cout<<"\n";
  
  vector<pair<int, int> > b = s.getBridge();
  cout<< b.size()<<"\n";;
  for (auto &i:b)
	  cout<<i.first<<" "<<i.second<<"\n";;
}