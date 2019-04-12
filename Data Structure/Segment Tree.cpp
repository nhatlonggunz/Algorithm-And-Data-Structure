#include <iostream>
using namespace std;
#define maxN long(5e4) + 3
int n, q, a[maxN], st[4*maxN];

int ll(int id) { return id << 1; }
int rr(int id) { return (id << 1) + 1; }
int mm(int l, int r) { return (l + r) >> 1; }

// building IT
void build(int id, int l, int r)
{
    if(l == r) st[id] = a[l];
    else{
        build(ll(id), l, mm(l, r));
        build(rr(id), mm(l, r) + 1, r);
        st[id] = max(st[ll(id)], st[rr(id)]);
    }
}

// Update IT
void update(int id, int l, int r, int i, int val)
{
    if(i < l || i > r) return;
    if(l == r && i == l) { st[id] = val; return; }

    update(ll(id), l, mm(l, r), i, val);
    update(rr(id), mm(l, r) + 1, r, i, val);

    st[id] = max(st[ll(id)], st[rr(id)]);
}
void update(int id, int val) { update(1, 1, n, id, val); }


// Query IT
int rmq(int id, int l, int r, int i, int j)
{
    if(j < l || i > r) return -long(1e9);
    if(i <= l && r <= j) return st[id];
    return max(
        rmq(ll(id), l, mm(l, r), i, j),
        rmq(rr(id), mm(l, r) + 1, r, i, j)
    );
}
int rmq(int l, int r) { return rmq(1, 1, n, l, r); }


// Main
int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> q;

    for(int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);

    int k, u, v;

    while(q--)
    {
        cin >> k >> u >> v;
        if(!k) update(u, v);
        else cout << rmq(u, v) << '\n';
    }

    return 0;
}
