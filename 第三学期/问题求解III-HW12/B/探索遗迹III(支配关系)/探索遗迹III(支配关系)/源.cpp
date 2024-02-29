
//更高效的方法是支配树，其代码过于复杂，这里给出暴力的方法
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int n, m, x, y;
vector<vector<int>>graph;
vector<int>visited;
vector<int>res;
int dfs(int u)
{
    visited[u] = 1;
    int sum = 1;
    for (int v : graph[u]) {
        if (!visited[v])
            sum += dfs(v);
    }
    return sum;
}
int main()
{
    cin >> n >> m;
    graph.resize(n + 1);
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        graph[x].push_back(y);
    }
    visited.resize(n + 1);
    cout << n << ' ';
    for (int i = 2; i <= n; ++i)
    {
        visited.assign(n + 1, 0);
        visited[i] = 1;
        cout << n - dfs(1) << ' ';
    }
    return 0;
}
/*
input:
9 10
1 2
2 3
3 4
4 5
2 5
2 6
6 7
7 8
6 9
9 8
output:
9 8 2 1 1 4 1 1 1
*/