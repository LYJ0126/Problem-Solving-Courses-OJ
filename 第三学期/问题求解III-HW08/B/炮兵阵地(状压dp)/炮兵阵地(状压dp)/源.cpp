#include <iostream>
#include <vector>
using namespace std;
const int N = 105, M = 1 << 10;
int n, m;
int g[N];
int dp[2][M][M];
int cnt[M];
vector <int> state;
bool check(int x) {
    for (int i = 0; i < m; i++) {
        if ((x >> i & 1) && ((x >> i + 1 & 1) || (x >> i + 2 & 1))) return false;//不合法
    }
    return true;
}
int count(int x) {//这一行被占用的格数量
    int ans = 0;
    for (int i = 0; i < m; i++) ans += x >> i & 1;
    return ans;
}
int main() {
    cin >> n >> m;
    char ch;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> ch;
            if (ch == 'H') g[i] += 1 << j;
        }
    }
    //合法状态
    for (int i = 0; i < 1 << m; i++) {
        if (check(i)) {
            state.push_back(i);
            cnt[i] = count(i);
        }
    }
    for (int i = 1; i <= n + 2; i++) {
        for (int j = 0; j < state.size(); j++) {//本行
            for (int former1 = 0; former1 < state.size(); former1++) {//上一行
                for (int former2 = 0; former2 < state.size(); former2++) {//上两行
                    int a = state[j], b = state[former1], c = state[former2];
                    if ((a & b) | (b & c) | (a & c)) continue;
                    if ((g[i - 1] & a) | (g[i] & b)) continue;
                    dp[i & 1][j][former1] = max(dp[i & 1][j][former1], dp[i - 1 & 1][former2][j] + cnt[b]);
                }
            }
        }
    }
    cout << dp[n + 2 & 1][0][0] << endl;
    return 0;
}

/*
5 4
PHPP
PPHH
PPPP
PHPP
PHHP

6
*/