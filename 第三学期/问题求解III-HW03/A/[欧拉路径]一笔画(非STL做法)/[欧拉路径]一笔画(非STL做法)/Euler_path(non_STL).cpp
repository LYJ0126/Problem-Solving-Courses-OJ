#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;

int n, m, x, y, t = 0;//t��¼���±�
int path[2000010];
int deg[100009], odd = 0, start = -1;
//��ʽǰ����
int head[100009], cnt = 0;
//cntΪ�ߵı��,��2��ʼ��������һ��������:��Ϊ������������һ�𽨵�,����cnt��ż��,����cnt^1������֮��Ӧ����һ����(�����)
//���
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
void add(int u, int v)//u,v֮�佨�������
{
	e[++cnt].to = v;
	e[cnt].next = head[u];
	e[head[u]].last = (head[u] == 0) ? 0 : cnt;//���head[u]==0,˵��uû�б�,��ôlast����0,�������cnt
	head[u] = cnt;
	e[++cnt].to = u;
	e[cnt].next = head[v];
	e[head[v]].last = (head[v] == 0) ? 0 : cnt;//ͬ��
	head[v] = cnt;
}
void delete_edge(int u, int v, int id)//ɾ����(u,v)�����Ϊid
{
	int opedge = 0;//����߱��
	if (id & 1) opedge = id + 1;//idΪ����������߱��Ϊid+1
	else opedge = id - 1;//idΪż��������߱��Ϊid-1
	if(head[u]==id) head[u] = e[id].next;//���Ҫɾ���ı���ͷ��㣬��ôͷ���ͱ����һ����
	else {
		e[e[id].last].next = e[id].next;//����Ҫɾ���ıߵ���һ���ߵ�next�ͱ��Ҫɾ���ıߵ���һ����
		e[e[id].next].last = e[id].last;//Ҫɾ���ıߵ���һ���ߵ�last�ͱ��Ҫɾ���ıߵ���һ����
	}
	//ͬ��
	if(head[v]==opedge) head[v] = e[opedge].next;
	else {
		e[e[opedge].last].next = e[opedge].next;
		e[e[opedge].next].last = e[opedge].last;
	}
}
//��ŷ����(��·)
void findpath(int u)
{
	for (int i = head[u]; i; i = e[i].next) {//����u�����б�
		if (head[u] == 0) break;//���uû�б��ˣ����˳�
		int v = e[i].to;
		delete_edge(u, v, i);//ɾ����(u,v)
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
		deg[x]++;//��x�ȼ�һ
		deg[y]++;//��y�ȼ�һ
	}
	for (int i = 1; i <= n; ++i) {
		if (deg[i] & 1) {//������ȶ���
			odd++;
			start = i;
		}
	}
	if (odd > 2) {
		printf("NO");
		return 0;
	}
	if (odd == 0) start = 1;//ȫ��ż�ȶ��㣬����ŷ����·����ȡһ��Ϊ���(����ȡ1)
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