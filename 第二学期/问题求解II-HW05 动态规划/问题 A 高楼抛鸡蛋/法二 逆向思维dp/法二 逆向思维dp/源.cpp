#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

int k, n;
int dp[105][10005];//k个鸡蛋，仍m次，最多确定多少层楼
int main()
{
	cin >> k >> n;
	for (int i = 1; i <= k; i++) dp[i][1] = 1;//边界：当扔次数为1时，楼层只能为1楼
	int ans = 0;
	for (int j = 2; j <= n; j++) {
		for (int i = 1; i <= k; i++) {
			dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1] + 1;//如果在dp[i-1][j-1]+1层碎了，鸡蛋和操作数均减一
			//如果在dp[i-1][j-1]+1层没碎，鸡蛋不变，操作数减一
			//包括砸的那一层，总共可以确定高度为dp[i-1][j-1]+dp[i][j-1]+1
		}
		if (dp[k][j] >= n) {
			ans = j;
			break;
		}
	}
	if (n == 1) cout << 1;
	else cout << ans;
	return 0;
}