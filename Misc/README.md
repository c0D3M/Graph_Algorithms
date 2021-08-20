CSES 1995  
https://cses.fi/problemset/task/1195/  
Key idea was to learn graph modelling with additonal state.  
Each node also store whether it has been reached with availaning discount (0) or not (1).  
If discount is availed then next state can only availed.  
If discount is not availed , then both state transition is possible.  
    Goto next node without availing discount.  
    Goto next node with availing discount.  
1 test cases still give TLE but give right answer, may be bidirectinal dijkstra to be used.  
