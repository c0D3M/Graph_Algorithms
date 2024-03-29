# Graph_Algorithms
Algorithms related to graphs  
This repository contains exercise algorithms  from Coursera Course on Graph.  
https://www.coursera.org/learn/algorithms-on-graphs/home/welcome  
Completed course with 83.33 %.  

TODO:  
- TLE on Negative cycle shortest path problem.  
- Optional Advance section (A* , Contraction Hirerachy, TSP).  
- Transtive Closure.  

BFS vs SPFA: Both are exactly same and uses queue to push relaxed nodes, but in BFS we never visit a node again while in SPFA we can visit.  
BFS is technically suitable for uniform cost edges(unweight graph), like edges of cost 1, BSF finds minimum edges to reach a node.  
It only consider minimum number of edges, NOT COST!  

To practice BFS/DFS/Dijkstra/Bellmand Ford/Flyod Warshall/SPFA in a single problem  
https://leetcode.com/problems/network-delay-time/  

Algroithm | #Description | #Time Complexity | #Space Complexity | #Misc  
--- | --- | --- | --- |---  
Dijkstra | Single Source Shortest Path for weighted graph  | O(_(V +  E) log V_) and for dense graph O(_E log V_)| O( _V_  ) | cant work on grah with -ve edges.  
Bellman Ford | Single Source Shortest path with -ve edges | O( _V_ **.** _E_ ) | O( _V_  ) | https://leetcode.com/problems/cheapest-flights-within-k-stops/description/  Handle -ve edges and can also find -ve cycle.  
Shortes Path faster Algorithm(SPFA) | Single Source Shortest path with -ve edges | O( _V_ **.** _E_ ) | O( _V_  ) | Unlike Bellmand Ford , this uses a queue to ush only those nodes which are relax and if they are not already in queue.  Above problem can be solved using SPFA also.  
Johnson Algorithm | All Pair Shortest Path | 283 | 290 | Works betters in sparse graph as it uses Bellman-Ford and Dijsktra.  
Fllyod-Warshall | All Pair Shortest Path | O( _V_ ^3 ) | 290 | typically used in dense graph.  
Kahn Algorithm | Topological Sort | O( _V_ + _E_ ) | 290 |  
Kruskal Algorithm | Minimum Spanning Tree | O( _V_ + _E_ ) | 290 |  
Prim Algorithm | Minimum Spanning Tree | O( _V_ + _E_ ) | 290 |  
Hierholzer's Algroithm  | Euler Path in a graph | | | https://www.youtube.com/watch?v=8MpoO2zA2l4  Practice: https://leetcode.com/problems/valid-arrangement-of-pairs/   
Tarjan Algorithm | For finding SCC in directed graph | 283 | 290 | https://www.youtube.com/watch?v=wUgWX0nc4NY For undirected graph we use SCC but for directed we cant use that as a directed edge is in different.  Practice: https://leetcode.com/problems/number-of-provinces/  
Tarjan Algorithm | For finding bridges and articulation point | | | https://codeforces.com/blog/entry/71146 https://www.youtube.com/watch?v=64KK9K4RpKE Practice:  https://leetcode.com/problems/critical-connections-in-a-network/  
Johnson All Simple cycle | For finding all cycles  | 283 | 290 | A SCC can contain multiple elementary cycle.
Bipartite test | 301 | 283 | 290 | Color the Graph with 2 color if possible its bi-partite
Hungarain Algorithm | Maximum Matching |  |  | Bipartite + Weighted  https://brilliant.org/wiki/hungarian-matching/   
Blosson Algorithm | Maximum Matching |  |  | Unweighted + Non-bipartite, like we used Christofide Algorithm for TSP.     https://brilliant.org/wiki/blossom-algorithm/  
Hopcroft Karp | Maximum Matching |  |  | Unweighted + Bipartite  https://brilliant.org/wiki/hopcroft-karp/   
Edmond-Karp Algorithm | Max-Flow | O( _V_ + _E_ ) | 290 | Augmented Path 
Dinic Algorithm | Max-Flow | O( _V_ + _E_ ) | 290 | Augmented Path, Another class of algorithm for max flow uses push-relabel.   

Euler Cycle: Visit each edge exactly once and end on same node where it start. Possibly if graph has even degree.  
To find a cycle then start from any node.  
If there is a Euler cycle there would be Euler Path also but reverse is not true.  

Euler Path: May start and end on different node.  
For undirected graph, atmost 2 node can have odd degree.  
For directed graph, at most 1 node has outDgree-inDgree =1(start node) and inDegree - outDegree=1 (end node).  
Hierholzer's Algorithm is used to find an Euler Path.  https://leetcode.com/problems/valid-arrangement-of-pairs/  
https://leetcode.com/problems/reconstruct-itinerary/description/  


Hamiltonian Cycle: It's a NP-Hard problem to find if a cycle exists or not.  
