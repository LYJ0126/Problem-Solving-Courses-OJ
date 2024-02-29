#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;

int n, x, y;
int value[100005];
int pa[100005];//���鼯��������
int dp[100005][2];//dp[i][0]��ʾ��ѡi�����ֵ��dp[i][1]��ʾѡi�����ֵ�����ڼ��仯����
vector<vector<int>>graph;
int findpa(int u)
{
    if (pa[u] == u) return u;
    return pa[u] = findpa(pa[u]);
}
void merge(int u, int v)
{
    int pu = findpa(u), pv = findpa(v);
    if (pu == pv) return;
    pa[pv] = pu;
}
int dfs(int u, int choose)//choose��ʾ�Ƿ�ѡu,0��ʾ��ѡ��1��ʾѡ
{
    if (dp[u][choose]) return dp[u][choose];//���仯����
    int sum = 0;
    if (choose) {
        sum += value[u];
        for (int v : graph[u]) {
            sum += dfs(v, false);
        }
    }
    else {
        for (int v : graph[u]) {
            sum += max(dfs(v, true), dfs(v, false));
        }
    }
    return dp[u][choose] = sum;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> value[i];
    graph.resize(n + 1);
    for (int i = 0; i <= n; ++i) pa[i] = i;
    for (int i = 1; i < n; ++i)
    {
        cin >> x >> y;
        graph[x].push_back(y);
        //graph[y].push_back(x);
        merge(x, y);
    }
    int root = findpa(1);//�ҵ����ڵ�
    cout << max(dfs(root, 1), dfs(root, 0));
    return 0;
}
/*
input:
7
1 20 3 4 5 6 7
1 2
1 3
2 4
2 5
3 6
3 7
output:
33
*/