#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;

int n, ans = 0, a[26];
string s;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++) {
        s = "";  cin >> s;
        a[s[s.length() - 1] - 'a'] = max(a[s[0] - 'a'] + 1, a[s[s.length() - 1] - 'a']);
    }
    for (int i = 0; i < 26; i++) {
        ans = max(ans, a[i]);
    }
    cout << n - ans;
    return 0;
}