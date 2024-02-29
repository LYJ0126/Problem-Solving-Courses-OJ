#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int inf = 0x3f3f3f3f;
const int dx[] = { -1,1,0,0 };
const int dy[] = { 0,0,-1,1 };
struct Edge
{
    int to, val;
    long long Net;
}e[10005];
int head[5005], tot;
int s, t;
int dep[5005];
int n;
void add(int u, int v, int cap)//��ʽǰ���Ǵ�ͼ,���������Ϊ0
{
    tot++;
    e[tot].to = v;
    e[tot].val = cap;
    e[tot].Net = head[u];
    head[u] = tot;
    tot++;
    e[tot].to = u;
    e[tot].val = 0;
    e[tot].Net = head[v];
    head[v] = tot;
}
bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int>q;
    q.push(s);
    dep[s] = 1;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (int i = head[x]; ~i; i = e[i].Net)
        {
            int y = e[i].to;
            if (e[i].val && !dep[y])
            {
                q.push(y);
                dep[y] = dep[x] + 1;
                if (y == t) return 1;//���ɴ�
            }
        }
    }
    return 0;
}
int dfs(int x, int flow)
{
    if (x == t) return flow;
    int rest = flow, k;
    for (int i = head[x]; ~i && rest; i = e[i].Net)
    {
        int y = e[i].to;
        if (e[i].val && dep[y] == dep[x] + 1)
        {
            k = dfs(y, min(rest, e[i].val));
            if (!k) dep[y] = 0;
            e[i].val -= k;
            e[i ^ 1].val += k;
            rest -= k;
        }
    }
    return flow - rest;
}
int main()
{
    int ans = 0;
    cin >> n;
    tot = 1;
    memset(head, -1, sizeof(head));
    s = 0;//Դ��
    t = n * n + 1;//���
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int val;
            scanf("%d", &val);
            ans += val;
            if ((i + j) & 1) add((i - 1) * n + j, t, val);//������(��ɫ��)��������
            else
            {
                add(s, (i - 1) * n + j, val);//ż����(��ɫ��)��Դ������ָ����
                for (int k = 0; k < 4; k++)
                {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x<1 || x>n || y<1 || y>n) continue;
                    add((i - 1) * n + j, (x - 1) * n + y, inf);//���ڵ�����������
                }
            }
        }
    }
    int sum = 0;
    while (bfs()) sum += dfs(s, inf);
    cout << ans - sum << endl;//�𰸵����ܺͼ�ȥ��С��
    return 0;
}