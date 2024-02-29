
//����ֻ�Ƿֿ��һ����
//���P2357�Ƿֿ龭����
//�ֿ�Ӧ�úܶ࣬����԰�ղ��н���
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
int a[1000005];
ll partsum[10000];//���
int belong[1000005];//������
int n, q, l, r, op, len;
ll querry(int left, int right)//l��r�ĺ�
{
	ll sum = 0;
	int lefttill = min(belong[left] * len, right);
	for (int i = left; i <= lefttill; i++) {//��������
		sum += a[i];
	}
	if (belong[left] != belong[right]) {//��������
		int rightstart = (belong[right] - 1) * len + 1;
		for (int i = rightstart; i <= right; i++) {
			sum += a[i];
		}
	}
	//�������
	for (int i = belong[left] + 1; i < belong[right]; i++) {
		sum += partsum[i];
	}
	return sum;
}
int main()
{
	scanf("%d%d", &n, &q);
	len = sqrt(n);//�鳤
	int partnum;//����
	if (n % len == 0) {
		partnum = n / len;
	}
	else partnum = 1 + n / len;
	for (int i = 1; i <= n; i++) belong[i] = (i - 1) / len + 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		partsum[belong[i]] += a[i];
	}
	for (int i = 1; i <= q; i++) {
		scanf("%d%d%d", &op, &l, &r);
		if (op == 2) printf("%lld\n", querry(l, r));
		else {//�޸�ֵ
			partsum[belong[l]] += (r - a[l]);
			a[l] = r;
		}
	}
	return 0;
}