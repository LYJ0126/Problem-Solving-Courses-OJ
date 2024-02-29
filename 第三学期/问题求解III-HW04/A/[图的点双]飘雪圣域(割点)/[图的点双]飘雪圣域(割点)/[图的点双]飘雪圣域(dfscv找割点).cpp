#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;

vector<int>ans;
vector<vector<int>>graph;
vector<int>times, d, low, parent, children;
vector<bool>visited;
vector<bool>iscut;
int n, m, x, y;
void dfscv(int u, int& times)
{
	//d记录的是每个结点访问的时间戳
	//low记录的是记录该顶点及其后代顶点通过后向边关联的邻点的最小d(时间戳)值
	//parent记录每个顶点前一个访问的顶点(父借点),根节点的parent记为-1
	//children记录每个顶点的子顶点个数
	times++;//访问次数(点数)加一
	d[u] = times;//当前点的访问时间戳为当前times
	low[u] = d[u];//目前将low记为d[u]，即向前访问最多只能到自己
	visited[u] = true;//u已经被访问过
	for (int v : graph[u]) {//dfs遍历
		if (!visited[v]) {//v没有被访问过，(u,v)是树边
			parent[v] = u;//u是v的父节点
			children[u]++;//u子顶点个数加一
			dfscv(v, times);//dfs递归执行
			low[u] = min(low[u], low[v]);//回退的时候，low[u]要和low[v]比较，看谁的后向边能指向更早的祖先
			if (parent[u] == -1 && children[u] >= 2) {//当u是根节点且dfs树含至少两个子树时，说明u是割点
				iscut[u] = true;
			}
			else if (parent[u] >= 0 && low[v] >= d[u]) {//u不是根节点，且v及v的后代没有能访问到u的祖先的，
				//即不存在从u后代指向u祖先的后向边，那么u是割点
				iscut[u] = true;
			}
		}
		//v被访问过，(u,v)是后向边。若v是u父节点，在递归回退时会对v.low进行更新。
		//若v不是u父节点，更新v.low，看u和v谁能指向更早的节点。这里不写low[v]，是因为还没回退到v，low[v]==d[v]。
		else if (v != parent[u]) low[u] = min(low[u], d[v]);
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	graph.resize(n + 1);
	times.resize(n + 1);
	d.resize(n + 1);
	low.resize(n + 1);
	parent.resize(n + 1);
	children.resize(n + 1, 0);
	visited.resize(n + 1, false);
	iscut.resize(n + 1, false);
	for (int i = 0; i < m; i++) {
		//建图
		scanf("%d%d", &x, &y);
		graph[x].emplace_back(y);
		graph[y].emplace_back(x);
	}
	for (int i = 1; i <= n; i++) {//对每个没有被搜过的点进行dfscv
		if (!visited[i]) {
			parent[i] = -1;//根节点没有父亲节点
			int times = 0;//时间戳初始化
			dfscv(i, times);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (iscut[i]) ans.push_back(i);
	}
	int len = ans.size();
	printf("%d\n", len);
	sort(ans.begin(), ans.end());
	for (int i = 0; i < len; i++) printf("%d ", ans[i]);
	return 0;
}