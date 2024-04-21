#include<iostream>
#include<cmath>
using namespace std;

typedef long long ll;
ll n, W, Q;//商店中的货物数量、小L的背包大小，以及小L设置的价值上限
//背包容量很大，用传统的01背包做法会超时且超内存
//注意到物品价值和上限为Q,Q<=100000,可以考虑变维
//dp[i][j]表示前i个物品中，价值为j的情况下，最小的体积。如果不存在这样的情况，dp[i][j]=INF
//dp[i][j]=min(dp[i-1][j],dp[i-1][j-v[i]]+w[i])
//为了节省空间，采用一维数组
ll dp[100005];
ll w[2001], q[2001];//w[i]表示第i个物品的体积，q[i]表示第i个物品的价值
const ll INF = 0x3f3f3f3f3f3f3f3f;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> W >> Q;
	//初始化
	dp[0] = 0;
	for (int i = 1; i <= Q; ++i) dp[i] = INF;
	ll maxvalue = 0;//记录可能的最大价值
	ll minvolume = INF;//记录价值为Q时最小体积
	for (int i = 1; i <= n; ++i) cin >> w[i] >> q[i];
	for (int i = 1; i <= n; ++i)
	{
		for (int j = Q; j >= q[i]; --j)
		{
			if (dp[j] == INF && dp[j - q[i]] == INF) dp[j] = INF;//无解
			else {//有解
				dp[j] = min(dp[j], dp[j - q[i]] + w[i]);
				if (dp[j] <= W) {//不能超过背包容量
					maxvalue = max(maxvalue, (ll)j);
					if (j == Q) minvolume = min(minvolume, dp[j]);
				}
			}
		}
	}
	if (maxvalue < Q || minvolume == INF) {
		cout << "No" << endl;
		cout << maxvalue << endl;
	}
	else {
		cout << "Yes" << endl;
		cout << minvolume << endl;
	}
	return 0;
}