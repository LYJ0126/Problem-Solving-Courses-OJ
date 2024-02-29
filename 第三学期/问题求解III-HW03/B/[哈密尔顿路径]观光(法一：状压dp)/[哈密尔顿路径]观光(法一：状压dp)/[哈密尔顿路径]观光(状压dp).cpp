#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

int n, m, x, y, w;
vector<vector<int>>graph;
vector<vector<int>>dp;
int main()
{
    scanf("%d%d", &n, &m);
    graph.resize(n, vector<int>(n, -1));//邻接矩阵存图
    dp.resize((1 << n), vector<int>(n, 0x3f3f3f3f));//2^n个状态
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &y, &w);
        //一定要注意可能有重边!
        if (graph[x - 1][y - 1] >= 0) graph[x - 1][y - 1] = graph[y - 1][x - 1] = min(graph[x - 1][y - 1], w);
        else graph[x - 1][y - 1] = graph[y - 1][x - 1] = w;
    }
    //初始化。只有一个点的路径长度为0
    for (int i = 0; i < n; i++) dp[1 << i][i] = 0;
    int len = (1 << n) - 1;
    for (int state = 1; state <= len; state++) {//枚举所有状态
        for (int u = 0; u < n; u++) {//列举当前点
            for (int v = 0; v < n; v++) {//列举下一个点v
                if (!((state >> v) & 1)) {//若v是已走过的点，dp[state][v]不能再走。要求state里不包含v
                    if (graph[u][v] >= 0) {
                        //当u,v存在路时，如果目前状态添加一条从u指向v的路，相比于原来的包含v的状态下的路更短，更新
                        dp[state | (1 << v)][v] = min(dp[state | (1 << v)][v], dp[state][u] + graph[u][v]);
                    }
                }
            }
        }
    }
    int ans = 0x33333333;
    for (int x = 0; x < n; x++) ans = min(ans, dp[len][x]);
    if (ans == 0x33333333) printf("-1");
    else printf("%d", ans);
    return 0;
}