#include <bits/stdc++.h>
#include <algorithm>
/* Finding all elementary cycle in directed graph using Johnson Algorithm
   Time Complexity = O((n+1) (V+E)) where n is number of cycles.
*/
using namespace std;
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
class AllCycles
{
	vector<vector<int> > adj;
	vector<int> s;          // visited stack
	set<int> blockedSet;   // blocked set
	map<int, int> blockedM;// blocked map
	int startV;            // started Vertex
	vector<vector<int> > result;
	bool dfs(int node);
	public:
	AllCycles(vector<vector<int> > adj);
	void findCycles(void);
	vector<vector<int> > getCycles(void);
	
};

// All cycles using Johnson Algorithm
AllCycles::AllCycles(vector<vector<int> > t_adj)
{
	adj = t_adj;
}
vector<vector<int> >  AllCycles::getCycles(void)
{
	return result;
}
bool AllCycles::dfs(int node)
{
	bool cycle = false;
	if(node==startV)
	{
		//found a cycle
		s.push_back(node);
		cycle = true;
		result.push_back(s);
		s.pop_back();
	}
	else if(blockedSet.find(node)==blockedSet.end())
	{
		s.push_back(node);
		blockedSet.insert(node);
		for( auto &j:adj[node]) // explore neighbors
			cycle |= dfs(j);
		
		if(cycle)
		{
			blockedSet.erase(node);
			auto it = blockedM.find(node);
			while(it!=blockedM.end())
			{
				node = it->second;
				blockedSet.erase(node); // Remove from blocked set
				blockedM.erase(it);// Remove the blocked map entry 
				it = blockedM.find(node);
			}
		}
		else
		{
			// add all neighbors to blocked map, key will be neighbors and value will be this node.
			for( auto &j:adj[node])
				blockedM.insert(make_pair(j, node));
		}
		s.pop_back();// pop from stack
	}
	return cycle;
		
}
void AllCycles::findCycles(void)
{
	for (int i=0; i < adj.size(); i++)
	{
		if(!adj[i].size())
			continue;
			startV = i;
			s.push_back(i);
			blockedSet.insert(i);
			for( auto &j:adj[i])
				dfs(j);
			blockedSet.erase(i);
			s.pop_back();
			// Now remove node i from graph , any edge incident on i to be remove.
			for (int j =i +1; j < adj.size() && adj[j].size()!=0; j++)
			{
				auto it = find(adj[j].begin(), adj[j].end(), i);
				if(it!=adj[j].end())
					adj[j].erase(it);
			}
	}
}

int main() 
{
	int offset = 0;
	#ifdef OFFSET // If the graph node input start with 1 , define this variable and recompile
		offset = 1;
	#endif
	size_t n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for (size_t i = 0; i < m; i++) 
	{
		int x, y;
		std::cin >> x >> y;
		adj[x-offset].push_back(y-offset);
	}
	
	// For a directed graph , cycles must be contained in a strongly connected component(scc).
	// Find SCC for given directed graph.
	SCC s(adj);
	s.buildSCC();
	
	// For each SCC run Johnson Algorithm
	vector<vector<int> > r = s.getSCC();// get all SCC
	for (int k=0; k< r.size(); k++)
	{
		int n_r = r[k].size();
		if(n_r==1) // SCC with just 1 node has no cycle.
			continue;
		
		// Create a sub-graph adjacency list
		vector<vector<int> > t_adj(n, vector<int>());
		for (int i=0; i< r[k].size(); i++) // r[k][i] identifies a unique node in scc
		{
			t_adj [r[k][i]] = adj[r[k][i]];
			for(auto it = t_adj[r[k][i]].begin(); it != t_adj[r[k][i]].end();)
				if(find(r[k].begin(), r[k].end(), *it)==r[k].end()) // If node doesn't exist in SCC , delete from adj list
					it = t_adj[r[k][i]].erase(it);
				else
					++it;
		}
		//Print sub-graph
		#if 0
		for (auto &i:t_adj)
		{
			if(!i.size()) 
				continue;
			
			for (auto &j: i)
				cout << j<<" ";
			cout<<"\n";
		}
		cout <<"\n";		 
		#endif
		
		// Start Johnson Algorithm			
		AllCycles c(t_adj);
		c.findCycles();
		
		for(auto i:c.getCycles())
		{
			for (auto j:i)
				cout <<j+offset<<" ";
			cout <<"\n";
		}
	}
}