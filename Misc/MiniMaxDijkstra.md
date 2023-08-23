This is a variant of Dijkstra where you have find maximum of the minimum(or vice versa).
The application of these kind of problem is Shortest bottleneck or Widest Path problem.

**Shortest Bottleneck**:
Here we have to find a path with shortest bottleneck
```
if d[v] > max(d[u], w) 
     d[v] = max(d[u], w) 
```
In the same below graph, path 1-2-3 has hurdle of 3 (maximum of minimum hurdle)  
while 1-2-5 has hurdle of 5  
So it is better to go via 1-2-3 which has less hurdle.  

Practice Problem: https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/

**Widest Path**:
Suppose this graph represent network bandwidth, what is best path ?
1-2-3 minimum we can transfer is 1 (minimum of all path weight) 
1-2-5 minimum we can transfer is 2
So the maximum of both is 2 , so we select 1-2-5 , as that give higher bandwidth.
```
if d[v] < min(d[u], w) 
     d[v] = min(d[u], w) 
```
![image](https://github.com/c0D3M/Graph_Algorithms/assets/20656683/f417be3c-390b-4c28-8489-0580170b0e07)

Image Courtsey: GFG
