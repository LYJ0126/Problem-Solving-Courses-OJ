#include<iostream>
#include<cmath>
#include<queue>
using namespace std;

int T, n, m;
vector<vector<int>>graph;
vector<int>indeg;//���
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
		int lowest = 0;//�����
		for (int i = 1; i <= n; ++i) {
			if (!indeg[i]) {
				if (!lowest) lowest = i;
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
		//��������,�ж��Ƿ��л�,�ж���������Ľ���Ƿ�Ψһ��ͬʱbfs�ж�ͼ�Ƿ���ͨ
		bool flag = true;
		queue<int>que;
		que.push(lowest);
		//bfs
		while (!que.empty()) {
			//���������Ƿ��ж��Ԫ��
			int size = que.size();
			if (size > 1) {//������������Ψһ������ǰ�ж�������
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
		if (!flag) {//������������Ψһ
			cout << "NO" << '\n';
			continue;
		}
		//�ж��Ƿ��л�
		for (int i = 1; i <= n; ++i) {
			if (indeg[i]) {//�л�
				flag = false;
				break;
			}
		}
		if (!flag) {//�л�
			cout << "NO" << '\n';
			continue;
		}
		//�ж�ͼ�Ƿ���ͨ
		for (int i = 1; i <= n; ++i) {
			if (!vis[i]) {//ͼ����ͨ
				flag = false;
				break;
			}
		}
		if (!flag) {//ͼ����ͨ
			cout << "NO" << '\n';
		}
		else {
			cout << "YES" << '\n';
		}
	}
	return 0;
}