#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

int n, k, x, y;
int dppos[10001], dpneg[10001];
struct node {
    int val;//≤Ó÷µ
    int yi, zheng;
};
node p[105];
vector<node>pos;
vector<node>neg;
vector<int>posmax, negmax;
int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> x >> y;
        int tempval = x - y * k;
        node tempnode;
        tempnode.val = tempval;
        tempnode.yi = x;
        tempnode.zheng = y;
        if (tempval >= 0) pos.push_back(tempnode);
        else neg.push_back(tempnode);
    }
    for (node v : pos) {
        for (int i = 10000; i >= v.val; --i) {
            if (i - v.val == 0 || dppos[i - v.val] != 0) dppos[i] = max(dppos[i], dppos[i - v.val] + v.yi + v.zheng);
        }
    }
    for (node u : neg) {
        for (int i = 10000; i >= -u.val; --i) {
            if (i + u.val == 0 || dpneg[i + u.val] != 0) dpneg[i] = max(dpneg[i], dpneg[i + u.val] + u.yi + u.zheng);
        }
    }
    int ans = dppos[0];
    for (int i = 1; i <= 10000; ++i) {
        if (dppos[i] && dpneg[i]) ans = max(ans, dppos[i] + dpneg[i]);
    }
    cout << ans;
    return 0;
}
/*
3 4
15 3
1 1
5 1

20
*/