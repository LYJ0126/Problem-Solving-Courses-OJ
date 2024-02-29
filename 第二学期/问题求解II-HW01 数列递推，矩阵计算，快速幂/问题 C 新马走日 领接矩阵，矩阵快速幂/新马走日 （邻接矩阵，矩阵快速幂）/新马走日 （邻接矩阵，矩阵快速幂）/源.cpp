
/*
邻接矩阵很重要的性质：
对n个点，构造n*n的邻接矩阵，有边相连则值为1，否则为0。
那么该矩阵的k次方得到的矩阵中，aij的值表示从点i到点j k步到达的路径数。
所以此题可以以棋盘上的格子作为图的结点构造邻接矩阵，再利用矩阵快速幂求其k次方，从而得出从起点到任意点经过k步到达的方法数
*/
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long ll;
int n, m, k, x, y, ne[8][2] = { {-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2} };//ne表示来源方向
ll a[226][226], res[226][226], temp[226][226];//temp为临时的矩阵
const int mod = 998244353;
void mul1()
{
	memset(temp, 0, sizeof(temp));//一定要清零
	int le = n * m;
	for (int i = 1; i <= le; i++)
		for (int t = 1; t <= le; t++)
			for (int j = 1; j <= le; j++) {
				temp[i][j] = (temp[i][j] + (res[i][t] * a[t][j]) % mod) % mod;
			}
	for (int i = 1; i <= le; i++)
		for (int j = 1; j <= le; j++) {
			res[i][j] = temp[i][j];
		}
}
void mul2()
{
	memset(temp, 0, sizeof(temp));//一定要清零
	int le = n * m;
	for (int i = 1; i <= le; i++)
		for (int t = 1; t <= le; t++)
			for (int j = 1; j <= le; j++) {
				temp[i][j] = (temp[i][j] + (a[i][t] * a[t][j]) % mod) % mod;
			}
	for (int i = 1; i <= le; i++)
		for (int j = 1; j <= le; j++) {
			a[i][j] = temp[i][j];
		}
}
void fastpower(int t)//快速幂
{
	while (t > 0) {
		if (t & 1) mul1();
		t >>= 1;
		mul2();
	}
}

int main()
{
	cin >> n >> m >> x >> y >> k;
	memset(a, 0, sizeof(a));
	int len = n * m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k < 8; k++) {
				int nx = i + ne[k][0];
				int ny = j + ne[k][1];
				if (nx<1 || nx>n || ny<1 || ny>m) continue;
				a[(i - 1) * m + j][(nx - 1) * m + ny] = 1;
				a[(nx - 1) * m + ny][(i - 1) * m + j] = 1;
			}
		}
	}
	memset(res, 0, sizeof(0));
	for (int t = 1; t <= len; t++) res[t][t] = 1;
	fastpower(k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			printf("%lld ", res[(x - 1) * m + y][(i - 1) * m + j]);
		}
		printf("\n");
	}
	return 0;
}