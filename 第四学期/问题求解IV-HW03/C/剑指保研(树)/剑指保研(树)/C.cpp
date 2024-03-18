#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

int n, a[500005], q;
vector<vector<int>>tree;
vector<pair<int, int>>modify;//记录修改操作以及时间戳(关键是要记录时间戳)
void dfs(int u, int Time, int val)//dfs进行统一修改处理
{
	if (Time == 0)//当前时间戳为0，说明前面没有修改操作
	{
		if (modify[u].second > Time) {//当前节点被修改，并且为修改子树根节点
			a[u] = modify[u].first;//修改当前节点的权值
			for (int v : tree[u]) dfs(v, modify[u].second, modify[u].first);//递归修改子树
		}
		else for (int v : tree[u]) dfs(v, Time, val);//当前节点没有被修改，递归子树
	}
	else {//当前时间戳不为0,说明前面有修改操作
		if (modify[u].second > Time) {//当前节点晚于之前的修改操作
			a[u] = modify[u].first;//修改当前节点的权值
			for (int v : tree[u]) dfs(v, modify[u].second, modify[u].first);//递归修改子树
		}
		else {//当前节点早于之前的修改操作,操作被覆盖
			a[u] = val;//修改当前节点的权值
			for (int v : tree[u]) dfs(v, Time, val);//递归修改子树
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
		cin >> a[i];//输入权值
		modify[i] = make_pair(a[i], 0);//记录初始权值,时间戳为0
	}
	int parent;
	for (int i = 2; i <= n; ++i) {//建树
		cin >> parent;
		tree[parent].push_back(i);//parent的子节点有i
	}
	//因为查询是离线的，所以可以先记录下所有的修改操作，最后查询的时候再一起处理
	cin >> q;
	int x, y;
	for (int i = 1; i <= q; ++i) {
		cin >> x >> y;//以x为根的子树所有节点权值改为y
		modify[x] = make_pair(y, i);//记录修改操作以及时间戳
	}
	//查询所有节点的权值
	dfs(1, 0, 0);
	for (int i = 1; i <= n; ++i) cout << a[i] << " ";
	return 0;
}