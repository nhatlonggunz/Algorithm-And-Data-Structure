#include <iostream>
#include <vector>
using namespace std;

class DisjointSet
{
	private: vector<int> r, p;
	public:
		DisjointSet(int n)
		{
			r.assign(n + 1, 0);
			p.assign(n + 1, 0);
			for(int i = 1; i <= n; i++) p[i] = i;
		}
		int Find(int x) { return x == p[x] ? x : (p[x] = Find(p[x])); }
		bool isSameSet(int x, int y) { return Find(x) == Find(y); }
		void Union(int x, int y)
		{
			x = Find(x), y = Find(y);
			
			if(r[x] < r[y]) { p[x] = y; }
			else{
				p[y] = x;
				if(r[x] == r[y]) r[x]++;
			}
		}
};
