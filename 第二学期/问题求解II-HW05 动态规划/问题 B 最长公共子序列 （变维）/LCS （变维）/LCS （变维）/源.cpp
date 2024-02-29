#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

char s[1000003], t[1003];
int dp[1005][1005], id[26][1000005];//dp[i][j]表示在t串前i位中选择，当公共串长度为j时，s串长度最短为dp[i][j]（可能超出s范围）
const int inf = 1e6 + 3;
int main()
{
	scanf("%s%s", &s, &t);
	int n = strlen(s), m = strlen(t);
	//记录s中每个位置对应的各个字符的后继的位置，超出范围的后继位置为n
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
	//边界初始化
	dp[1][1] = id[t[0] - 'a'][0];//此时s串对应位置在与t[0]符号相同的位置处
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