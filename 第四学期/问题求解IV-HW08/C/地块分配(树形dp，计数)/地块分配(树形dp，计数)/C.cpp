#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 4;
const ll mod = 1e9 + 7;
//记忆化搜索，dp[i][j]表示第i个节点选择j号码学院的情况下，以i为根的子树搜构成的图的总情况个数
ll dp[maxn][4];
ll n, k;
vector<vector<int>>tree;//构建树
ll dfs(int u, int fa, int c)
{
	if (dp[u][c] >= 0) return dp[u][c];//已经计算过了
	ll ans = 1;
	for (int v : tree[u]) {
		if (v == fa) continue;
		ll sum = 0;
		for (int j = 1; j <= 3; ++j) {
			if (j == c) continue;//相邻节点不同
			sum = (sum + dfs(v, u, j)) % mod;
		}
		ans = (ans * sum) % mod;//每个子结点对应有2种选择，有2^{tree[u].size()}种选择情况，累乘
	}
	return dp[u][c] = ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	tree.resize(n + 1);
	int u, v;
	for (int i = 1; i < n; ++i) {
		cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	memset(dp, -1, sizeof(dp));
	int x, c;
	for (int i = 0; i < k; ++i) {
		cin >> x >> c;
		for (int j = 1; j <= 3; ++j) {
			if (j == c) continue;
			dp[x][j] = 0;//节点x已经被学院c占领，所以不能选择学院j，所以dp[x][j] = 0
		}
	}
	//记忆化搜索
	ll ans = 0;
	for (int i = 1; i <= 3; ++i) {
		if (dp[1][i] == 0) continue;//根节点已经被占领
		ans = (ans + dfs(1, 0, i)) % mod;
	}
	cout << ans << endl;
	return 0;
}