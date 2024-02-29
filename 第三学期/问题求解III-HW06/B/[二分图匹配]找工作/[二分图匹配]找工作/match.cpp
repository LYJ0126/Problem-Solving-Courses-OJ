#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
const int INF = 1 << 28;//��ʼ���þ���ֵ
vector<vector<int>>graph;
int cx[20009];//����X�е���ƥ��ĵ�,���õ�û��ƥ��ĵ���Ϊ-1
int cy[20009];//����Y�е���ƥ��ĵ�,���õ�û��ƥ��ĵ���Ϊ-1
//d�ǹ�������·��ʱ�������������δƥ���ľ���  
int d[20009];//��ʾ�ö�������г�����u�����̾��롣������-1
int nx, ny, m, x, y;
int dis;//��ʾ�����ʵ��׸�(�ص㣺�׸�)δ��M���͵ķǸ������d����ֵ
vector<int>visited;//��ÿ����չƥ�伯��ʱ���ڼ�¼ÿ����ķ������
vector<int>setx, sety;//�洢����ͼ��������X,Y

//Ѱ������·��
bool hkinit_and_hkbfs()
{
    queue<int>que;
    //��ʼ��
    dis = INF;
    memset(d, -1, sizeof(d));
    for (int u : setx) {
        if (cx[u] == -1) {//u����X��δ��ƥ��M����
            //��δ�����Ľڵ����,����ʼ���ýڵ����Ϊ0                                                                      
            que.push(u);
            d[u] = 0;
        }
    }
    //���������������·
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (d[u] > dis) break;
        //��Ϊdisһ��ʼ����ΪINF����d[u]����dis�����ʾ�Ѿ�������·��dis�ˣ���Ϊdis�϶��Ǳ��޸Ĺ��˲�ʹ��d[u]>dis��
        //�������bfs�ǶԾ�����зֲ㣬ÿ�ξ���+1
        //ȡ�Ҳඥ��
        for (int v : graph[u]) {
            if (d[v] == -1) {//d[v]==-1:ֻ��vΪ����·��δ�����ĵ�Ž���������
                d[v] = d[u] + 1;//v��Ӧ����Ϊu��Ӧ�����һ
                if (cy[v] == -1) {//cy[v]==-1��ʾ��vΪ�Ҳ�ûƥ��ĵ�,��ǰ��������·
                    dis = d[v];
                }
                else {
                    d[cy[v]] = d[v] + 1;
                    //cy[v]!=-1 ��ʾv�Ѿ���ƥ���ˣ���ʱ�����Ǽ�����Ѱ����·����
                    //������vƥ��ĵ�cy[v]������У�������·��Ϊu-->v-->cy[v]                                                                              
                    que.push(cy[v]);
                }
            }
        }
    }
    return dis != INF;
    //������·������޸�dis���򲻻����INF
}
//����Ѱ��·��
int findpath(int u)//��maxmatch֪��ִ��findpath��u�϶���cx[u]=-1�ģ���δƥ��
{
    visited[u] = 1;
    for (int v : graph[u]) {
        //����õ�û�б������� ���Ҿ���Ϊ��һ�ڵ�+1
        if (!visited[v] && d[v] == d[u] + 1) {
            visited[v] = 1;
            //v�Ѿ���ƥ�䣬��d[v]=dis����d[cy[v]]=dis+1>dis��
            //��ʱu-->v--cy[v]�϶���������·���ϣ���Ϊ�Ѿ�����dis�ˣ����������ڳ���Ϊdis������·����
            if (cy[v] != -1 && d[v] == dis) continue;
            if (cy[v] == -1 || findpath(cy[v])) {
                //���vû��ƥ�䣬��ֱ�ӽ�vƥ���u�����v�Ѿ�ƥ���ˣ����Ҵ�cy[v],Ҳ���Ǵ�v֮ǰ�Ѿ�ƥ���x�еĵ������
                //�����ܹ��ҵ�һ������·����Ҳ��vƥ���u,����ԭ����ƥ��߸ĳɷ�ƥ���,��ƥ��߸ĳ�ƥ��ߡ�ƥ������һ��
                cy[v] = u;
                cx[u] = v;
                return 1;
            }
        }
    }
    return 0;
}
//�õ����ƥ��
int max_match()
{
    int res = 0;
    //��ʼ��cx,cy
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    while (hkinit_and_hkbfs())
    {
        //visited��ʼ��
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
        //sety��Ԫ���±����y�и�nx��ƫ��
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