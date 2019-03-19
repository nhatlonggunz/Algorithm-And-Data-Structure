#include <bits/stdc++.h>
using namespace std;
#define ii pair<int, int>
#define fi first
#define se second
#define maxN long(1e4) + 10
int n, m, src, res = -1;
vector<ii> g[maxN];
vector<int> d, p;
vector<bool> visited;
priority_queue<ii, vector<ii>, greater<ii> > pq;

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

void Dijkstra(int src)
{
    int u; ii v;
    p.assign(n + 1, 0);
    d.assign(n + 1, long(1e9));
    visited.assign(n + 1, false);
    d[src] = 0; pq.push(ii(0, src));

    while(!pq.empty())
    {
        u = pq.top().se;
        if(pq.top().fi > d[u]) { pq.pop(); continue; }
        pq.pop();

        visited[u] = true;

        for(unsigned i = 0; i < g[u].size(); i++)
        {
            v = g[u][i];
            if(!visited[v.fi] && d[v.fi] > d[u] + v.se)
            {
                d[v.fi] = d[u] + v.se;
                p[v.fi] = u;
                pq.push(ii(d[v.fi], v.fi));
            }
        }
    }
}

void trace(int src, int dest)
{
    printf("%d <- ", dest);
    while(p[dest] != src && p[dest])
    {
        dest = p[dest];
        printf("%d <- ", dest);
    }
    printf("%d\n", src);
}

int main()
{
    input();
    Dijkstra(src);
    //trace(2, 1);

    for(int i = 1; i <= n; i++) res = max(res, d[i]);
    //for(int i = 1; i <= n; i++) printf("%d ", d[i]);

    printf("%d", res*2);

    return 0;
}
/*
4 8 2
1 2 7
1 3 8
1 4 4
2 1 69
2 3 1
3 1 2
3 4 6
4 2 2
*/
