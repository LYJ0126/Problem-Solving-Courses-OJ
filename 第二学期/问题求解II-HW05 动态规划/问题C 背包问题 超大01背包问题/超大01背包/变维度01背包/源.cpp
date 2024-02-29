#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cmath>
#include<cstring>
using namespace std;

//此题中背包容积太大，但是物品价值和却不超过1e6，我们可以将dp的变量改为选择的物品范围和总价值。
//即在前i个物品中选择使总价值为j(可能无解，无解的情况赋值inf)，物品体积和最小。这就是最优子结构。
//最后从末端线性查找答案
const int inf = 1e9 + 4;
int n, V, v[550], w[550], dp[1000005];//volume worth  为了防止MLE，采用一维dp数组
int main()
{
	scanf("%d%d", &n, &V);
	for (int i = 1; i <= n; i++) scanf("%d%d", &v[i], &w[i]);
	dp[0] = 0;
	for (int i = 1; i <= 1e6; i++) dp[i] = inf;
	for (int i = 1; i <= n; i++) {
		for (int j = 1e6; j >= w[i]; j--) {
			if (dp[j] == inf && dp[j - w[i]] == inf) dp[j] = inf;//发现此处无解，赋值为inf
			else {
				dp[j] = min(dp[j - w[i]] + v[i], dp[j]);//最优子结构
			}
		}
	}
	int ans = 1e6;
	while (dp[ans] > V) ans--;//逆序寻找答案
	printf("%d", ans);
	return 0;
}