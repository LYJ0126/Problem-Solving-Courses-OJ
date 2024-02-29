


//����˼·
/*
��ģ��

    �Ѹ�ͼ���������㶨�򣬼���ÿ�������Ⱥͳ��ȡ������ĳ��������֮��Ϊ��������ô�϶�������ŷ����·�� 
    ��Ϊŷ����·Ҫ��ÿ����� = ���ȣ�Ҳ�����ܶ���Ϊż�������������ȵ�ز�����ŷ����·��

    ���ˣ�����ÿ������Ⱥͳ���֮���Ϊż������ô�����ż������2����x��Ҳ����˵������ÿһ���㣬ֻҪ��x���߸ı䷽��
    ����>�����Ǳ��룬��>����Ǳ���������ܱ�֤�� = �롣���ÿ���㶼�ǳ� = �룬��ô�����ԣ���ͼ�ʹ���ŷ����·��

    ���ڵ�����ͱ���ˣ��Ҹøı���Щ�ߣ�������ÿ����� = �룿����������ģ�͡�

    ���ȣ�������ǲ��ܸı䷽��ģ�Ҫ֮���ã�ɾ��һ��ʼ���ǰ�����߶������𣿶�����ʲô�򣬾Ͱ����繹����ʲô����
    �߳���������1�����½�s��t�������� > ���ĵ�u�����ӱ�(u, t)������Ϊx�����ڳ� > ��ĵ�v�����ӱ�(s, v)��
    ����Ϊx��ע��Բ�ͬ�ĵ�x��ͬ����
    ֮�󣬲쿴��S���������б��Ƿ��������о�������ŷ����·��û�о���û�С�ŷ����·���ĸ����쿴��ֵ���䣬
    ������������ 0��������1����ֵ����0����1���ı߷��򣬾��ܵõ�ÿ����� = ���ȵ�ŷ��ͼ��
    ����������������ÿ���� > ���ĵ㣬����x���߽���������Щ�����ı߷���OK���� = ���ˡ����ڳ� > ��ĵ���Ȼ��
    ��ô��û��s��t���ӵĵ���ô�죿��s���ӵ������ǳ� > �룬��t���ӵ��������� > ������ô�����û��sҲû��t���ӵĵ㣬
    ��Ȼ���ڿ�ʼ���Ѿ������� = ���ˡ���ô�������������У���Щ�����ڡ��м�㡱������֪���м���������������ۻ��ģ�
    ��������ȥ���پͳ������٣�����֮����Ȼ�Ա���ƽ�⡣
��������������������������������
��Ȩ����������ΪCSDN������yangzhongmin21����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/yangzhongmin21/article/details/83986074
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;

int T;
int n, m, s, t, u, v, dir;//dirΪ0����Ϊ1����
const long long inf = 0x7ffffffff;
long long w, ans = 0, dis[52001];
int tot = 1, now[52001], head[52001];
int deg[705];//��Ⱥͳ��ȵĲ�
int pa[705];//�ж���ͨ���õĲ��鼯����

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

inline int bfs() {  //�ڲ��������й���ֲ�ͼ 
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
    scanf("%d", &T);//T����ͼ
    for (int i = 0; i < T; i++)
    {
        bool flag = true;
        ans = 0;
        memset(now, 0, sizeof(now));
        memset(head, 0, sizeof(head));
        memset(deg, 0, sizeof(deg));
        tot = 1;
        scanf("%d%d", &n, &m);//n��,m��
        for (int j = 0; j <= n; ++j) pa[j] = j;//��ʼ�����鼯����
        for (int j = 0; j < m; ++j) {
            scanf("%d%d%d", &u, &v, &dir);
            deg[u]--;
            deg[v]++;
            if (dir == 0) add(u, v, 1);//��������ⶨ�򣬲�����������
            merge(v, u);
        }
        for (int i = 1; i <= n; ++i) {//�ж��Ƿ�����ͨ
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
            if (deg[i] & 1) {//������Ϊ����Ҳ����
                flag = false;
                break;
            }
        }
        if (!flag) {
            printf("impossible\n");
            continue;
        }
        s = 0, t = n + 1;//�½�Դ�ͻ�
        for (int i = 1; i <= n; ++i) {//����������
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