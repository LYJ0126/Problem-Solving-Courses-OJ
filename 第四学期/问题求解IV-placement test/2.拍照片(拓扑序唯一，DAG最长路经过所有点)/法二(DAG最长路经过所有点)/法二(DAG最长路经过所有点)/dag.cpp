#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
#include<queue>
#include<unordered_map>
using namespace std;

int T, n, m;
typedef long long ll;
vector<vector<int>>graph;
vector<int>indeg;//���
vector<bool>vis;
unordered_map<int, ll>edge;//��¼��Ȩ(0��ʾû�бߣ�1��ʾ�б�)
vector<int>dp;
int DP(int u) {//���仯�������·������,�������Ϊ���
	if (vis[u]) return dp[u];
	vis[u] = true;
	for (int v : graph[u]) {
		if (edge[u << 18 | v]) dp[u] = max(dp[u], DP(v) + 1);//��uΪ����·��u->v·+��vΪ����·������ȡ���
	}
	return dp[u];
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> n >> m;
		graph.clear();
		graph.resize(n + 1);
		indeg.clear();
		indeg.resize(n + 1, 0);
		vis.clear();
		vis.resize(n + 1, false);
		edge.clear();
		int a, b;
		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			graph[a].push_back(b);//a->b
			++indeg[b];
			edge[(a << 18) | b] = 1;//��¼a->b�ı�Ȩ,1��ʾ�бߡ���Ϊ���ݷ�Χ��1e5,��������λ�����ӹ�ϣ���¼��Ȩ
		}
		int lowest = 0;//�����
		for (int i = 1; i <= n; ++i) {
			if (!indeg[i]) {
				if(!lowest)lowest = i;
				else {//�ж�������
					lowest = 0;
					break;
				}
			}
		}
		if (!lowest) {//û������˻����ж�������
			cout << "NO" << '\n';
			continue;
		}
		//ͨ�����������ж��Ƿ��л�
		queue<int>que;
		que.push(lowest);
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			vis[u] = true;
			for (int v : graph[u]) {
				--indeg[v];
				if (!indeg[v]) {
					que.push(v);
				}
			}
		}
		//�ж��Ƿ��޻�����ͨ
		bool flag = true;
		for (int i = 1; i <= n; ++i) {
			if (indeg[i] || !vis[i]) {
				flag = false;
				break;
			}
		}
		if (!flag) {//�л����߲���ͨ
			cout << "NO" << '\n';
			continue;
		}
		//�ж��·�����Ƿ�Ϊn-1
		//dp
		dp.clear();
		for (int i = 1; i < n; ++i) vis[i] = false;
		dp.resize(n + 1, 0);
		if (DP(lowest) != n - 1) {//�·���Ȳ�Ϊn-1
			cout << "NO" << '\n';
			continue;
		}
		cout << "YES" << '\n';
	}
	return 0;
}