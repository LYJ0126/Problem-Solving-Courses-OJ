#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cstring>
#include<unordered_map>
#include<unordered_set>
using namespace std;

int n, m;
string s, t;
const int mod = 998244353;
unordered_set<int>st;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        cin >> s;
        int temp = 0;
        for (char c : s) {
            temp = (temp * 27 + c - 'a' + 1) % mod;
        }
        st.insert(temp);
    }
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        cin >> t;
        int temp = 0;
        for (char c : t) temp = (temp * 27 + c - 'a' + 1) % mod;
        if (st.find(temp) != st.end()) ++ans;
    }
    printf("%d\n", ans);
    return 0;
}