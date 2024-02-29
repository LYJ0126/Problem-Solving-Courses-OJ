#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cstring>
//#include<unordered_map>
#include<unordered_set>
using namespace std;

int n, m;
string s, t;
const int mod = 998244353;
unordered_set<string>st;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        cin >> s;
        st.insert(s);
    }
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        cin >> t;
        if (st.find(t) != st.end()) ++ans;
    }
    printf("%d\n", ans);
    return 0;
}