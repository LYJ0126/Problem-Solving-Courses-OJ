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
	//d��¼����ÿ�������ʵ�ʱ���
	//low��¼���Ǽ�¼�ö��㼰��������ͨ������߹������ڵ����Сd(ʱ���)ֵ
	//parent��¼ÿ������ǰһ�����ʵĶ���(�����),���ڵ��parent��Ϊ-1
	//children��¼ÿ��������Ӷ������
	times++;//���ʴ���(����)��һ
	d[u] = times;//��ǰ��ķ���ʱ���Ϊ��ǰtimes
	low[u] = d[u];//Ŀǰ��low��Ϊd[u]������ǰ�������ֻ�ܵ��Լ�
	visited[u] = true;//u�Ѿ������ʹ�
	for (int v : graph[u]) {//dfs����
		if (!visited[v]) {//vû�б����ʹ���(u,v)������
			parent[v] = u;//u��v�ĸ��ڵ�
			children[u]++;//u�Ӷ��������һ
			dfscv(v, times);//dfs�ݹ�ִ��
			low[u] = min(low[u], low[v]);//���˵�ʱ��low[u]Ҫ��low[v]�Ƚϣ���˭�ĺ������ָ����������
			if (parent[u] == -1 && children[u] >= 2) {//��u�Ǹ��ڵ���dfs����������������ʱ��˵��u�Ǹ��
				iscut[u] = true;
			}
			else if (parent[u] >= 0 && low[v] >= d[u]) {//u���Ǹ��ڵ㣬��v��v�ĺ��û���ܷ��ʵ�u�����ȵģ�
				//�������ڴ�u���ָ��u���ȵĺ���ߣ���ôu�Ǹ��
				iscut[u] = true;
			}
		}
		//v�����ʹ���(u,v)�Ǻ���ߡ���v��u���ڵ㣬�ڵݹ����ʱ���v.low���и��¡�
		//��v����u���ڵ㣬����v.low����u��v˭��ָ�����Ľڵ㡣���ﲻдlow[v]������Ϊ��û���˵�v��low[v]==d[v]��
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
		//��ͼ
		scanf("%d%d", &x, &y);
		graph[x].emplace_back(y);
		graph[y].emplace_back(x);
	}
	for (int i = 1; i <= n; i++) {//��ÿ��û�б��ѹ��ĵ����dfscv
		if (!visited[i]) {
			parent[i] = -1;//���ڵ�û�и��׽ڵ�
			int times = 0;//ʱ�����ʼ��
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