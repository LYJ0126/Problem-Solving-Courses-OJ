#include<iostream>
#include<cmath>
#include<vector>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

int n, m, x, y, ans = -1;
bool findans = false;
vector<int>pa;

int findpa(int x)
{
    if (pa[x] == x) return x;
    else return pa[x] = findpa(pa[x]);
}
void merge(int x, int y)
{
    int pax = findpa(x);
    int pay = findpa(y);
    if (pax != pay) pa[y] = pax;
}
int main()
{
    cin >> n >> m;
    pa.resize(n + 1);
    for (int i = 0; i <= n; i++) pa[i] = i;//并查集初始化
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        merge(x, y);
    }
    bool flag = true;
    for (int i = 2; i <= n; i++) {
        if (findpa(i) != findpa(i - 1)) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << findpa(1);
    }
    else cout << -1;
    return 0;
}