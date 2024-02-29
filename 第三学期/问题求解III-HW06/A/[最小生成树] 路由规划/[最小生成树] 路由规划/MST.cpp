#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

typedef long long ll;
int n, m, x, y;
ll w, ans = 0;
vector<int>pa;//���鼯�ĸ������飬�ж������Ƿ���ͨ
class node
{
public:
    int u, v;
    ll weight;//��㣬�յ㣬Ȩ
}edge[300009];
//���鼯ģ��
//Ѱ������
int findpa(int id)
{
    if (pa[id] == id) return id;
    else return pa[id] = findpa(pa[id]);
}
void merge(int u1, int u2)
{
    int pu1 = findpa(u1);
    int pu2 = findpa(u2);
    pa[pu2] = pu1;
}
int main()
{
    cin >> n >> m;
    pa.resize(n + 1);
    for (int i = 0; i <= n; i++) pa[i] = i;//��ʼ�����鼯��������
    for (int i = 0; i < m; i++) {
        scanf("%d%d%lld", &x, &y, &w);
        edge[i].u = x;
        edge[i].v = y;
        edge[i].weight = -w;//ȡ��
    }
    sort(edge, edge + m, [&](node a, node b) {return a.weight < b.weight; });//����Ȩ����
    int k = 0, j = 0;//k��ʾ�����˶������ߣ�j��ʾ��ǰ�����
    while (k < n - 1) {
        int v1 = findpa(edge[j].u);
        int v2 = findpa(edge[j].v);
        if (v1 != v2) {//���ñ����˵����½�ͼ�в���ͨ
            merge(v1, v2);//���˵�ͨ��(v1,v2)��ͨ
            ans += edge[j].weight;
            k++;//�¼���һ����

        }
        j++;
    }
    printf("%lld", -ans);
    return 0;
}

/*
4 5
1 2 2
1 3 2
1 4 3
2 3 4
3 4 3

10
*/