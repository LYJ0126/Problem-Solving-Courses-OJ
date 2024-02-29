
/*
�ڽӾ������Ҫ�����ʣ�
��n���㣬����n*n���ڽӾ����б�������ֵΪ1������Ϊ0��
��ô�þ����k�η��õ��ľ����У�aij��ֵ��ʾ�ӵ�i����j k�������·������
���Դ�������������ϵĸ�����Ϊͼ�Ľ�㹹���ڽӾ��������þ������������k�η����Ӷ��ó�����㵽����㾭��k������ķ�����
*/
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long ll;
int n, m, k, x, y, ne[8][2] = { {-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2} };//ne��ʾ��Դ����
ll a[226][226], res[226][226], temp[226][226];//tempΪ��ʱ�ľ���
const int mod = 998244353;
void mul1()
{
	memset(temp, 0, sizeof(temp));//һ��Ҫ����
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
	memset(temp, 0, sizeof(temp));//һ��Ҫ����
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
void fastpower(int t)//������
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