#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#define ii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define maxN 110
using namespace std;
bool visited[maxN];
int n, m, d[maxN];
vector<ii> g[maxN];
priority_queue<ii, vector<ii>, greater<ii> > q;

void input()
{
    int u, v, t;
    scanf("%d%d", &n, &m);

    while(m--)
    {
        scanf("%d%d%d", &u, &v, &t);
        g[u].push_back(ii(v, t));
        g[v].push_back(ii(u, t));
    }
}

void process(int vtx)
{
    visited[vtx] = true;
    ii v;

    for(int i = 0; i < g[vtx].size(); i++)
    {
        v = g[vtx][i];
        if(!visited[v.fi]) q.push(ii(v.se, v.fi));
    }
}

void Prim()
{
    int mst = 0;
    process(1);
    ii u;
    while(!q.empty())
    {
        u = q.top(); q.pop();
        if(!visited[u.se])
            mst += u.fi, process(u.se);
    }
    printf("%d", mst);
}

int main()
{
    input();
    Prim();

    return 0;
}

/*
6 7
1 2 1
1 6 20
2 3 2
3 6 3
3 4 20
5 4 5
6 5 4
*/
