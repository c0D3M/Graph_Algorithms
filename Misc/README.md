**Graph Modelling**  
Can be understood from Page 150 of https://cpbook.net/  
Another good resource is https://codeforces.com/blog/entry/45897  

**CSES 1995**  
https://cses.fi/problemset/task/1195/  
Key idea was to learn graph modelling with additional state.  
Each node also store whether it has been reached with availing discount (0) or not (1).  
If discount is availed then next state can only availed.  
If discount is not availed , then both state transition is possible.  
    Goto next node without availing discount.  
    Goto next node with availing discount.  
~~1 test cases still give TLE but give right answer on my machine in 2 minutes, may be bidirectinal dijkstra to be used.~~
Root cause was early exit in Dijkstra.
Continue if distance of node is lesser than cost i.e. dist[u] < cost  
Exit if we reached destination node, because destination node if processed surely that means it has been relaxed and cheapest cost as we r using PQ.  

**UVA 11367**
https://vjudge.net/problem/UVA-11367  
Another graph modelling problem , same as above , here it can have 'c' state i.e. car can take fuel from [0..c] stations inclusive.  
So at each node we have option to visit neighbour and relax their cost if possible(current fuel capacity is good enough).  
Another option is to fuel up by 1 unit.  
All test cases passes.  

**Fb Hacker Cub 2020 Qualification Round** 
https://www.facebook.com/codingcompetitions/hacker-cup/2020/qualification-round/problems/D1  

Running on Fumes 
Chapter 1 nodes are on x-axis, so we can simply use sliding window of m past station.  
Chapter 2 is like graph, we can do graph modelling.  
Answer is correct till Case 16 ,Case 17 is getting seg fault due to large input.  
But the idea is same as above problems.  

**UVA 10269**
https://vjudge.net/problem/UVA-10269  
Key idea is Mario can zip thru some path of length <=L , now to find these paths one has to run **Fllyod Warshall** Algorithm to find all pair shortes path.  
So first do this and then run **Dijkstra** and model the graph , here the state would be (node,K) i.e. how many time accelration show has been used.  
At each piority queue pop transaction first do normal dijkstra relaxtion and then see if accelaration can be used and select those path (calculated from flyod warshall whose length <=L).  
All test cases passes.  

**1928. Minimum Cost to Reach Destination in Time**  
https://leetcode.com/problems/minimum-cost-to-reach-destination-in-time/  
Here too we are given cost & time, we have reach in least cost to destination.  
Additionally if time surpass a threshold (given as input)  we cannot explore any further.  
Now 2 things can happen, either we found a cheaper cost to next node, in that case take both new_cost & new_time and push in PQ.  
If not see if we get a shorter time path ? if yes push with updated time but same cost as new_cost, this is because we found a cheaper time to next node, however cost we have to take whatever it brings us here.  
All this logic to be done if we are within threshold time.  
Early pruning can be done,
If we encounter a node whose cost as well time is already lesser than current node can relax, return
If we encounter dest node, stop, as surely this is cheapest cost , since our PQ is prioritizing lower cost node first.

**Dijkstra as helper** 
sum time we can use it as sub routine
consider https://leetcode.com/problems/maximum-path-quality-of-a-graph/  
Here we have to come back to src node 0 , so if we wander too far and reach back in stipulated time(given in input decrement as we traverse in graph).  
Then there is no need to explore the DFS and we can do early exit.  

