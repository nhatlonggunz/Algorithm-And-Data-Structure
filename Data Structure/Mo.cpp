// Nguyen Cao Nhat Long

/**
Mo's algorithm (based on Square root decomposition),
process offline queries (l,r) in O((N+Q)sqrt(N))
**/

/**
This code uses Mo's Algorithm to solve
https://www.spoj.com/problems/DQUERY/
**/

/**
Given a sequence of n numbers a1, a2, ..., an and a number of d-queries.
A d-query is a pair (i, j) (1 <= i <= j <= n). For each d-query (i, j),
you have to return the number of distinct elements in the subsequence ai, ai+1, ..., aj

1 <= n <= 3e4
1 <= ai <= 10^6
1 <= q <= 2e5, the number of d-queries
**/

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define mp make_pair
#define fi first
#define se second

#define maxn 30002
#define maxq 200002
#define maxa 1000002

int n, a[maxn], id[maxq], cnt[maxa], ans[maxq], res;
ii query[maxq];

bool cmp(int a, int b) {
    int part = sqrt(n);
    int x = query[a].fi / part;
    int y = query[b].fi / part;

    if(x == y)
        return query[a].se < query[b].se;
    return x < y;
}

/**
Take a value a[i] into account
**/
void add(int i) {
    cnt[a[i]]++; // increase counter of value a[i]
    // a[i] appears for the first time
    // which means a new distinct element
    if(cnt[a[i]] == 1) res++;
}

/**
remove a value a[i]
**/
void remove(int i) {
    cnt[a[i]]--;
    if(cnt[a[i]] == 0) res--;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);     cout.tie(0);

    /// Input
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];

    int q;
    cin >> q;
    for(int i = 1; i <= q; i++)
        cin >> query[i].fi >> query[i].se;

    // id[i] is the original position of query i
    for(int i = 1; i <= q; i++)
        id[i] = i;

    /// sort queries into sqrt(q) part
    sort(id + 1, id + q + 1, cmp);

    /// Initialize by answer the first query
    // mo_l, mo_r is the current range (l,r) of Mo's Algorithm
    int mo_l = query[id[1]].fi, mo_r = query[id[1]].se;

    // answer the first query
    for(int i = mo_l; i <= mo_r; i++)
        add(i);
    ans[id[1]] = res;

    for(int i = 2; i <= q; i++) {
        int l = query[id[i]].fi;
        int r = query[id[i]].se;

        while(mo_l > l) add(--mo_l); // extend to the left
        while(mo_r < r) add(++mo_r); // extend to the right
        while(mo_l < l) remove(mo_l++); // reduce from the left
        while(mo_r > r) remove(mo_r--); // reduce from the right

        ans[id[i]] = res; // store query
    }

    for(int i = 1; i <= q; i++)
        cout << ans[i] << '\n';
}
