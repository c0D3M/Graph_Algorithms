#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#define INDEX 1 //set this to 1 if graph input starts with 1 as first node.
#define UNDIRECTED  // define this to process the input for undirected graph test case
using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
class Compare
{
public:
    bool operator()(pair<int, int> a, pair<int, int> b)
    {
        return a.second > b.second;
    }
};

int distance(vector<vector<int> > &adj, vector<vector<double> > &cost, int s, int t) {
  //write your code her
  vector<double> dist(adj.size(), INFINITY);
  priority_queue<pair<int, int>, vector<pair<int, int>>, Compare>  p;
  p.push(std::make_pair(s, 0));
  dist[s] = 0;
  vector<bool> visited(adj.size(), 0);
  while(!p.empty())
  {
	  int n = p.top().first;
	  p.pop();
	  if(visited[n])
			continue;
	  for(int i =0; i< adj[n].size(); i++)
	  {
		  if(dist[adj[n][i]] > (dist[n] + cost[n][i])) //Relax
		  {
		      dist[adj[n][i]] = (dist[n] + cost[n][i]);
			  p.push(std::make_pair(adj[n][i], dist[adj[n][i]]));
		  }  
	  }
	  visited[n] = true;	
  }
  if(dist[t]!=INFINITY)
	  return dist[t];
  else
	return -1;
}	

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<double> > cost(n, vector<double>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - INDEX].push_back(y - INDEX);
    cost[x - INDEX].push_back(w);
#ifdef UNDIRECTED
	adj[y - INDEX].push_back(x - INDEX);
    cost[y - INDEX].push_back(w);
#endif
  }
  int s, t;
  std::cin >> s >> t;
  s = s - INDEX; 
  t = t - INDEX;
  std::cout << distance(adj, cost, s, t);
}
