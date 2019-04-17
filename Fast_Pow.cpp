/**
Calculate a^x in O(logx)
**/

#include <iostream>
using namespace std;

long long mod = 1e9 + 7LL;

long long pow(long long base, int exp)
{
	if(exp == 0) return 1LL;
	long long tmp = pow(base, exp >> 1) % mod;
	return exp & 1 ? (base * tmp * tmp) % mod : (tmp * tmp) % mod;
}

int main()
{
	ios::sync_with_stdio(false);
	int a, b;
	cin >> a >> b;

	cout << pow(a, b);

	return 0;
}
