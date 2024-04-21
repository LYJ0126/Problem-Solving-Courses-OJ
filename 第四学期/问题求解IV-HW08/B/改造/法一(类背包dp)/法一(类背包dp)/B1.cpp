#include<iostream>
#include<cmath>
#include<cstring>
//#include<vector>
using namespace std;
bool dp[101][1001][1001];
int num[101];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T, n;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> n;
		int sum = 0;
		for (int i = 1; i <= n; ++i) {
			cin >> num[i];
			sum += num[i];
		}
		if (sum % 3 != 0) {//不可能分为和相等的三组
			cout << "No" << '\n';
			continue;
		}
		int target = sum / 3;
		//构建不二数组dp[][][]。dp[i][j][k]表示前i个数中,使第一组数和为j，第二组和为k的情况是否存在
		memset(dp, false, sizeof(dp));
		dp[0][0][0] = true;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= target; ++j) {
				for (int k = 0; k <= target; ++k) {
					dp[i][j][k] = dp[i - 1][j][k];//不选第i个数
					if (j >= num[i]) dp[i][j][k] = dp[i][j][k] || dp[i - 1][j - num[i]][k];//选第i个数放入第一组
					if (k >= num[i]) dp[i][j][k] = dp[i][j][k] || dp[i - 1][j][k - num[i]]; //选第i个数放入第二组
				}
			}
		}
		if (dp[n][target][target]) cout << "Yes" << '\n';
		else cout << "No" << '\n';
		/*cin >> n;
		int sum = 0;
		vector<int>num(n + 1);
		for (int i = 1; i <= n; ++i) {
			cin >> num[i];
			sum += num[i];
		}
		if (sum % 3 != 0) {//不可能分为和相等的三组
			cout << "No" << endl;
			continue;
		}
		int target = sum / 3;
		//构建不二数组dp[][][]。dp[i][j][k]表示前i个数中,使第一组数和为j，第二组和为k的情况是否存在
		vector<vector<vector<bool>>>dp(n + 1, vector<vector<bool>>(target + 1, vector<bool>(target + 1, false)));
		dp[0][0][0] = true;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= target; ++j) {
				for (int k = 0; k <= target; ++k) {
					dp[i][j][k] = dp[i - 1][j][k];//不选第i个数
					if (j >= num[i]) dp[i][j][k] = dp[i][j][k] || dp[i - 1][j - num[i]][k];//选第i个数放入第一组
					if (k >= num[i]) dp[i][j][k] = dp[i][j][k] || dp[i - 1][j][k - num[i]]; //选第i个数放入第二组
				}
			}
		}
		if (dp[n][target][target]) cout << "Yes" << endl;
		else cout << "No" << endl;*/
	}
	return 0;
}