#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

int k, n;
int dp[105][10005];//k����������m�Σ����ȷ�����ٲ�¥
int main()
{
	cin >> k >> n;
	for (int i = 1; i <= k; i++) dp[i][1] = 1;//�߽磺���Ӵ���Ϊ1ʱ��¥��ֻ��Ϊ1¥
	int ans = 0;
	for (int j = 2; j <= n; j++) {
		for (int i = 1; i <= k; i++) {
			dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1] + 1;//�����dp[i-1][j-1]+1�����ˣ������Ͳ���������һ
			//�����dp[i-1][j-1]+1��û�飬�������䣬��������һ
			//�����ҵ���һ�㣬�ܹ�����ȷ���߶�Ϊdp[i-1][j-1]+dp[i][j-1]+1
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