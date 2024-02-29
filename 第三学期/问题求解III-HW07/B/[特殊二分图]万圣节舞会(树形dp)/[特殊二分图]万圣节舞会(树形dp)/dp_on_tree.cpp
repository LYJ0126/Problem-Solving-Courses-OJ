#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, r[100009], l, k, root;
vector<vector<int>>graph;
vector<vector<int>>ans;
vector<int>pa;
int findpa(int x)
{
    if (pa[x] == x) return x;
    return pa[x] = findpa(pa[x]);
}
void merge(int x, int y)
{
    int pax = findpa(x);
    int pay = findpa(y);
    pa[pay] = pax;
}
int dfs(int id, int choose)
{
    int value = 0;
    if (choose == 1) {//选
        if (ans[id][1] != -9999999) value += ans[id][1];
        else {
            value += r[id];
            for (int v : graph[id]) value += dfs(v, 0);
            ans[id][1] = value;
        }
    }
    else {
        if (ans[id][0] != -9999999) value += ans[id][0];
        else {
            for (int v : graph[id]) value += max(dfs(v, 1), dfs(v, 0));
            ans[id][0] = value;
        }
    }
    return value;
}

int main()
{
    scanf("%d", &n);
    graph.resize(n + 1);
    ans.resize(n + 1, vector<int>(2, -9999999));
    pa.resize(n + 1);
    for (int i = 0; i <= n; ++i) pa[i] = i;//并查集初始化

    for (int i = 1; i <= n; ++i) scanf("%d", &r[i]);
    for (int i = 1; i < n; ++i) {
        scanf("%d%d", &l, &k);
        graph[k].push_back(l);//上司指向直接下属
        merge(k, l);
    }
    root = findpa(1);//根节点
    printf("%d", max(dfs(root, 1), dfs(root, 0)));//从根开始搜索，分选或不选两种情况
}

/*
7
1
1
1
1
1
1
1
1 3
2 3
6 4
7 4
4 5
3 5

5
*/