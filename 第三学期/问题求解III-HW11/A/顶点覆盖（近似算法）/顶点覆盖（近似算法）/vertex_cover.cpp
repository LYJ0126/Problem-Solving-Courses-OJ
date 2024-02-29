#include<iostream>
#include<cmath>
#include<unordered_map>
#include<cstring>
#include<vector>
using namespace std;

int n, m, x, y;
vector<vector<int>>graph;//邻接表
unordered_map<int, int>mp;//记录哪些边已经被覆盖
int temp[2004];//选入的边
int ans[2004];
int pos = 0;
int main()
{
    cin >> n >> m;
    graph.resize(n + 1);
    for (int i = 0; i < m; ++i) {//建图
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    for (int u = 1; u <= n; ++u) {
        for (int v : graph[u]) {//遍历所有边
            if (!mp[(u << 11) + v]) {
                ans[pos] = (u << 11) + v;//选入边(u,v)
                pos++;
                //u所有邻边全部被覆盖
                for (int vv : graph[u]) {
                    mp[(u << 11) + vv] = 1;
                    mp[(vv << 11) + u] = 1;
                }
                //v所有邻边全部被覆盖
                for (int uu : graph[v]) {
                    mp[(v << 11) + uu] = 1;
                    mp[(uu << 11) + v] = 1;
                }
            }
        }
    }
    cout << pos * 2 << "\n";
    for (int i = 0; i < pos; ++i) cout << (ans[i] >> 11) << ' ' << (ans[i] & 0x7ff) << ' ';
    return 0;
}