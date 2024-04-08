#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;

//tips：每个点到根的路径上不同的gcd取值在log_2n数量级,所以在dfs是时候可以存储每个点与其后代结点的gcd值以及个数，
//这样可以加速查询

typedef unsigned long long ull;
const ull mod = 1e9 + 7;
ull n, ans = 0;
vector<ull>p;//记录每个村庄(点)的“繁荣度”
vector<vector<int>>tree;//记录树的结构,1为根节点
vector<vector<ull>>gcds;//记录每个点到后代节点(包括自身)的gcd值和个数,其中gcds[i][j]后17位表示该gcd值的个数，前47位表示gcd值

ull gcd(ull a, ull b) {//求最大公约数
	if (b == 0) return a;
	return gcd(b, a % b);
}

void dfs(int u, int fa)
{
	for (int v : tree[u]) {
		if (v == fa) continue;//不走回头路
		dfs(v, u);
	}
	//将u和其后代结点的gcd值和个数存储起来
	gcds[u].push_back((p[u] << 17) + 1);//添加自身的繁荣度(gcd(p[u],p[u])=p[u])
	ans = (ans + p[u]) % mod;
	//遍历u的子节点(直接后代),计算新的gcd值和个数
	for (int v : tree[u]) {
		if (v == fa) continue;
		int sz = gcds[v].size();
		for (int i = 0; i < sz; ++i) {
			ull g = gcd(p[u], gcds[v][i] >> 17);//计算新的gcd值
			ull cnt = gcds[v][i] & 0x1ffff;//计算该gcd值的个数
			ans = (ans + g * cnt % mod) % mod;
			//将新的gcd值和个数存储起来
			//在gcds[u]中查找是否已经存在该gcd值
			int j = 0, u_sz = gcds[u].size();
			for (; j < u_sz; ++j) {
				if (gcds[u][j] >> 17 == g) {
					gcds[u][j] += cnt;//更新个数
					break;
				}
			}
			if (j == u_sz) gcds[u].push_back((g << 17) + cnt);//添加新的gcd值和个数
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	p.resize(n + 1);
	tree.resize(n + 1);
	gcds.resize(n + 1);
	for (int i = 1; i <= n; ++i) cin >> p[i];
	int u, v;
	for (int i = 1; i < n; ++i) {
		cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	dfs(1, 0);
	cout << ans;
	return 0;
}