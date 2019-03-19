#include <vector>
#include <queue>
#include <iostream>
using namespace std;
#define maxN long(1e3) + 3
int n, s, t, mf, c[maxN][maxN], f[maxN][maxN];
vector<int> g[maxN], p;
 
bool findPath()
{
    int u, v;
    queue<int> q;           q.push(s);
    p.assign(n + 1, 0);     p[s] = -1;
 
    while(!q.empty())
    {
        u = q.front(); q.pop();
        if(u == t) return true;
 
        for(unsigned i = 0; i < g[u].size(); i++)
        {
            v = g[u][i];
            if(!p[v] && f[u][v] < c[u][v])
            {
                p[v] = u;
                if(v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}
 
void augment()
{
    int u, v, flow = long(1e9);
 
    for(v = t; (u = p[v]) != -1; v = u)
        flow = min(flow, c[u][v] - f[u][v]);
    for(v = t; (u = p[v]) != -1; v = u)
        f[u][v] += flow, f[v][u] -= flow;
 
    mf += flow;
}
 
void input()
{
    int m, a, b, d;
    cin >> n >> m >> s >> t;
 
    while(m--)
    {
        cin >> a >> b >> d;
        g[a].push_back(b);
        g[b].push_back(a);
        c[a][b] = d;
    }
}
 
int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    input();
 
    while(findPath())
        augment();
 
    cout << mf;
 
    return 0;
}