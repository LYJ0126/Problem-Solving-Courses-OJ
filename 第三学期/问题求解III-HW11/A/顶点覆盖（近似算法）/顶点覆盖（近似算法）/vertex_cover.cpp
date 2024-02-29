#include<iostream>
#include<cmath>
#include<unordered_map>
#include<cstring>
#include<vector>
using namespace std;

int n, m, x, y;
vector<vector<int>>graph;//�ڽӱ�
unordered_map<int, int>mp;//��¼��Щ���Ѿ�������
int temp[2004];//ѡ��ı�
int ans[2004];
int pos = 0;
int main()
{
    cin >> n >> m;
    graph.resize(n + 1);
    for (int i = 0; i < m; ++i) {//��ͼ
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    for (int u = 1; u <= n; ++u) {
        for (int v : graph[u]) {//�������б�
            if (!mp[(u << 11) + v]) {
                ans[pos] = (u << 11) + v;//ѡ���(u,v)
                pos++;
                //u�����ڱ�ȫ��������
                for (int vv : graph[u]) {
                    mp[(u << 11) + vv] = 1;
                    mp[(vv << 11) + u] = 1;
                }
                //v�����ڱ�ȫ��������
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