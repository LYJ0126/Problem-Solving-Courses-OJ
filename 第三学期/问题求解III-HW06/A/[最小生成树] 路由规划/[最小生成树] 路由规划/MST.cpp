#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

typedef long long ll;
int n, m, x, y;
ll w, ans = 0;
vector<int>pa;//并查集的辅助数组，判断两点是否连通
class node
{
public:
    int u, v;
    ll weight;//起点，终点，权
}edge[300009];
//并查集模板
//寻找祖先
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
    for (int i = 0; i <= n; i++) pa[i] = i;//初始化并查集辅助数组
    for (int i = 0; i < m; i++) {
        scanf("%d%d%lld", &x, &y, &w);
        edge[i].u = x;
        edge[i].v = y;
        edge[i].weight = -w;//取负
    }
    sort(edge, edge + m, [&](node a, node b) {return a.weight < b.weight; });//按边权排序
    int k = 0, j = 0;//k表示加入了多少条边，j表示当前边序号
    while (k < n - 1) {
        int v1 = findpa(edge[j].u);
        int v2 = findpa(edge[j].v);
        if (v1 != v2) {//当该边两端点在新建图中不连通
            merge(v1, v2);//两端点通过(v1,v2)连通
            ans += edge[j].weight;
            k++;//新加了一条边

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