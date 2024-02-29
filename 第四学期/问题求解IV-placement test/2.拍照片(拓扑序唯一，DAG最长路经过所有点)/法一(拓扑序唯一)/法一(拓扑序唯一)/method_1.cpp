#include<iostream>
#include<cmath>
#include<queue>
using namespace std;

int T, n, m;
vector<vector<int>>graph;
vector<int>indeg;//入度
vector<bool>vis;
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
		int a, b;
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			graph[a].push_back(b);//a->b
			indeg[b]++;
		}
		int lowest = 0;//最矮的人
		for (int i = 1; i <= n; ++i) {
			if (!indeg[i]) {
				if (!lowest) lowest = i;
				else {//有多个最矮的人
					lowest = 0;
					break;
				}
			}
		}
		if (!lowest) {//没有最矮的人或者有多个最矮的人
			cout << "NO" << '\n';
			continue;
		}
		//拓扑排序,判断是否有环,判断拓扑排序的结果是否唯一。同时bfs判断图是否连通
		bool flag = true;
		queue<int>que;
		que.push(lowest);
		//bfs
		while (!que.empty()) {
			//检查队列中是否有多个元素
			int size = que.size();
			if (size > 1) {//拓扑排序结果不唯一，即当前有多个最矮的人
				flag = false;
				break;
			}
			int u = que.front();
			vis[u] = true;
			que.pop();
			while (size--) {
				for (int v : graph[u]) {
					indeg[v]--;
					if (!indeg[v]) {
						que.push(v);
					}
				}
			}
		}
		if (!flag) {//拓扑排序结果不唯一
			cout << "NO" << '\n';
			continue;
		}
		//判断是否有环
		for (int i = 1; i <= n; ++i) {
			if (indeg[i]) {//有环
				flag = false;
				break;
			}
		}
		if (!flag) {//有环
			cout << "NO" << '\n';
			continue;
		}
		//判断图是否连通
		for (int i = 1; i <= n; ++i) {
			if (!vis[i]) {//图不连通
				flag = false;
				break;
			}
		}
		if (!flag) {//图不连通
			cout << "NO" << '\n';
		}
		else {
			cout << "YES" << '\n';
		}
	}
	return 0;
}