#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
ll a[1000005];
int n, q, l, r;
int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		a[i] += a[i - 1];//a[i]��ʾ���Ǵ�1��i���������ͣ������ǰ׺��
	}
	for (int i = 1; i <= q; i++) {
		scanf("%d%d", &l, &r);
		printf("%lld\n", a[r] - a[l - 1]);
	}
	return 0;
}