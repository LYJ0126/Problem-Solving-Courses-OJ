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
		if (sum % 3 != 0) {//�����ܷ�Ϊ����ȵ�����
			cout << "No" << '\n';
			continue;
		}
		int target = sum / 3;
		//������������dp[][][]��dp[i][j][k]��ʾǰi������,ʹ��һ������Ϊj���ڶ����Ϊk������Ƿ����
		memset(dp, false, sizeof(dp));
		dp[0][0][0] = true;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= target; ++j) {
				for (int k = 0; k <= target; ++k) {
					dp[i][j][k] = dp[i - 1][j][k];//��ѡ��i����
					if (j >= num[i]) dp[i][j][k] = dp[i][j][k] || dp[i - 1][j - num[i]][k];//ѡ��i���������һ��
					if (k >= num[i]) dp[i][j][k] = dp[i][j][k] || dp[i - 1][j][k - num[i]]; //ѡ��i��������ڶ���
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
		if (sum % 3 != 0) {//�����ܷ�Ϊ����ȵ�����
			cout << "No" << endl;
			continue;
		}
		int target = sum / 3;
		//������������dp[][][]��dp[i][j][k]��ʾǰi������,ʹ��һ������Ϊj���ڶ����Ϊk������Ƿ����
		vector<vector<vector<bool>>>dp(n + 1, vector<vector<bool>>(target + 1, vector<bool>(target + 1, false)));
		dp[0][0][0] = true;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= target; ++j) {
				for (int k = 0; k <= target; ++k) {
					dp[i][j][k] = dp[i - 1][j][k];//��ѡ��i����
					if (j >= num[i]) dp[i][j][k] = dp[i][j][k] || dp[i - 1][j - num[i]][k];//ѡ��i���������һ��
					if (k >= num[i]) dp[i][j][k] = dp[i][j][k] || dp[i - 1][j][k - num[i]]; //ѡ��i��������ڶ���
				}
			}
		}
		if (dp[n][target][target]) cout << "Yes" << endl;
		else cout << "No" << endl;*/
	}
	return 0;
}