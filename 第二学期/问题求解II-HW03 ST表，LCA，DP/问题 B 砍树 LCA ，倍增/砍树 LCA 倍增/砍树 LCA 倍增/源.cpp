#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN = 100008;
vector<int>v[MAXN];
int n, m, x, y;
int depth[MAXN], anc[MAXN][20], coloru[MAXN], colorv[MAXN];//depth����ڵ���ȣ�ancΪ��������
int edge[MAXN];//edge���������ĸ��׽��֮��ߵı��
struct node
{
    int value, dep;
};
bool cmp(node x, node y) {
    return x.dep > y.dep;
}
void build(int x, int fa)
{
    // ������ x ʱ x ���������ȶ��Ѿ������ʹ���anc �����ѱ�����
    // ������ھͿ��Լ��� x �� anc ����
    anc[x][0] = fa;
    for (int i = 1; i <= 19; i++)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
    // ����
    for (int y : v[x])
        if (y != fa)   // ���ڵĽڵ㲻�Ǹ��ף��Ǿ��Ǻ��ӣ���������
        {
            depth[y] = depth[x] + 1;
            build(y, x); // y �� x �ĺ��ӣ�x �� y �ĸ���
        }
}
int find_lca(int x, int y)
{
    if (depth[x] < depth[y]) swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (depth[anc[x][i]] >= depth[y])
            x = anc[x][i];
    // ��ʱ�� depth[x] = depth[y]
    if (x == y) return x;
    for (int i = 19; i >= 0; i--)
        if (anc[x][i] != anc[y][i])
        {
            x = anc[x][i];
            y = anc[y][i];
        }
    // ע�ⲻ�Ⱥ���������ʱ x, y һ������ LCA �ĺ���, LCA = anc[x][0] = anc[y][0]
    return anc[x][0];
}
int main()
{
    scanf("%d%d", &n, &m);
    edge[1] = 0;
    for (int i = 1; i <= n - 1; i++) {

        scanf("%d%d", &x, &y);
        edge[y] = i;
        v[x].push_back(y);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        coloru[i] = x;
        colorv[i] = y;
    }
    build(1, 0);
    //����·����
    int n1 = coloru[1], n2 = colorv[1];
    bool flag = true;
    for (int i = 2; i <= m; i++) {
        node p1, p2, p3, p4;
        p1.value = find_lca(n1, coloru[i]);
        p1.dep = depth[p1.value];
        p2.value = find_lca(n1, colorv[i]);
        p2.dep = depth[p2.value];
        p3.value = find_lca(n2, coloru[i]);
        p3.dep = depth[p3.value];
        p4.value = find_lca(n2, colorv[i]);
        p4.dep = depth[p4.value];
        node temparray[4] = { p1,p2,p3,p4 };
        sort(temparray, temparray + 4, cmp);
        n1 = temparray[0].value;
        n2 = temparray[1].value;
        if (n1 == n2) {
            flag = false;
            break;
        }
    }
    if (flag) {//���ڽ���Ѱ������
        int maximumbian = -1;
        int father = find_lca(n1, n2);
        int t = n1;
        while (t != father) {
            if (edge[t] > maximumbian) {
                maximumbian = edge[t];
            }
            t = anc[t][0];
        }
        t = n2;
        while (t != father) {
            if (edge[t] > maximumbian) {
                maximumbian = edge[t];
            }
            t = anc[t][0];
        }
        printf("%d", maximumbian);
    }
    else printf("-1");
    return 0;
}