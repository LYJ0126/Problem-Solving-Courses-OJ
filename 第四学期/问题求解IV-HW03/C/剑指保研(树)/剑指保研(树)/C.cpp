#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

int n, a[500005], q;
vector<vector<int>>tree;
vector<pair<int, int>>modify;//��¼�޸Ĳ����Լ�ʱ���(�ؼ���Ҫ��¼ʱ���)
void dfs(int u, int Time, int val)//dfs����ͳһ�޸Ĵ���
{
	if (Time == 0)//��ǰʱ���Ϊ0��˵��ǰ��û���޸Ĳ���
	{
		if (modify[u].second > Time) {//��ǰ�ڵ㱻�޸ģ�����Ϊ�޸��������ڵ�
			a[u] = modify[u].first;//�޸ĵ�ǰ�ڵ��Ȩֵ
			for (int v : tree[u]) dfs(v, modify[u].second, modify[u].first);//�ݹ��޸�����
		}
		else for (int v : tree[u]) dfs(v, Time, val);//��ǰ�ڵ�û�б��޸ģ��ݹ�����
	}
	else {//��ǰʱ�����Ϊ0,˵��ǰ�����޸Ĳ���
		if (modify[u].second > Time) {//��ǰ�ڵ�����֮ǰ���޸Ĳ���
			a[u] = modify[u].first;//�޸ĵ�ǰ�ڵ��Ȩֵ
			for (int v : tree[u]) dfs(v, modify[u].second, modify[u].first);//�ݹ��޸�����
		}
		else {//��ǰ�ڵ�����֮ǰ���޸Ĳ���,����������
			a[u] = val;//�޸ĵ�ǰ�ڵ��Ȩֵ
			for (int v : tree[u]) dfs(v, Time, val);//�ݹ��޸�����
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	tree.resize(n + 1);
	modify.resize(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];//����Ȩֵ
		modify[i] = make_pair(a[i], 0);//��¼��ʼȨֵ,ʱ���Ϊ0
	}
	int parent;
	for (int i = 2; i <= n; ++i) {//����
		cin >> parent;
		tree[parent].push_back(i);//parent���ӽڵ���i
	}
	//��Ϊ��ѯ�����ߵģ����Կ����ȼ�¼�����е��޸Ĳ���������ѯ��ʱ����һ����
	cin >> q;
	int x, y;
	for (int i = 1; i <= q; ++i) {
		cin >> x >> y;//��xΪ�����������нڵ�Ȩֵ��Ϊy
		modify[x] = make_pair(y, i);//��¼�޸Ĳ����Լ�ʱ���
	}
	//��ѯ���нڵ��Ȩֵ
	dfs(1, 0, 0);
	for (int i = 1; i <= n; ++i) cout << a[i] << " ";
	return 0;
}