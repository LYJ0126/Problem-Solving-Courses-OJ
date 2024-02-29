#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long ll;
const int mod = 998244353;
ll m, k, c;
ll a[11], b[4], f[11], q;
int C(int n, int t)//求Cnk的组合数
{
	int up = 1, down = 1;
	for (int j = n; j >= n - t + 1; j--) up *= j;
	for (int j = 1; j <= t; j++) down *= j;
	return up / down;
}
struct matrix1//构造1*(m+k+2)的矩阵
{
	ll a1[16];
};
struct matrix2//构造(m+k+2)*(m+k+2)的矩阵
{
	ll b1[16][16];
};
matrix1 mul1(matrix1 A, matrix2 B)//1,2型矩阵相乘,对应矩阵快速幂中res=res*d的步骤
{
	matrix1 res;
	memset(res.a1, 0, sizeof(res.a1));
	for (int i = 1; i <= m + k + 2; i++) {
		for (int j = 1; j <= m + k + 2; j++) {
			res.a1[i] = (res.a1[i] + (A.a1[j] * B.b1[j][i]) % mod) % mod;
		}
	}
	return res;
}
matrix2 mul2(matrix2 A, matrix2 B)//2,2型矩阵相乘，对应矩阵快速幂中d=d*d的步骤
{
	matrix2 res;
	memset(res.b1, 0, sizeof(res.b1));
	for (int i = 1; i <= m + k + 2; i++)
		for (int j = 1; j <= m + k + 2; j++)
			for (int t = 1; t <= m + k + 2; t++) {
				res.b1[i][j] = (res.b1[i][j] + (A.b1[i][t] * B.b1[t][j]) % mod) % mod;
			}
	return res;
}
ll fastpower(ll n, ll base)//快速幂求pow(base,n)，此题中由于k较小可以不用快速幂
{
	ll res = 1;
	while (n > 0) {
		if (n & 1) {
			res = (res * base) % mod;
		}
		base = (base * base) % mod;
		n >>= 1;
	}
	return res;
}
ll matrixpow(ll n)//核心:矩阵快速幂
{
	matrix1 res;
	matrix2 d;
	//核心:初始化
	//转移矩阵应如下
	/*
	a1	1	0	…	0(1,m)										0(j=m+k+2,最后一列)
	a2	0	1		0			i从1到m,j从m+1到m+k+1全是0		0
	…	…	0		…											0
	am-1			1(m-1,m)									…
	am		…		0
	b0				…			C00		C11		C22…
	b1							0		C10		C21
	…							…		0		C20
												0
	bk									…		^				0
	c	0	0		0			0		0		0				c(注意最后有c)
	*/
	for (int i = 1; i <= m; i++) d.b1[i][1] = a[i];
	for (int i = m + 1; i <= m + k + 1; i++) d.b1[i][1] = b[i - m - 1];
	d.b1[m + k + 2][1] = c;
	for (int j = 2; j <= m; j++)
		for (int i = 1; i <= m + k + 2; i++) {
			if (j == i + 1) d.b1[i][j] = 1;
			else d.b1[i][j] = 0;
		}
	for (int j = m + 1; j <= m + k + 1; j++) {
		for (int i = 1; i <= m + k + 2; i++) {
			if (i <= m) d.b1[i][j] = 0;
			else {
				if (i <= j) {
					d.b1[i][j] = C(j - m - 1, j - i);
				}
				else d.b1[i][j] = 0;
			}
		}
	}
	for (int i = 1; i <= m + k + 2; i++) {
		d.b1[i][m + k + 2] = 0;
	}
	d.b1[m + k + 2][m + k + 2] = c;
	memset(res.a1, 0, sizeof(res.a1));
	for (int i = 1; i <= m; i++) res.a1[i] = f[m + 1 - i];
	for (int i = m + 1; i <= m + k + 1; i++) res.a1[i] = fastpower(i - m - 1, m + 1);//注意开始时res里系数为bi的项从m+1开始，
	//这样保证计算递推式下一项时res的第一个数确实是fn
	res.a1[m + k + 2] = fastpower(m, c);
	//快速幂模板
	while (n > 0) {
		if (n & 1) {
			res = mul1(res, d);
		}
		d = mul2(d, d);
		n >>= 1;
	}
	return res.a1[1];
}

int main()
{
	scanf("%lld%lld%lld", &m, &k, &c);
	for (int i = 1; i <= m; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= m; i++) scanf("%lld", &f[i]);
	for (int i = 0; i <= k; i++) scanf("%lld", &b[i]);
	scanf("%lld", &q);
	for (int t = 1; t <= q; t++) {
		ll n;
		scanf("%lld", &n);
		//注意这个分类
		if (n <= m) printf("%lld ", f[n]);
		else {
			ll ans = matrixpow(n - m);
			printf("%lld ", ans);
		}
	}
	return 0;
}