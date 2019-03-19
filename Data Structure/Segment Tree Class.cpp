#include <iostream>
#include <vector>
using namespace std;
#define maxN long(5e4) + 3

class SegmentTree
{
private:
    vector<int> st, a;
    int n;

    int ll(int id) { return id << 1; }
    int rr(int id) { return (id << 1) + 1; }
	int mm(int l, int r) { return (l + r) >> 1; }
    void build(int id, int l, int r)
    {
        if(l == r) st[id] = l;
        else{
            build(ll(id), l, mm(l, r));
            build(rr(id), mm(l, r) + 1, r);

            int p1 = st[ll(id)], p2 = st[rr(id)];
            st[id] = a[p1] < a[p2] ? p1 : p2;
        }
    }

    int rmq(int id, int l, int r, int i, int j)
    {
        if(i > r || j < l) return 0;
        if(i <= l && r <= j) return st[id];

        int p1 = rmq(ll(id), l, mm(l, r), i, j);
        int p2 = rmq(rr(id), mm(l, r) + 1, r, i, j);

        if(!p1) return p2;
        if(!p2) return p1;

        return a[p1] < a[p2] ? p1 : p2;
    }

public:
    SegmentTree() { n = 0; }
    SegmentTree(const vector<int> &_a)
    {
        a = _a; n = a.size();
        st.assign(4*n + 2, 0);
        build(1, 1, n);
    }
    int rmq(int i, int j) { return rmq(1, 1, n, i, j); }
};

int n, q, a[maxN];

int main()
{
    ios::sync_with_stdio(false);
    //cin.tie(0); cout.tie(0);

    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i];

    SegmentTree IT(vector<int>(a, a + n + 1));

    int l, r;
    while(q--)
    {
        cin >> l >> r;

        cout << a[IT.rmq(l, r)] << '\n';
    }

    return 0;
}
