// Long Nguyen

// https://www.spoj.com/problems/QTREE/
/* This problem is a classic problem for Heavy Light Decomposition */


#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define ii pair<int,int>
#define mp make_pair

#define maxn 10010

// general variables and tree variables
int n = 10000, cost[maxn];
vector<int> g[maxn];
vector<ii> edge;
int h[maxn];

// hld variables (see explanation in heavy light decomposition code)
int posInBase[maxn], nChain, chainHead[maxn], chainInd[maxn];
int parent[maxn], nChild[maxn], nBase, baseArr[maxn];

// segment trees (interval tree)
int IT[4*maxn];

/**
Pre-process the tree using dfs
create h[u], nChild[u], parent[u]
**/
void dfs(int u, int p)
{
    nChild[u] = 1;
    parent[u] = p;

    for(int i = 0; i < (int)g[u].size(); i++)
    {
        int v = g[u][i];

        if(v != p)
        {
            h[v] = h[u] + 1;
            dfs(v, u);
            nChild[u] += nChild[v];
        }
    }
}


/**
Heavy Light Decomposition
**/
void hld(int u)
{
    if(chainHead[nChain] == 0)
        chainHead[nChain] = u;

    chainInd[u] = nChain;
    posInBase[u] = ++nBase;
    baseArr[nBase] = u;

    // Find Heavy Vertex
    int heavyVertex = -1;

    for(int i = 0; i < (int)g[u].size(); i++)
    {
        int v = g[u][i];

        if(v != parent[u])
            if(heavyVertex == -1 || nChild[heavyVertex] < nChild[v])
                heavyVertex = v;
    }

    // found
    if(heavyVertex != -1)
        hld(heavyVertex);

    // finished a chain, continue with light vertex
    for(int i = 0; i < (int)g[u].size(); i++)
    {
        int v = g[u][i];

        if(v != parent[u] && v != heavyVertex)
        {
            ++nChain;
            hld(v);
        }
    }
}


/**
Update Interval Tree
**/
void update(int id, int l, int r, int i, int val)
{
    if(i < l || r < i) return;
    if(l == r && i == l)
    {
        IT[id] = val;
        return;
    }

    int mid = (l + r) >> 1;

    update(id << 1, l, mid, i, val);
    update((id << 1) + 1, mid + 1, r, i, val);

    IT[id] = max(IT[id << 1], IT[(id << 1) + 1]);
}
void update(int pos, int val) { update(1, 1, n, pos, val); }


/**
Query Interval Tree
**/
int query(int id, int l, int r, int i, int j)
{
    if(j < l || i > r) return -1e9;
    if(i <= l && r <= j) return IT[id];

    int mid = (l + r) >> 1;
    return max(
        query(id << 1, l, mid, i, j),
        query((id << 1) + 1, mid + 1, r, i, j)
    );
}
int query(int l, int r) { return query(1, 1, n, l, r); }


/**
Query HLD, find max weight edge on path from u to v
Both query the max weight, and find LCA at the same time
**/
int queryHLD(int u, int v)
{
    int uchain = chainInd[u];
    int vchain = chainInd[v];

    int res = 0;

    // u and v in different chain
    while(uchain != vchain)
    {
        // heavy vertex of uchain is "deeper" than vchain's
        if(h[chainHead[uchain]] > h[chainHead[vchain]])
        {
            // query from heavy vertex (called 'head') to current vertex u
            // note that value at position u is the weight of edge (parent[u], u)
            // therefore query head to u include edge (parent[head], head)
            res = max(res, query(posInBase[chainHead[uchain]], posInBase[u]));
            u = parent[chainHead[uchain]];
            uchain = chainInd[u];
        }
        else
        {
            // same as processing u
            res = max(res, query(posInBase[chainHead[vchain]], posInBase[v]));
            v = parent[chainHead[vchain]];
            vchain = chainInd[v];
        }
    }

    // u and v are now in the same chain
    // make u the ancestor of v, therefore u is LCA
    if(h[u] > h[v])
        swap(u, v);

    // query from u->v, aka LCA -> v
    // value at pos[u]+1 is the weight of edge(LCA, pos[u] + 1)
    res = max(res, query(posInBase[u] + 1, posInBase[v]));

    return res;
}


/**
Reset variable for next query
**/
void reset()
{
    nChain = 1;
    nBase = 0;
    edge.clear();

    for(int i = 1; i <= n; i++)
    {
        g[i].clear();
        h[i] = 0;
        chainHead[i] = 0;
    }
}

void input()
{
    scanf("%d", &n);

    for(int i = 0; i < n - 1; i++)
    {
        int u, v;
        scanf("%d%d%d", &u, &v, &cost[i]);

        edge.push_back(ii(u, v));
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

/**
Setup
dfs to preprocess then HLD and build IT
**/
void setup()
{
    // preprocess tree
    dfs(1, 0);

    // heavy light decomposition
    hld(1);

    // make edge list so that with an edge (u,v)
    // u is the parent of v
    // which makes it easier for queries in this problem
    for(int i = 0; i < (int)edge.size(); i++)
        if(parent[edge[i].first] == edge[i].second)
            swap(edge[i].first, edge[i].second);

    // if the cost of edge (u,v) is changed (u is parent of v)
    // update IT at position posInBase[v]
    for(int i = 0; i < (int)edge.size(); i++)
        update(posInBase[edge[i].second], cost[i]);
}


/**
Main job, solve the problem
**/
void process()
{
    char s[5];
    while(true)
    {
        scanf("%s", s);

        if(s[0] == 'Q')
        {
            int u, v;
            scanf("%d%d", &u, &v);

            int res = queryHLD(u, v);
            printf("%d\n", res);
        }
        else if(s[0] == 'C')
        {
            int index, val;
            scanf("%d%d", &index, &val);
            index--;

            // weight of edge (u,v) is stored at pos[v] (u is parent)
            update(posInBase[edge[index].second], val);
        }
        else
            break;
    }
}

int main()
{
    #ifdef DEBUG
    freopen("qtree.inp", "r", stdin);
    freopen("qtree.out", "w", stdout);
    #endif // DEBUG

    int nTest;
    scanf("%d", &nTest);

    while(nTest--)
    {
        reset();
        input();
        setup();
        process();
    }
}

/*
1

3
1 2 1
2 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
DONE


1
20
5 1 20
10 2 27
12 3 11
12 4 24
12 5 25
7 6 17
18 7 28
16 8 25
18 9 23
12 10 17
7 11 15
1 13 10
18 14 13
14 15 17
14 16 24
12 17 11
4 18 10
8 19 18
2 20 11
Query 2 18
Change 1 101
Query 2 18
Change 2 102
Query 2 18
Change 3 103
Query 2 18
Change 4 104
Query 2 18
Change 5 105
Query 2 18
DONE

27
27
102
102
104
104
*/
