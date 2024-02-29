#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

char s[1000003], t[1003];
int dp[1005][1005], id[26][1000005];//dp[i][j]��ʾ��t��ǰiλ��ѡ�񣬵�����������Ϊjʱ��s���������Ϊdp[i][j]�����ܳ���s��Χ��
const int inf = 1e6 + 3;
int main()
{
	scanf("%s%s", &s, &t);
	int n = strlen(s), m = strlen(t);
	//��¼s��ÿ��λ�ö�Ӧ�ĸ����ַ��ĺ�̵�λ�ã�������Χ�ĺ��λ��Ϊn
	for (int i = 0; i < 26; i++) {
		id[i][n] = inf;
		for (int j = n - 1; j >= 0; j--) {
			if (s[j] - 'a' == i) id[i][j] = j;
			else id[i][j] = id[i][j + 1];
		}
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m; j++) dp[i][j] = inf;
	}
	//�߽��ʼ��
	dp[1][1] = id[t[0] - 'a'][0];//��ʱs����Ӧλ������t[0]������ͬ��λ�ô�
	for (int i = 2; i <= m; i++) {
		dp[i][1] = min(dp[i - 1][1], id[t[i - 1] - 'a'][0]);
		for (int j = 2; j <= i; j++) {
			if (dp[i - 1][j - 1] != inf) dp[i][j] = min(dp[i - 1][j], id[t[i - 1] - 'a'][dp[i - 1][j - 1] + 1]);
		}
	}
	int ans = m;
	while (dp[m][ans] > n) ans--;
	printf("%d", ans);
	return 0;
}