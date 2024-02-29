#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long ll;
const int mod = 998244353;
struct matrix
{
	ll a[2][2];
};
matrix mul(matrix A, matrix B)//æÿ’Û≥À∑®
{
	matrix res;
	memset(res.a, 0, sizeof(res.a));
	for (int i = 0; i <= 1; i++)
		for (int j = 0; j <= 1; j++)
			for (int k = 0; k <= 1; k++) {
				res.a[i][j] = (res.a[i][j] + (A.a[i][k] * B.a[k][j]) % mod) % mod;
			}
	return res;
}
ll fastpower(ll n)//æÿ’ÛøÏÀŸ√›
{
	matrix c, res;
	c.a[0][0] = c.a[0][1] = c.a[1][0] = 1;
	c.a[1][1] = 0;
	memset(res.a, 0, sizeof(res.a));
	res.a[0][0] = 1, res.a[0][1] = 1;
	while (n > 0) {
		if (n & 1) res = mul(res, c);
		c = mul(c, c);
		n >>= 1;
	}
	return res.a[0][0];
}
int main()
{
	int n;
	cin >> n;
	if (n == 1 || n == 2) cout << 1;
	else cout << fastpower(n - 2);
	return 0;
}