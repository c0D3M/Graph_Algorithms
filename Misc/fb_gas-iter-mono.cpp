#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
int main(int argc, char*argv[])
{
	int t;
	cin >> t;
	for(int i =1; i<=t; ++i)
	{
		int n, m;
		cin >> n >> m;
		vector<long long> c(n);
		for(int i =0; i < n ; ++i)
			cin >> c[i];
		if(m < n)
		{
			// Mono Stack 
			deque<pair<int, long long>> stk;// Index and cost
			stk.push_back(make_pair(0, 0));
			for(int i =1; i < n ; ++i)
			{
				// is the current tos is out of range (range means M cities )
				if(i - stk.front().first > m)
					stk.pop_front();
				if(stk.empty())
					break;
				if(c[i]==0)
					continue;
				long long new_cost = c[i] + stk.front().second;
				// is this new_cost cheapest among all the m cities cost in stack ?
				while(!stk.empty() and stk.back().second >= new_cost)
					stk.pop_back();
				stk.push_back(make_pair(i, new_cost));
			}
			cout << "Case #" << i<< ": " << (stk.empty() ? -1 : stk.front().second) << "\n";
		}
		else
			cout << "Case #"<<i<<": 0\n";
		
	}
}