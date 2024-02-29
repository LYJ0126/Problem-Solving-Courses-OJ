#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;

int n, m, f[20008], fa[20008], ans = 0;
//fa储存每个结点对应的根。f表示每个罪犯的对立集合是那个罪犯所在的集合
struct node
{
	int a, b, c;
}edge[100009];
bool cmp(node u, node v)
{
	return u.c > v.c;
}
/*int getanc(int id)//寻找根节点（递归写法）
{
	if (fa[id] == id) return id;
	return fa[id] = getanc(fa[id]);//利用递归同时完成路径压缩
}*/
int getanc(int id)//寻找根节点（迭代写法）
{
	int root = fa[id];
	while (root != id) {//如果id就是根节点的话不进入循环
		id = fa[id];
		root = fa[id];
	}
	//路径压缩
	while (id != fa[id]) {
		int nxt = fa[id];
		fa[id] = root;
		id = nxt;
	}
	return root;
}
void merge(int x, int y)//合并
{
	x = getanc(x);
	y = getanc(y);
	if (x != y) fa[y] = x;
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &edge[i].a, &edge[i].b, &edge[i].c);
	//按照怨气值从大到小排序
	sort(edge + 1, edge + m + 1, cmp);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		if (getanc(edge[i].a) == getanc(edge[i].b)) {//说明此时这条边的两个人之前已经被分到了一个监狱，无法再调节。
			//此时答案就是这条边权。
			ans = edge[i].c;
			break;
		}
		else {
			if (f[edge[i].a]) merge(f[edge[i].a], edge[i].b); //若f[edge[i].a]非0，表示edge[i].a已经有对立集合，则把f[edge[i].a]所在
			//集合和edge[i].b所在集合合并
			else f[edge[i].a] = edge[i].b;//否则说明edge[i].a还没有对立集合（前面没有出现过）,则edge[i].b代表其对立集合
			if (f[edge[i].b]) merge(f[edge[i].b], edge[i].a); //f[edge[i].b]非0，说明edge[i].b已有对立集合，则把f[edge[i].b]所在的
			//集合和edge[i].a所在集合合并
			else f[edge[i].b] = edge[i].a;//否则说明edge[i].b还没有对立集合（前面没出现过），则edge[i].a代表其对立集合
		}
	}
	printf("%d", ans);
	return 0;
}