#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cmath>
#include<cstring>
using namespace std;

//�����б����ݻ�̫�󣬵�����Ʒ��ֵ��ȴ������1e6�����ǿ��Խ�dp�ı�����Ϊѡ�����Ʒ��Χ���ܼ�ֵ��
//����ǰi����Ʒ��ѡ��ʹ�ܼ�ֵΪj(�����޽⣬�޽�������ֵinf)����Ʒ�������С������������ӽṹ��
//����ĩ�����Բ��Ҵ�
const int inf = 1e9 + 4;
int n, V, v[550], w[550], dp[1000005];//volume worth  Ϊ�˷�ֹMLE������һάdp����
int main()
{
	scanf("%d%d", &n, &V);
	for (int i = 1; i <= n; i++) scanf("%d%d", &v[i], &w[i]);
	dp[0] = 0;
	for (int i = 1; i <= 1e6; i++) dp[i] = inf;
	for (int i = 1; i <= n; i++) {
		for (int j = 1e6; j >= w[i]; j--) {
			if (dp[j] == inf && dp[j - w[i]] == inf) dp[j] = inf;//���ִ˴��޽⣬��ֵΪinf
			else {
				dp[j] = min(dp[j - w[i]] + v[i], dp[j]);//�����ӽṹ
			}
		}
	}
	int ans = 1e6;
	while (dp[ans] > V) ans--;//����Ѱ�Ҵ�
	printf("%d", ans);
	return 0;
}