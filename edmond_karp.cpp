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

int max_flow(FlowGraph& graph, int s, int t) {
    int flow = 0;
    /* your code goes here */
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
			do{
				FlowGraph::Edge e = graph.get_edge(parent[start].second);
				graph.add_flow(parent[start].second, min_flow);
				start = e.from;
			}while(start !=s);
			flow += min_flow;
		}
		else // No Augmented path found break;
			break;
	}
    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
