#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }
};

FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

int max_flow(FlowGraph& graph, int s, int t, vector<int> &matching) {
    int flow = 0;
    
	//Edmond Karp Algorithm
	while(1)
	{
		
		map<int, pair<int, int>> parent;
		parent[s].first = -1;
		parent[t].first = -1;
		queue<int> q; // BFS Queue
		set<int>  v;  // Visited Set
		q.push(s);
		while(!q.empty())
		{
			if(parent[t].first!=-1)
				break;
			int current = q.front();
			q.pop();
			v.insert(current);

			for( auto & i:graph.get_ids(current))
			{
				FlowGraph::Edge e = graph.get_edge(i);
				// Vertex is unvisited && capacity > flow  && sink is !found
				if((v.find(e.to)==v.end()) && (e.capacity > e.flow) && (parent[t].first==-1))
				{
					q.push(e.to);
					parent[e.to].first  = current;
					parent[e.to].second = i;
					v.insert(e.to);
				}
			}
		}
		if(parent[t].first!=-1) // we found a augmented path
		{
			
			// Find minimum flow of the augmented path
			int min_flow = INFINITY;
			int start =t;
			do{
				FlowGraph::Edge e = graph.get_edge(parent[start].second);
				min_flow = min(min_flow, e.capacity-e.flow);
				start = e.from;
			}while(start !=s);
			// Update Graph and residual
			start =t;
			//printf("Path: ");
			do{
				FlowGraph::Edge e = graph.get_edge(parent[start].second);
				graph.add_flow(parent[start].second, min_flow);
				//printf("%d ", e.from);
				#if 0
				if((e.to != t) && (e.from!=s))
				{
					//printf("%d -> %d \n", e.from, e.to-matching.size()-1);
					matching[e.from-1] = e.to-matching.size()-1;
				}
				#endif
				start = e.from;
			}while(start !=s);
			//printf("\n");
			flow += min_flow;
		}
		else // No Augmented path found break;
			break;
	}
	
	for (int i =1 ; i <= matching.size(); i++)
	{
		for (auto &j:graph.get_ids(i))
			if(graph.get_edge(j).flow) // if their is flow
				matching[graph.get_edge(j).from-1] = graph.get_edge(j).to-matching.size()-1;
	}
    return flow;
}

class MaxMatching {
 public:
  void Solve() {
    vector<vector<bool>> adj_matrix = ReadData();
    vector<int> matching = FindMatching(adj_matrix);
    WriteResponse(matching);
  }

 private:
  vector<vector<bool>> ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    return adj_matrix;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }

  vector<int> FindMatching(const vector<vector<bool>>& adj_matrix) {

	vector<int> matching(adj_matrix.size(), -1);
	// Convert  to G` i.e. add s & table
	int n = 2 + adj_matrix.size()+ adj_matrix[0].size();
	FlowGraph  g(n);
	
	for (int i=0; i< adj_matrix.size(); i++)
	{
		// For each left connect to s
		g.add_edge(0, i+1, 1); 
		for (int j=0; j < adj_matrix[0].size(); j++)
			if(adj_matrix[i][j])
				g.add_edge(i+1, 1+adj_matrix.size()+j, 1);
	}
	// Add each right to t
	for (int j=0; j < adj_matrix[0].size(); j++)
		g.add_edge(1+adj_matrix.size()+j, n-1, 1);
	max_flow(g, 0, g.size() - 1, matching);

		
    return matching;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}
