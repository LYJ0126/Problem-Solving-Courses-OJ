#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;

int n, m, f[20008], fa[20008], ans = 0;
//fa����ÿ������Ӧ�ĸ���f��ʾÿ���ﷸ�Ķ����������Ǹ��ﷸ���ڵļ���
struct node
{
	int a, b, c;
}edge[100009];
bool cmp(node u, node v)
{
	return u.c > v.c;
}
/*int getanc(int id)//Ѱ�Ҹ��ڵ㣨�ݹ�д����
{
	if (fa[id] == id) return id;
	return fa[id] = getanc(fa[id]);//���õݹ�ͬʱ���·��ѹ��
}*/
int getanc(int id)//Ѱ�Ҹ��ڵ㣨����д����
{
	int root = fa[id];
	while (root != id) {//���id���Ǹ��ڵ�Ļ�������ѭ��
		id = fa[id];
		root = fa[id];
	}
	//·��ѹ��
	while (id != fa[id]) {
		int nxt = fa[id];
		fa[id] = root;
		id = nxt;
	}
	return root;
}
void merge(int x, int y)//�ϲ�
{
	x = getanc(x);
	y = getanc(y);
	if (x != y) fa[y] = x;
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &edge[i].a, &edge[i].b, &edge[i].c);
	//����Թ��ֵ�Ӵ�С����
	sort(edge + 1, edge + m + 1, cmp);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		if (getanc(edge[i].a) == getanc(edge[i].b)) {//˵����ʱ�����ߵ�������֮ǰ�Ѿ����ֵ���һ���������޷��ٵ��ڡ�
			//��ʱ�𰸾���������Ȩ��
			ans = edge[i].c;
			break;
		}
		else {
			if (f[edge[i].a]) merge(f[edge[i].a], edge[i].b); //��f[edge[i].a]��0����ʾedge[i].a�Ѿ��ж������ϣ����f[edge[i].a]����
			//���Ϻ�edge[i].b���ڼ��Ϻϲ�
			else f[edge[i].a] = edge[i].b;//����˵��edge[i].a��û�ж������ϣ�ǰ��û�г��ֹ���,��edge[i].b�������������
			if (f[edge[i].b]) merge(f[edge[i].b], edge[i].a); //f[edge[i].b]��0��˵��edge[i].b���ж������ϣ����f[edge[i].b]���ڵ�
			//���Ϻ�edge[i].a���ڼ��Ϻϲ�
			else f[edge[i].b] = edge[i].a;//����˵��edge[i].b��û�ж������ϣ�ǰ��û���ֹ�������edge[i].a�������������
		}
	}
	printf("%d", ans);
	return 0;
}