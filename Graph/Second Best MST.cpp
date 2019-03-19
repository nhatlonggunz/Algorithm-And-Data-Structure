#include <bits/stdc++.h>
using namespace std;
#define maxN long(1e6) + 10
#define ii pair<int,int>
#define fi first
#define se second
#define mp make_pair
int n, m, res1 = long(1e9) + 10, res2 = long(1e9) + 10;
vector< pair<int,ii> > edge;
vector<int> MST;

class DisjoinSet
{
public:
    DisjoinSet(int n)
    {
        p.assign(n + 1, 0);
        r.assign(n + 1, 0);
        for(int i = 1; i <= n; i++) p[i] = i;
    }
    int Find(int x) { return x == p[x] ? x : (p[x] = Find(p[x])); }
    bool isSameSet(int x, int y) { return Find(x) == Find(y); }
    void Union(int x, int y)
    {
        x = Find(x); y = Find(y);
        if(r[x] < r[y]) p[x] = y;
        else
        {
            p[y] = x;
            if(r[x] == r[y]) r[x]++;
        }
    }
private: vector<int> p, r;
} *UF;

void input()
{
    int u, v, t;
    scanf("%d%d", &n, &m);

    while(m--)
    {
        scanf("%d%d%d", &u, &v, &t);
        edge.push_back(mp(t, ii(u, v)));
    }
    sort(edge.begin(), edge.end());
}

void Kruskal(int banned, bool flag)
{
    int cnt = 0, S1 = 0, S2 = 0 ; UF = new DisjoinSet(n);

    for(unsigned i = 0; i < edge.size(); i++)
        if(i != banned && !UF->isSameSet(edge[i].se.fi, edge[i].se.se))
        {
            UF->Union(edge[i].se.fi, edge[i].se.se);
            S1 += edge[i].fi, S2 += edge[i].fi;
            if(flag) MST.push_back(i);
            if(++cnt == n - 1) break;
        }
    if(flag) res1 = min(res1, S1);
    if(!flag && cnt == n - 1) res2 = min(res2, S2);
    //printf("%d %d\n", res1, res2);
}

int main()
{
    input();
    Kruskal(-1, 1);

    for(unsigned i = 0; i < MST.size(); i++) Kruskal(MST[i], 0);

    printf("%d %d", res1, res2);

    return 0;
}

/*
5 6
1 3 1
2 3 1
3 4 1
3 5 1
2 5 5
4 5 2

4 5
*/

/*
5 8
1 3 75
1 2 9
3 4 51
2 5 42
4 5 31
3 5 66
3 2 95
4 2 19

110 121
*/
