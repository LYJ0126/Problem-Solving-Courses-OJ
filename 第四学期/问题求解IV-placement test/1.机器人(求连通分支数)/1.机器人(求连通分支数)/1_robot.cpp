#include<iostream>
#include<cmath>
#include<vector>
#include<unordered_map>
using namespace std;

int n, m, k;
vector<vector<int>>graph;
vector<int>pa;//���鼯��������
typedef long long ll;
int findpa(int id) {//���鼯����
	if (pa[id] == id) return id;
	return pa[id] = findpa(pa[id]);
}
void merge(int x, int y) {//���鼯�ϲ�
	int pa_x = findpa(x);
	int pa_y = findpa(y);
	if (pa_x != pa_y) {
		pa[pa_y] = pa_x;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	graph.resize(n * m);//��ʼ��
	pa.resize(n * m);
	for (int i = 0; i < n * m; ++i) {//��ʼ�����鼯
		pa[i] = i;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m - 1; ++j) {
			int connect;
			cin >> connect;
			if (connect) {//����ͼ
				graph[i * m + j].push_back(i * m + j + 1);
				graph[i * m + j + 1].push_back(i * m + j);
				merge(i * m + j, i * m + j + 1);//�ϲ���ͨ�ĵ�
			}
		}
	}
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < m; ++j) {
			int connect;
			cin >> connect;
			if (connect) {//����ͼ
				graph[i * m + j].push_back((i + 1) * m + j);
				graph[(i + 1) * m + j].push_back(i * m + j);
				merge(i * m + j, (i + 1) * m + j);//�ϲ���ͨ�ĵ�
			}
		}
	}
	unordered_map<int, ll>mp;
	int x, y;
	for (int i = 0; i < k; ++i) {
		cin >> x >> y;
		mp[findpa((x - 1) * m + y - 1)]++;//ͳ��ÿ����ͨ��֧�ĵ�ĸ���
	}
	ll ans = 0;
	for (auto& p : mp) {
		ans += p.second * p.second;//����ÿ����ͨ��֧�ĵ�ĸ�����ƽ���ĺͣ���Ϊ��
	}
	cout << ans << endl;
	return 0;
}