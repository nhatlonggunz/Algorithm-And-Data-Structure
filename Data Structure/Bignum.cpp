#include <string>
#include <iostream>
using namespace std;
string a, b;

int toNum(char c) { return c - '0'; }
char toChar(int n) { return n + '0'; }

string add(string a, string b)
{
	int tmp, carry = 0;

	if(a.length() < b.length()) a.insert(0, b.length() - a.length(), '0');
	else if(a.length() > b.length()) b.insert(0, a.length() - b.length(), '0');

	for(int i = a.length() - 1; i >= 0; i--)
	{
		tmp = toNum(a[i]) + toNum(b[i]) + carry;
		a[i] = toChar(tmp % 10);
		carry = tmp / 10;
	}

	return carry ? ('1' + a) : a;
}

string operator*(string a, int b)
{
	int tmp, carry = 0;

	for(int i = a.length() - 1; i >= 0; i--)
	{
		tmp = toNum(a[i]) * b + carry;
		a[i] = toChar(tmp % 10);
		carry = tmp / 10;
	}

	return carry ? (toChar(carry) + a) : a;
}

string operator*(string a, string b)
{
	int m = -1;
	string tmp, res;

	for(int i = b.length() - 1; i >= 0; i--)
	{
		//tmp = multiply(a, toNum(b[i]));
		tmp = a * toNum(b[i]);
		tmp.append(++m, '0');
        res = add(res, tmp);
	}

	return res;
}

bool operator >(string a, string b)
{
    if(a.length() > b.length()) return true;
    if(a.length() < b.length()) return false;
    return a > b;
}
bool operator <(string a, string b)
{
    if(a.length() < b.length()) return true;
    if(a.length() > b.length()) return false;
    return a < b;
}
bool operator >=(string a, string b) { return a > b || a == b; }
bool operator <=(string a, string b) { return a < b || a == b; }

int main()
{
    cin >> a >> b;

    cout << a * b;

    return 0;
}
