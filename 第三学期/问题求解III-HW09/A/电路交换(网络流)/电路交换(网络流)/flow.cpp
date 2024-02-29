#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
#include<cmath>
using namespace std;

int n, m, s, t, u, v;
const long long inf = 0x7ffffffff;
long long w, ans = 0, dis[520010];
int tot = 1, now[520010], head[520010];

struct node {
    int to, net;
    long long val;
} e[520010];

inline void add(int u, int v, long long w) {//��ʽǰ���Ǵ�ͼ
    e[++tot].to = v;
    e[tot].val = w;
    e[tot].net = head[u];
    head[u] = tot;

    e[++tot].to = u;
    e[tot].val = 0;
    e[tot].net = head[v];
    head[v] = tot;
}

inline int bfs() {  //�ڲ��������й���ֲ�ͼ 
    for (register int i = 1; i <= n; i++) dis[i] = inf;
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    now[s] = head[s];
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (register int i = head[x]; i; i = e[i].net) {
            int v = e[i].to;
            if (e[i].val > 0 && dis[v] == inf) {
                q.push(v);
                now[v] = head[v];
                dis[v] = dis[x] + 1;
                if (v == t) return 1;
            }
        }
    }
    return 0;
}

inline int dfs(int x, long long sum) {  //sum����������·��������Ĺ���
    if (x == t) return sum;
    long long k, res = 0;  //k�ǵ�ǰ��С��ʣ������ 
    for (register int i = now[x]; i && sum; i = e[i].net) {
        now[x] = i;  //��ǰ���Ż� 
        int v = e[i].to;
        if (e[i].val > 0 && (dis[v] == dis[x] + 1)) {
            k = dfs(v, min(sum, e[i].val));
            if (k == 0) dis[v] = inf;  //��֦��ȥ��������ϵĵ� 
            e[i].val -= k;
            e[i ^ 1].val += k;
            res += k;  //res��ʾ�����õ�����������ͣ��൱�������������� 
            sum -= k;  //sum��ʾ�����õ��ʣ������ 
        }
    }
    return res;
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%lld", &u, &v, &w);
        add(u, v, w);
    }
    while (bfs()) {
        ans += dfs(s, inf);
    }
    printf("%lld", ans);
    return 0;
}

/*
input:
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 30
output:
50
*/