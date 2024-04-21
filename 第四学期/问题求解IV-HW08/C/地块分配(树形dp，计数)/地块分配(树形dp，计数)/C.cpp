#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 4;
const ll mod = 1e9 + 7;
//���仯������dp[i][j]��ʾ��i���ڵ�ѡ��j����ѧԺ������£���iΪ���������ѹ��ɵ�ͼ�����������
ll dp[maxn][4];
ll n, k;
vector<vector<int>>tree;//������
ll dfs(int u, int fa, int c)
{
	if (dp[u][c] >= 0) return dp[u][c];//�Ѿ��������
	ll ans = 1;
	for (int v : tree[u]) {
		if (v == fa) continue;
		ll sum = 0;
		for (int j = 1; j <= 3; ++j) {
			if (j == c) continue;//���ڽڵ㲻ͬ
			sum = (sum + dfs(v, u, j)) % mod;
		}
		ans = (ans * sum) % mod;//ÿ���ӽ���Ӧ��2��ѡ����2^{tree[u].size()}��ѡ��������۳�
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
			dp[x][j] = 0;//�ڵ�x�Ѿ���ѧԺcռ�죬���Բ���ѡ��ѧԺj������dp[x][j] = 0
		}
	}
	//���仯����
	ll ans = 0;
	for (int i = 1; i <= 3; ++i) {
		if (dp[1][i] == 0) continue;//���ڵ��Ѿ���ռ��
		ans = (ans + dfs(1, 0, i)) % mod;
	}
	cout << ans << endl;
	return 0;
}