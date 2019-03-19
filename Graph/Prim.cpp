#include <cstdio>
#include <vector>
#include <iostream>
#include <queue>
#define ii pair<int, long long>
#define li pair<long long, int>
#define fi first
#define se second
#define maxN long(3e3) + 5
using namespace std;
int n;
vector<long long> d;
vector<ii> g[maxN];
vector<bool> visited;
long long res, a[maxN];
priority_queue<li> pq;

void input()
{
    long long t;
    scanf("%d", &n);

    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        for(int j = 1; j < i; j++)
        {
            if((i + j)&1) t = (a[i] + a[j])*min(a[i],a[j]);
            else t = (a[i] + a[j])*max(a[i],a[j]);
            g[i].push_back(ii(j, t));
            g[j].push_back(ii(i, t));
        }
    }
}

void Prim()
{
    d.assign(n + 1, -1); visited.assign(n + 1, false);
    d[1] = 0;
    int u;

    for(int k = 1; k <= n; k++)
    {
        u = 0;
        for(int i = 1; i <= n; i++) 
            if(!visited[i] && d[i] > d[u]) 
                u = i;
                
        visited[u] = true; 
        res += d[u];
        
        for(unsigned i = 0; i < g[u].size(); i++)
        {
            ii v = g[u][i];
            if(!visited[v.fi] && d[v.fi] < v.se) d[v.fi] = v.se;
        }
    }
}

int main()
{
    input();
    Prim();

    printf("%lld", res);

    return 0;
}
