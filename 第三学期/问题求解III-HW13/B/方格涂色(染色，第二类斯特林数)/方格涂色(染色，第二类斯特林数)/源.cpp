#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;

typedef long long ll;
int n, m, k;
const int mod = 998244353;
ll stering[2510][2510];//�ڶ���˹����������ʾ��n��Ԫ�ػ���Ϊm���ǿռ��ϵĻ�����
ll c[2510][2510];//�����
ll fac[1255];//�׳�
int main()
{
	cin >> n >> m >> k;
	//��ڶ���˹������
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
	//�������
	c[0][0] = 1;
	for (int i = 1; i <= len; i++)
	{
		c[i][0] = 1;
		for (int j = 1; j <= i; j++)
		{
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
		}
	}
	//��׳�
	fac[0] = 1;
	for (int i = 1; i <= len; i++)
	{
		fac[i] = fac[i - 1] * (ll)i % mod;
	}
	ll ans = 0;
	int x = len >> 1;//x��ʾX���ϵ�Ԫ�ظ���
	int y = len - x;//y��ʾY���ϵ�Ԫ�ظ���
	for (int i = 1; i <= k; ++i) {
		for (int j = 1; j <= k; ++j) {
			if (i <= x && j <= y && i + j <= k) {
				//X����ѡi����ɫ��Y����ѡj����ɫ��i+j<=k�������ķ�����Ϊstering[x][i]*stering[y][j]*c[k][i+j]*fac[i+j]
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