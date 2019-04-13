/**
Calculate (a * b) % mod in O(log2(x)) without overflow
**/

/**
calculate (a*b) % mod 

b = 2k:
- a*b = a * 2k = (a*k) * 2

b = 2k + 1:
- a*b = a * (2k + 1) = a*2k + a = (a*k)*2 + a
**/

#include <iostream>
using namespace std;

long long mod = 1e15

int fast_mul(long long a, long long b)
{
	if(b == 0) return 0;
	if(b == 1) return a % mod;
	
	long long tmp = fast_mul(a, b >> 1) % mod;
	return b & 1LL ? ((tmp << 1) + a) % mod : (tmp << 1) % mod;
}

int main()
{
	ios::sync_with_stdio(false);
	int a, b;
	cin >> a >> b;

	cout << pow(a, b);

	return 0;
}
