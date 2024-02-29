#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

typedef long long ll;
ll n, k, a[5009], cold[5009], hot[5009];
ll sum[5009];//sum[l,r]表示l+1到r程序在同一块Cache上执行所需时间，这里实现的是前缀和数组
ll dp[5009][2];//dp[i][0]表示第i个程序和前面一个程序使用的Cache不一样，dp[i][1]表示一样
int last[5009];//last[i]保存第i个程序之前最近的一个和i同类型的程序的位置
int main()
{
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	for (int i = 1; i <= k; i++) scanf("%lld", &cold[i]);
	for (int i = 1; i <= k; i++) scanf("%lld", &hot[i]);
	sum[1] = cold[a[1]];
	for (int i = 2; i <= n; i++) {
		if (a[i] == a[i - 1]) sum[i] = sum[i - 1] + hot[a[i]];
		else sum[i] = sum[i - 1] + cold[a[i]];
	}
	for (int i = 1; i <= n; i++) {
		if (last[i] == 0) {
			int temp = i;
			int id = i + 1;
			while (id <= n) {
				if (a[id] == a[temp]) {
					last[id] = temp;
					temp = id;
				}
				id++;
			}
		}
	}
	dp[1][0] = dp[1][1] = cold[a[1]];
	for (int i = 2; i <= n; i++) {
		//先考虑第i个程序没享受到Cache hit，如果后面享受到了，会覆盖这种情况
		dp[i][0] = dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + cold[a[i]];
		//如果享受到了Cache hit
		if (last[i] != 0) {
			if (last[i] == i - 1) {
				dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + hot[a[i]];//和上一个程序同一个Cache
			}
			else {
				dp[i][0] = min(dp[i][0], dp[last[i] + 1][0] + sum[i - 1] - sum[last[i] + 1] + hot[a[i]]);//和上一个程序不同Cache
				//注意last[i]+1必须从0转移过来，因为要让last[i]+1到i-1都换到和last[i]不同的Cache，这样i才能利用last[i]
			}
		}
	}
	ll ans = min(dp[n][0], dp[n][1]);
	printf("%lld", ans);
	return 0;
}