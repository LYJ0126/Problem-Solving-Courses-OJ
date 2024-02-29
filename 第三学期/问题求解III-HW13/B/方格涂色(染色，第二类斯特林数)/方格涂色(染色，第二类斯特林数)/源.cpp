#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;

typedef long long ll;
int n, m, k;
const int mod = 998244353;
ll stering[2510][2510];//第二类斯特林数，表示将n个元素划分为m个非空集合的划分数
ll c[2510][2510];//组合数
ll fac[1255];//阶乘
int main()
{
	cin >> n >> m >> k;
	//求第二类斯特林数
	stering[0][0] = 1;
	int len = n * m;
	for (int i = 1; i <= len; i++)
	{
		stering[i][1] = 1;
		for (int j = 2; j <= i; j++)
		{
			stering[i][j] = (stering[i - 1][j - 1] + stering[i - 1][j] * (ll)j) % mod;
		}
	}
	//求组合数
	c[0][0] = 1;
	for (int i = 1; i <= len; i++)
	{
		c[i][0] = 1;
		for (int j = 1; j <= i; j++)
		{
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
		}
	}
	//求阶乘
	fac[0] = 1;
	for (int i = 1; i <= len; i++)
	{
		fac[i] = fac[i - 1] * (ll)i % mod;
	}
	ll ans = 0;
	int x = len >> 1;//x表示X集合的元素个数
	int y = len - x;//y表示Y集合的元素个数
	for (int i = 1; i <= k; ++i) {
		for (int j = 1; j <= k; ++j) {
			if (i <= x && j <= y && i + j <= k) {
				//X集合选i种颜色，Y集合选j种颜色，i+j<=k。这样的方案数为stering[x][i]*stering[y][j]*c[k][i+j]*fac[i+j]
				ans = (ans + stering[x][i] * stering[y][j] % mod * c[k][i + j] % mod * fac[i + j] % mod) % mod;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
/*
input:
2 3 3
output:
42
*/