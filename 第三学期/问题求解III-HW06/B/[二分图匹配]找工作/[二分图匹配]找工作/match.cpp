#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
const int INF = 1 << 28;//初始设置距离值
vector<vector<int>>graph;
int cx[20009];//集合X中点所匹配的点,若该点没有匹配的点则为-1
int cy[20009];//集合Y中点所匹配的点,若该点没有匹配的点则为-1
//d是广搜增广路径时候用来存与左侧未匹配点的距离  
int d[20009];//表示该顶点和所有出发点u间的最短距离。特殊标记-1
int nx, ny, m, x, y;
int dis;//表示被访问的首个(重点：首个)未被M饱和的非根顶点的d属性值
vector<int>visited;//在每轮扩展匹配集合时用于记录每个点的访问情况
vector<int>setx, sety;//存储二分图两个集合X,Y

//寻找增广路集
bool hkinit_and_hkbfs()
{
    queue<int>que;
    //初始化
    dis = INF;
    memset(d, -1, sizeof(d));
    for (int u : setx) {
        if (cx[u] == -1) {//u属于X且未被匹配M饱和
            //将未遍历的节点入队,并初始化该节点距离为0                                                                      
            que.push(u);
            d[u] = 0;
        }
    }
    //广度优先搜索增广路
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (d[u] > dis) break;
        //因为dis一开始被设为INF，若d[u]大于dis，则表示已经有增广路径dis了（因为dis肯定是被修改过了才使得d[u]>dis）
        //这里调用bfs是对距离进行分层，每次距离+1
        //取右侧顶点
        for (int v : graph[u]) {
            if (d[v] == -1) {//d[v]==-1:只有v为增广路径未经过的点才进入计算距离
                d[v] = d[u] + 1;//v对应距离为u对应距离加一
                if (cy[v] == -1) {//cy[v]==-1表示若v为右侧没匹配的点,则当前即是增广路
                    dis = d[v];
                }
                else {
                    d[cy[v]] = d[v] + 1;
                    //cy[v]!=-1 表示v已经被匹配了，这时候我们继续搜寻增广路径，
                    //并将与v匹配的点cy[v]放入队列，即增广路径为u-->v-->cy[v]                                                                              
                    que.push(cy[v]);
                }
            }
        }
    }
    return dis != INF;
    //有增广路径则会修改dis，则不会等于INF
}
//深搜寻找路径
int findpath(int u)//由maxmatch知道执行findpath的u肯定是cx[u]=-1的，即未匹配
{
    visited[u] = 1;
    for (int v : graph[u]) {
        //如果该点没有被遍历过 并且距离为上一节点+1
        if (!visited[v] && d[v] == d[u] + 1) {
            visited[v] = 1;
            //v已经有匹配，且d[v]=dis，则d[cy[v]]=dis+1>dis，
            //此时u-->v--cy[v]肯定不在增广路径上（因为已经超过dis了，而我们是在长度为dis的增广路径）
            if (cy[v] != -1 && d[v] == dis) continue;
            if (cy[v] == -1 || findpath(cy[v])) {
                //如果v没有匹配，则直接将v匹配给u。如果v已经匹配了，并且从cy[v],也就是从v之前已经匹配的x中的点出发，
                //还能能够找到一条增广路，则也将v匹配给u,即将原来的匹配边改成非匹配边,非匹配边改成匹配边。匹配数加一。
                cy[v] = u;
                cx[u] = v;
                return 1;
            }
        }
    }
    return 0;
}
//得到最大匹配
int max_match()
{
    int res = 0;
    //初始化cx,cy
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    while (hkinit_and_hkbfs())
    {
        //visited初始化
        int len = visited.size();
        for (int i = 0; i < len; ++i) visited[i] = 0;
        for (int r : setx) {
            if (cx[r] == -1) res += findpath(r);
        }
    }
    return res;
}
int main()
{
    scanf("%d%d%d", &nx, &ny, &m);
    int n = nx + ny;
    graph.resize(n + 1);
    setx.resize(nx);
    sety.resize(ny);
    visited.resize(n + 1);
    int posx = 0, posy = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        //sety中元素下标相对y有个nx的偏移
        graph[x].emplace_back(y + nx);
        graph[y + nx].emplace_back(x);
    }
    for (int i = 0; i < nx; ++i) setx[i] = i + 1;
    for (int i = 0; i < ny; ++i) sety[i] = nx + i + 1;
    int ans = max_match();
    printf("%d", ans);
    return 0;
}

/*
4 4 6
1 1
2 1
3 1
4 1
1 3
2 2

3
*/