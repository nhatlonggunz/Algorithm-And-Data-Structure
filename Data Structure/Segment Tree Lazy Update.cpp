/*
n elements, q queries;
0 u v: update(u, v);
1 u v: max(a[u..v]);
6 3
0 1 3 3
0 4 6 4
1 1 6
4
*/
#include <iostream>
using namespace std;
#define maxN long(5e4) + 3
int n, q, a[maxN], st[4*maxN], lazy[4*maxN];

int ll(int id) { return id << 1; }
int rr(int id) { return (id << 1) + 1; }

void build(int id, int l, int r)
{
    if(l == r) st[id] = a[l];
    else{
        int m = (l + r) >> 1;
        build(ll(id), l, m);
        build(rr(id), m + 1, r);

        st[id] = max(st[ll(id)], st[rr(id)]);
    }
}

void update(int id, int l, int r, int i, int j, int val)
{
    if(lazy[id])
    {
        st[id] += lazy[id];

        if(l != r) {
            lazy[ll(id)] += lazy[id];
            lazy[rr(id)] += lazy[id];
        }
        lazy[id] = 0;
    }

    if(j < l || i > r) return;
    if(i <= l && r <= j)
    {
        st[id] += val;

        if(l != r) {
            lazy[ll(id)] += val;
            lazy[rr(id)] += val;
        }
        return;
    }

    int m = (l + r) >> 1;
    update(ll(id), l, m, i, j, val);
    update(rr(id), m + 1, r, i, j, val);

    st[id] = max(st[ll(id)], st[rr(id)]);
}
void update(int l, int r, int val) { update(1, 1, n, l, r, val); }

int rmq(int id, int l, int r, int i, int j)
{
    if(j < l || i > r) return -long(1e9);
    if(lazy[id])
    {
        st[id] += lazy[id];

        if(l != r) {
            lazy[ll(id)] += lazy[id];
            lazy[rr(id)] += lazy[id];
        }

        lazy[id] = 0;
    }
    if(i <= l && r <= j) return st[id];

    int m = (l + r) >> 1;
    return max( rmq(ll(id), l, m, i, j),
                rmq(rr(id), m + 1, r, i, j));
}
int rmq(int l, int r) { return rmq(1, 1, n, l, r); }

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> q;

    int t, u, v, k;
    while(q--)
    {
        cin >> t;

        if(!t) {
            cin >> u >> v >> k;
            update(u, v, k);
        }
        else {
            cin >> u >> v;
            cout << rmq(u, v) << '\n';
        }
    }

    return 0;
}
