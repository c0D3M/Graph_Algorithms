#include <bits/stdc++.h>
#include <algorithm>
/*
SCC algorithm using Tarjan's Algorithm 
Every vertex is reachable from every other vertex.
every vertex belong to exactly one SCC.
nodes from different SCC cannot be connected.
one SCC can have internally many cycles.
*/
struct N
{
	N()
	{
		index = lowlink = -1;
		onStack = false;
	}
	int index;
	int lowlink;
	bool onStack;
};
using namespace std;
class SCC
{
	vector<struct N> n;
	vector<vector<int> > adj;
	int index ; // free index
	stack<int> s; // stack of nodes been pushed.
	vector<vector<int> > res; //result containing SCC list
	void strongconnect(int i); // recursive call to visit each node 
	
	public:
	SCC(vector<vector<int> > adj); // construct the class with # of nodes
	void buildSCC(void); // pass adjacency list and it return SCC list
	vector<vector<int> > getSCC(void);
};
SCC::SCC(vector<vector<int> > a)
{
	adj = a;
	index =0;  // initialize the index 
	//populate nodes.
	n.reserve(a.size());
	for (unsigned int i=0; i<a.size(); i++)
	{
		N t;
		n.push_back(t);
	}
}
void SCC::strongconnect(int v)
{
	n[v].lowlink = n[v].index = index++; //Assign free index to this node and increment index.
	n[v].onStack = true;
	s.push(v);
	
	// Traverse all the neighbors of this node.
	for (unsigned int i=0; i<adj[v].size(); i++)
	{
		if(n[adj[v][i]].index==-1)// unvisited node, recursive call it.
		{
			strongconnect(adj[v][i]);
			// recursive call assign some lowlink value to univisited node, use that to update mine lowlink value
			n[v].lowlink = std::min(n[v].lowlink, n[adj[v][i]].lowlink);
			
		}
		else if(n[adj[v][i]].onStack)
		{
			n[v].lowlink = std::min(n[v].lowlink, n[adj[v][i]].index);
		}
	}
	
	// If this is root node , pop-up stack
	if(n[v].lowlink == n[v].index)
	{
		vector<int> scc;
		int t;
		do
		{
			t = s.top();
			n[t].onStack = false;
			s.pop();
			scc.push_back(t);
		}while(t!=v);
		std::reverse(scc.begin(), scc.end()); // just reverse the scc so as to start with root node.
		res.push_back(scc);
	}
}
void SCC::buildSCC(void)
{
	for (unsigned int i=0; i<adj.size() ; i++)
		if(n[i].index==-1)
			strongconnect(i);
}
vector<vector<int> >  SCC::getSCC(void)
{
	return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
	adj[x].push_back(y);
  }
  SCC s(adj);
  s.buildSCC();
  std::cout << s.getSCC().size();
}