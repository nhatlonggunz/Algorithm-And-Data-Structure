#include <bits/stdc++.h>
using namespace std;
#define ii pair<int, int>
#define fi first
#define se second
#define maxN long(1e4) + 10
int n, m, src, res = -1;
vector<ii> g[maxN];
vector<int> d;
vector<bool> inQueue;

void input()
{
	int u, v, t;
	scanf("%d%d%d", &n, &m, &src);

	while(m--)
	{
		scanf("%d%d%d", &u, &v, &t);
		g[u].push_back(ii(v, t));
		g[v].push_back(ii(u, t));
	}
}

void SPFA()
{
	int u; ii v;
	queue<int> q;
	d.assign(n + 1, long(1e9));
	inQueue.assign(n + 1, false);

	d[src] = 0; inQueue[src] = true;
	q.push(src);

	while(!q.empty())
	{
		u = q.front(), inQueue[u] = false, q.pop();

		for(unsigned i = 0; i < g[u].size(); i++)
		{
			v = g[u][i];
			if(d[v.fi] > d[u] + v.se)
			{
				d[v.fi] = d[u] + v.se;

				if(!inQueue[v.fi])
				{
					q.push(v.fi);
					inQueue[v.fi] = true;
				}
			}
		}
	}
}

int main()
{
	input();
	SPFA();

	for(int i = 1; i <= n; i++) res = max(res, d[i]);

	printf("%d", res*2);
		
	return 0;
}
