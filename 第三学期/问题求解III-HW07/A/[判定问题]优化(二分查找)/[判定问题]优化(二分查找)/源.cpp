#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long ll;
int n, k;
ll a[100009];
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
    sort(a, a + n);
    ll startnum = a[0];
    for (int i = 0; i < n; ++i) a[i] -= startnum;//与最小值的差
    ll lleft = 0, rright = a[n - 1];
    ll mid = 0;
    ll s = 0;
    int num = 0;
    while (lleft <= rright) {//二分查找答案
        mid = (lleft + rright) >> 1;
        s = 0, num = 0;
        for (int i = 1; i < n; ++i) {
            if (a[i] - s < mid) num++;
            else s = a[i];
        }
        if (num <= k) {
            lleft = mid + 1;
        }
        else rright = mid - 1;
    }
    printf("%lld", rright);
    return 0;
}

/*
6 2
10 83 9 12 32 13

4
*/