# Graph_Algorithms
Algorithms related to graphs  
This repository contains exercise algorithms  from Coursera Course on Graph.  
https://www.coursera.org/learn/algorithms-on-graphs/home/welcome  
Completed course with 83.33 %.  

TODO:  
- TLE on Negative cycle shortest path problem.  
- Optional Advance section (A* , Contraction Hirerachy, TSP).  
- Transtive Closure.  


Algroithm | #Description | #Time Complexity | #Space Complexity | #Misc  
--- | --- | --- | --- |---  
Dijkstra | Single Source Shortest Path for weighted graph  | O(_(V +  E) log V_) and for dense graph O(_E log V_)| O( _V_  ) | cant work on grah with -ve edges.  
Bellman Ford | Single Source Shortest path with -ve edges | O( _V_ **.** _E_ ) | O( _V_  ) | Handle -ve edges and can also find -ve cycle.  
Johnson Algorithm | All Pair Shortest Path | 283 | 290 | Works betters in sparse graph as it uses Bellman-Ford and Dijsktra.  
Fllyod-Warshall | All Pair Shortest Path | O( _V_ ^3 ) | 290 | typically used in dense graph.  
Kahn Algorithm | Topological Sort | O( _V_ + _E_ ) | 290 |  
Kruskal Algorithm | Minimum Spanning Tree | O( _V_ + _E_ ) | 290 |  
Prim Algorithm | Minimum Spanning Tree | O( _V_ + _E_ ) | 290 |  
Edmond-Karp Algorithm | Max-Flow | O( _V_ + _E_ ) | 290 | Augmented Path 
Dinic Algorithm | Max-Flow | O( _V_ + _E_ ) | 290 | Augmented Path, Another class of algorithm for max flow uses push-relabl.   
Tarjan Algorithm | For finding SCC in directed graph | 283 | 290 | https://www.youtube.com/watch?v=wUgWX0nc4NY For undirected graph we use SCC but for directed we cant use that as a directed edge is in different.    
Tarjan Algorithm | For finding bridges and articulation point | | | https://codeforces.com/blog/entry/71146 https://www.youtube.com/watch?v=64KK9K4RpKE  
Johnson All Simple cycle | For finding all cycles  | 283 | 290 | A SCC can contain multiple elementary cycle.
Bipartite test | 301 | 283 | 290 | Color the Graph with 2 color if possible its bi-partite
Hungarain Algorithm | Maximum Matching | 283 | 290 | Bipartite + Weighted   
Blosson Algorithm | Maximum Matching | 283 | 290 | Weighted + Non-bipartite, like we used Christofide Algorithm for TSP.     
Hopcroft Karp | Maximum Matching | 283 | 290 | Unweighted + Bipartite   

Euler Cycle: Visit each edge exactly once and end on same node where it start. Possibly if graph has even degree.  
To find a cycle then start from any node.  
If there is a Euler cycle there would be Euler Path also but reverse is not true.  

Euler Path: May start and end on different node.  
For undirected graph, atmost 2 node can have odd degree.  
For directed graph, at most 1 node has outDgree-inDgree =1(start node) and inDegree - outDegree=1 (end node).  
Hierholzer's Algorithm is used to find an Euler Path.  https://leetcode.com/problems/valid-arrangement-of-pairs/  


Hamiltonian Cycle: It's a NP-Hard problem to find if a cycle exists or not.  
