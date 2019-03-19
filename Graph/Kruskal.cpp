#include <iostream>
#include <vector>
using namespace std;
#define ii pair<int,int> 
#define fi first
#define se second
int n, wei;
vector<pair<int,ii> > edge;
vector<ii> MST;

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
		void isSameSet(int x, int y) { return Find(x) == Find(y); }
		void Union(int x, int y)
		{
			x = Find(x), y = Find(y);
			
			if(r[x] < r[y]) { p[x] = y; }
			else{
				p[y] = x;
				if(r[x] == r[y]) r[x]++;
			}
		}
}

void input()
{
	int m, a, b, w;
	
	cin >> n >> m;
	
	while(m--)
	{
		cin >> a >> b >> w;
		edge.push_back(make_pair(w, ii(a, b));
	}
	sort(edge.begin(), edge.end());
}

void Kruskal()
{
	int cnt = 0; DisjointSet UF(n);
	
	for(unsigned i = 0; i < edge.size(); i++)
		if(!isSameSet(edge[i].se.fi, edge[i].se.se))
		{
			UF.Union(edge[i].se.fi, edge[i].se.se);
			MST.push_back(ii(edge[i].se.fi, edge[i].se.se));
			wei += edge[i].fi;
			if(++cnt == n - 1) break;
		}
}

int main()
{
	input();
	Kruskal();
	return 0;
}