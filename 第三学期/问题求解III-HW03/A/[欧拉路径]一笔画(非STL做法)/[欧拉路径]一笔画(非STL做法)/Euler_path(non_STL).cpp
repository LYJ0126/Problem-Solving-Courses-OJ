#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;

int n, m, x, y, t = 0;//t记录答案下标
int path[2000010];
int deg[100009], odd = 0, start = -1;
//链式前向星
int head[100009], cnt = 0;
//cnt为边的编号,从2开始。这样有一个特殊性:因为建边是两条边一起建的,所以cnt是偶数,而且cnt^1就是与之对应的另一条边(反向边)
//快读
inline int quickread() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1; 
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0'; 
		ch = getchar();
	}
	return x * f; 
}
struct edge
{
	int to, next, last;
}e[2000010];
void add(int u, int v)//u,v之间建立无向边
{
	e[++cnt].to = v;
	e[cnt].next = head[u];
	e[head[u]].last = (head[u] == 0) ? 0 : cnt;//如果head[u]==0,说明u没有边,那么last就是0,否则就是cnt
	head[u] = cnt;
	e[++cnt].to = u;
	e[cnt].next = head[v];
	e[head[v]].last = (head[v] == 0) ? 0 : cnt;//同理
	head[v] = cnt;
}
void delete_edge(int u, int v, int id)//删除边(u,v)，编号为id
{
	int opedge = 0;//反向边编号
	if (id & 1) opedge = id + 1;//id为奇数，反向边编号为id+1
	else opedge = id - 1;//id为偶数，反向边编号为id-1
	if(head[u]==id) head[u] = e[id].next;//如果要删除的边是头结点，那么头结点就变成下一条边
	else {
		e[e[id].last].next = e[id].next;//否则，要删除的边的上一条边的next就变成要删除的边的下一条边
		e[e[id].next].last = e[id].last;//要删除的边的下一条边的last就变成要删除的边的上一条边
	}
	//同理
	if(head[v]==opedge) head[v] = e[opedge].next;
	else {
		e[e[opedge].last].next = e[opedge].next;
		e[e[opedge].next].last = e[opedge].last;
	}
}
//找欧拉迹(回路)
void findpath(int u)
{
	for (int i = head[u]; i; i = e[i].next) {//遍历u的所有边
		if (head[u] == 0) break;//如果u没有边了，就退出
		int v = e[i].to;
		delete_edge(u, v, i);//删除边(u,v)
		findpath(v);
	}
	path[++t] = u;
}

int main()
{
	n = quickread(), m = quickread();
	for (int i = 0; i < m; ++i) {
		x = quickread(), y = quickread();
		add(x, y);
		deg[x]++;//点x度加一
		deg[y]++;//点y度加一
	}
	for (int i = 1; i <= n; ++i) {
		if (deg[i] & 1) {//遇到奇度顶点
			odd++;
			start = i;
		}
	}
	if (odd > 2) {
		printf("NO");
		return 0;
	}
	if (odd == 0) start = 1;//全是偶度顶点，则有欧拉回路，任取一点为起点(这里取1)
	findpath(start);
	printf("YES\n");
	for (int i = t; i > 0; i--) printf("%d ", path[i]);
	return 0;
}
/*
input:
4 5
1 2
1 3
1 4
2 3
2 4
output:
YES
2 4 1 3 2 1
*/