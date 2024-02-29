#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<deque>
using namespace std;

//当最大和子数组长度小于k时，可以利用一个长度为k的滑动窗口，在前缀和数组中查询不同终点的长度不大于k的最大子数组并求出最大值。
// 同时，如果i<k，那么还要考虑包含第一个数的情况
//预处理：原数组每个都减去x再求前缀和,原数组每个都加上x再求前缀和
//小于k时，每次s2[n]-s2[i]
//大于等于k时，预处理，计算好从1到j之间前缀和最小的minimum[i]，那么此时和为s1[n]-minimum[i]+2kx（i==n-k）
//同时还要考虑包含1的情况
typedef long long ll;
deque<int> q;
ll n, k, x;
ll a[100009];
ll s1[100009], minimum[100009], s2[100009];
int main()
{
	scanf("%lld%lld%lld", &n, &k, &x);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		s1[i] = s1[i - 1] + a[i] - x;//前缀和1
		s2[i] = s2[i - 1] + a[i] + x;//前缀和2
		if (i == 1) minimum[i] = s1[i];
		else {
			if (s1[i] < minimum[i - 1]) minimum[i] = s1[i];
			else minimum[i] = minimum[i - 1];
		}
	}
	ll ans1 = 0;
	//当最大子数组长度小于k时，利用单调队列求得最大值
	for (int i = 1; i <= n; i++)
	{
		while (!q.empty() && s2[i] < s2[q.back()]) q.pop_back();
		q.push_back(i);
		if (i < k) ans1 = max(s2[i], ans1);//当1可能包含进去时，要考虑
		while (!q.empty() && i - q.front() >= k + 1) q.pop_front();
		ans1 = max(ans1, s2[i] - s2[q.front()]);
	}
	//当最大子数组长度大于等于k时
	ll ans2 = 0;
	ans2 = max(ans2, s1[k] + 2 * k * x);//先考虑1到k
	for (int i = k + 1; i <= n; i++) {//再从k+1开始
		ans2 = max(ans2, s1[i] + 2 * k * x);//包含1
		ans2 = max(ans2, s1[i] - minimum[i - k] + 2 * k * x);//不包含1
	}
	ll ans = max(ans1, ans2);
	printf("%lld", ans);
	return 0;
}