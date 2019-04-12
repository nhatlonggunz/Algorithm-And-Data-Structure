// https://blog.anudeep2011.com/heavy-light-decomposition/

/*
Implement the idea of Heavy Light Decomposition
To see how to apply to a problem,
look for QTREE problems in SPOJ
*/

// Nguyen Cao Nhat Long
// Pikachuuuuuuuuuuuuu
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

#define maxn 10010

// End of template

/*
    chainHead[c]: head of chain c
    chainInd[u]: no. of the chain to which u belongs
    posInBase[u]: position of u in the whole big (combined of) chain(s), called base chain

    note: chain[y] is cut from chain[x] if parent[chainHead[y]] = a node in chain[x]
            (which means jump from this chain to parent chain)
*/

int n, parent[maxn], nChain, chainHead[maxn], chainInd[maxn], posInBase[maxn];
int nChild[maxn]; // nChild[u] size of subtree with root u
int cnt;

void hld(int u)
{
    if(chainHead[nChain] == 0)
        chainHead[nChain] = u;

    chainInd[u] = nChain;
    posInBase = ++cnt;

    // find heavy vertex (find v: max(nChild[v]))
    int heavyVertex = -1;

    for(int i = 0; i < (int)g[u].size(); i++)
    {
        int v = g[u][i];

        if(v != p)
            if(heavyVertex == -1 || nChild[v] > nChild[heavyVertex])
                heavyVertex = v;
    }


    // found ! (also imply u is not leaf)
    if(heavyVertex > -1)
        hld(heavyVertex);

    // after finishing a chain, look for new chains
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

// update interval tree from node u to node anc (anc is ancestor of u)
void update(int u, int anc)
{
    int uchain = chainInd[u];       // current chain of u
    int achain = chainInd[anc];     // current chain of anc

    while(true)
    {
        // if u and anc are in a same chain, update from u upto a
        if(uchain == achain)
        {
            updateIT(..., posInBase[anc], posInBase[u],...);
            break;
        }
        // else update from u upto chain head of u
        updateIT(..., posInBase[chainHead[u]], posInBase[u], ...);

        // jump up to 'parent' chain
        u = parent[chainHead[u]];
        uchain = chainInd[u];
    }
}
