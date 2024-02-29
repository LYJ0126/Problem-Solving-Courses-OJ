#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cmath>
#include<cstring>
using namespace std;

typedef long long ll;
const int mod = 998244353, len = 2005;
ll n, a[200005], b[200005], fac[8040], inv[8040], dp[4020][4020], ans = 0;
//fac����׳ˣ�inv����׳˵���Ԫ��dpΪ��̬�滮����Ľ��,ansΪ���ս��
//������
ll quickpow(ll x, ll y)
{
	ll res = 1;
	while (y > 0) {
		if (y & 1) res = (res * x) % mod;
		y >>= 1;
		x = (x * x) % mod;
	}
	return res;
}
//����Ԫ
inline ll inverse(ll x) {
	return quickpow(x, mod - 2) % mod;
}
//�������
inline ll C(ll x, ll y) {
	return fac[x] * inv[x - y] % mod * inv[y] % mod;
}
int main()
{
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld%lld", &a[i], &b[i]);
		dp[len - a[i]][len - b[i]] ++;//offset=len;
	}
	fac[0] = 1, inv[0] = inverse(fac[0]);//�׳˺���ԪԤ����
	for (int i = 1; i <= 8020; i++) {//��׳˺���Ԫ
		fac[i] = (fac[i - 1] * i) % mod;
		inv[i] = inverse(fac[i]);
	}
	//�������ÿһ���У�������ʼ�㵽�õ��·�������ĺ�
	for (int i = 1; i <= len * 2; i++) {
		for (int j = 1; j <= len * 2; j++) {
			dp[i][j] = (dp[i][j] + (dp[i - 1][j] + dp[i][j - 1]) % mod) % mod;
		}
	}
	for (int i = 1; i <= n; i++) {
		ans = (ans + dp[len + a[i]][len + b[i]]) % mod;
		ans = (ans - C(2 * a[i] + 2 * b[i], 2 * a[i])) % mod;//�Խ����ϵĶ�Ӧ��������ѡ��ͬһ�����ϰ������
		ans = (ans + mod) % mod;//��ֹ��Ϊ����
	}
	ll inverseoftwo = (fac[1] * inverse(fac[2])) % mod;//����x��=(x-1)!*(x!)����2����Ԫ
	ans = (ans * inverseoftwo) % mod;
	printf("%lld", ans);
	return 0;
}