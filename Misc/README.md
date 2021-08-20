**Graph Modelling**  
Can be understood from Page 150 of https://cpbook.net/  
Another good resource is https://codeforces.com/blog/entry/45897  

**CSES 1995**  
https://cses.fi/problemset/task/1195/  
Key idea was to learn graph modelling with additonal state.  
Each node also store whether it has been reached with availaning discount (0) or not (1).  
If discount is availed then next state can only availed.  
If discount is not availed , then both state transition is possible.  
    Goto next node without availing discount.  
    Goto next node with availing discount.  
1 test cases still give TLE but give right answer, may be bidirectinal dijkstra to be used.  

**UVA 11367**
https://vjudge.net/problem/UVA-11367  
Another graph modelling problem , same as above , here it can have 'c' state i.e. car can take fuel from [0..c] inclusive.  
So at each node we have option to visit  neighbour and relax their cost if possible(current fuel capacity is good enough).  
Another option is to fuel up by 1 unit.  
All test cases passes.  

**Fb Hacker Cub 2020 Qualification Round** 
Running on Fumes 
Chapter 1 nodes are on x-axis, so we can simply use sliding window of m past station.  
Chapter 2 is like graph, we can do graph modelling.  
Answer is correct till Case 16 ,Case 17 is getting seg fault due to large input.  
But the idea is same as above problems.  
