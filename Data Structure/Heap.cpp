#include <iostream>

#define maxn long(1e4) + 2
using namespace std;

class MIN_HEAP
{
    private: int n, *heap;
    public:
        MIN_HEAP(int n) { this->n = 0; heap = new int[n + 1]; }
        ~MIN_HEAP() { delete[] heap; }

        int top() { return heap[1]; }
        bool empty() { return !n; }
        int size() { return n; }

        void upHeap(int id)
        {
            if(id == 1 || heap[id] > heap[id >> 1]) return;
            swap(heap[id], heap[id >> 1]);
            upHeap(id >> 1);
        }

        void downHeap(int id)
        {
            int j = id << 1;
            if(j > n) return;
            if(j < n && heap[j] > heap[j + 1]) j++;
            if(heap[j] > heap[id]) return;

            swap(heap[id], heap[j]);
            downHeap(j);
        }
        void push(int val)
        {
            heap[++n] = val;
            upHeap(n);
        }
        void pop(int id)
        {
            if(empty()) return;
            heap[id] = heap[n--];
            downHeap(id); upHeap(id);
        }
};

int main()
{
    ios::sync_with_stdio(false);

    int n, a[100];

    cin >> n; MIN_HEAP pq(n);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pq.push(a[i]);
    }
    for(int i = 1; i <= n; i++) {
        a[i] = pq.top();
        pq.pop(1);
        cout << a[i];
    }

    return 0;
}
