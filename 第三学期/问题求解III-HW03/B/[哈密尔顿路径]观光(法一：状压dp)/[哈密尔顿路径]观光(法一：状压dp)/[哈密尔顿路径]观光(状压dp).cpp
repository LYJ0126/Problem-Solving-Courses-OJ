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
    graph.resize(n, vector<int>(n, -1));//�ڽӾ����ͼ
    dp.resize((1 << n), vector<int>(n, 0x3f3f3f3f));//2^n��״̬
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &y, &w);
        //һ��Ҫע��������ر�!
        if (graph[x - 1][y - 1] >= 0) graph[x - 1][y - 1] = graph[y - 1][x - 1] = min(graph[x - 1][y - 1], w);
        else graph[x - 1][y - 1] = graph[y - 1][x - 1] = w;
    }
    //��ʼ����ֻ��һ�����·������Ϊ0
    for (int i = 0; i < n; i++) dp[1 << i][i] = 0;
    int len = (1 << n) - 1;
    for (int state = 1; state <= len; state++) {//ö������״̬
        for (int u = 0; u < n; u++) {//�оٵ�ǰ��
            for (int v = 0; v < n; v++) {//�о���һ����v
                if (!((state >> v) & 1)) {//��v�����߹��ĵ㣬dp[state][v]�������ߡ�Ҫ��state�ﲻ����v
                    if (graph[u][v] >= 0) {
                        //��u,v����·ʱ�����Ŀǰ״̬���һ����uָ��v��·�������ԭ���İ���v��״̬�µ�·���̣�����
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