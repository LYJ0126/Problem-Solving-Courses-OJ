


//解题思路
/*
建模：

    把该图的无向边随便定向，计算每个点的入度和出度。如果有某个点出入度之差为奇数，那么肯定不存在欧拉回路。 
    因为欧拉回路要求每点入度 = 出度，也就是总度数为偶数，存在奇数度点必不能有欧拉回路。

    好了，现在每个点入度和出度之差均为偶数。那么将这个偶数除以2，得x。也就是说，对于每一个点，只要将x条边改变方向
    （入>出就是变入，出>入就是变出），就能保证出 = 入。如果每个点都是出 = 入，那么很明显，该图就存在欧拉回路。

    现在的问题就变成了：我该改变哪些边，可以让每个点出 = 入？构造网络流模型。

    首先，有向边是不能改变方向的，要之无用，删。一开始不是把无向边定向了吗？定的是什么向，就把网络构建成什么样，
    边长容量上限1。另新建s和t。对于入 > 出的点u，连接边(u, t)、容量为x，对于出 > 入的点v，连接边(s, v)，
    容量为x（注意对不同的点x不同）。
    之后，察看从S发出的所有边是否满流。有就是能有欧拉回路，没有就是没有。欧拉回路是哪个？察看流值分配，
    将所有流量非 0（上限是1，流值不是0就是1）的边反向，就能得到每点入度 = 出度的欧拉图。
    由于是满流，所以每个入 > 出的点，都有x条边进来，将这些进来的边反向，OK，入 = 出了。对于出 > 入的点亦然。
    那么，没和s、t连接的点怎么办？和s连接的条件是出 > 入，和t连接的条件是入 > 出，那么这个既没和s也没和t连接的点，
    自然早在开始就已经满足入 = 出了。那么在网络流过程中，这些点属于“中间点”。我们知道中间点流量不允许有累积的，
    这样，进去多少就出来多少，反向之后，自然仍保持平衡。
————————————————
版权声明：本文为CSDN博主「yangzhongmin21」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/yangzhongmin21/article/details/83986074
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;

int T;
int n, m, s, t, u, v, dir;//dir为0无向，为1有向
const long long inf = 0x7ffffffff;
long long w, ans = 0, dis[52001];
int tot = 1, now[52001], head[52001];
int deg[705];//入度和出度的差
int pa[705];//判断连通性用的并查集数组

struct node {
    int to, net;
    long long val;
} e[52001];

inline void add(int u, int v, long long w) {
    e[++tot].to = v;
    e[tot].val = w;
    e[tot].net = head[u];
    head[u] = tot;

    e[++tot].to = u;
    e[tot].val = 0;
    e[tot].net = head[v];
    head[v] = tot;
}

inline int bfs() {  //在残量网络中构造分层图 
    for (register int i = 0; i <= n + 1; i++) dis[i] = inf;
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

inline int dfs(int x, long long sum) {  //sum是整条增广路对最大流的贡献
    if (x == t) return sum;
    long long k, res = 0;  //k是当前最小的剩余容量 
    for (register int i = now[x]; i && sum; i = e[i].net) {
        now[x] = i;  //当前弧优化 
        int v = e[i].to;
        if (e[i].val > 0 && (dis[v] == dis[x] + 1)) {
            k = dfs(v, min(sum, e[i].val));
            if (k == 0) dis[v] = inf;  //剪枝，去掉增广完毕的点 
            e[i].val -= k;
            e[i ^ 1].val += k;
            res += k;  //res表示经过该点的所有流量和（相当于流出的总量） 
            sum -= k;  //sum表示经过该点的剩余流量 
        }
    }
    return res;
}

int findpa(int x) {
    if (x == pa[x]) return x;
    return pa[x] = findpa(pa[x]);
}
void merge(int x, int y) {
    int px = findpa(x);
    int py = findpa(y);
    if (px != py) pa[py] = px;

}
int main()
{
    scanf("%d", &T);//T组混合图
    for (int i = 0; i < T; i++)
    {
        bool flag = true;
        ans = 0;
        memset(now, 0, sizeof(now));
        memset(head, 0, sizeof(head));
        memset(deg, 0, sizeof(deg));
        tot = 1;
        scanf("%d%d", &n, &m);//n点,m边
        for (int j = 0; j <= n; ++j) pa[j] = j;//初始化并查集数组
        for (int j = 0; j < m; ++j) {
            scanf("%d%d%d", &u, &v, &dir);
            deg[u]--;
            deg[v]++;
            if (dir == 0) add(u, v, 1);//无向边任意定向，并构建流网络
            merge(v, u);
        }
        for (int i = 1; i <= n; ++i) {//判断是否弱连通
            if (findpa(i) != findpa(1)) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            printf("impossible\n");
            continue;
        }
        for (int i = 1; i <= n; ++i) {
            if (deg[i] & 1) {//度数差为奇数也不行
                flag = false;
                break;
            }
        }
        if (!flag) {
            printf("impossible\n");
            continue;
        }
        s = 0, t = n + 1;//新建源和汇
        for (int i = 1; i <= n; ++i) {//构建流网络
            if (deg[i] < 0) {
                add(s, i, -deg[i] / 2);
            }
            else if (deg[i] > 0) {
                add(i, t, deg[i] / 2);
                deg[t]++;
            }
        }
        while (bfs()) {
            ans += dfs(s, inf);
        }
        if (ans == deg[t]) printf("possible\n");
        else printf("impossible\n");
    }
    return 0;
}

/*
input:
2
4 4
1 2 0
2 3 0
3 4 0
4 1 1
4 4
1 2 1
3 2 1
3 4 0
1 4 0
output:
possible
impossible
*/