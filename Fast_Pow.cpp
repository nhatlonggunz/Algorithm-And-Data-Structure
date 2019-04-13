/**
Calculate a^x in O(logx)
**/

#include <iostream>
using namespace std;

int pow(int base, int exp)
{
	if(exp == 0) return 1;
	int tmp = pow(base, exp / 2);
	return b & 1 ? base * tmp * tmp : tmp * tmp;
}

int main()
{
	ios::sync_with_stdio(false);
	int a, b;
	cin >> a >> b;

	cout << pow(a, b);

	return 0;
}
