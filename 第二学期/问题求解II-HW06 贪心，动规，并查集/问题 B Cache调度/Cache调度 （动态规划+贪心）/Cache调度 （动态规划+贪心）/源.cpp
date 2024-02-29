#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

typedef long long ll;
ll n, k, a[5009], cold[5009], hot[5009];
ll sum[5009];//sum[l,r]��ʾl+1��r������ͬһ��Cache��ִ������ʱ�䣬����ʵ�ֵ���ǰ׺������
ll dp[5009][2];//dp[i][0]��ʾ��i�������ǰ��һ������ʹ�õ�Cache��һ����dp[i][1]��ʾһ��
int last[5009];//last[i]�����i������֮ǰ�����һ����iͬ���͵ĳ����λ��
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
		//�ȿ��ǵ�i������û���ܵ�Cache hit������������ܵ��ˣ��Ḳ���������
		dp[i][0] = dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + cold[a[i]];
		//������ܵ���Cache hit
		if (last[i] != 0) {
			if (last[i] == i - 1) {
				dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + hot[a[i]];//����һ������ͬһ��Cache
			}
			else {
				dp[i][0] = min(dp[i][0], dp[last[i] + 1][0] + sum[i - 1] - sum[last[i] + 1] + hot[a[i]]);//����һ������ͬCache
				//ע��last[i]+1�����0ת�ƹ�������ΪҪ��last[i]+1��i-1��������last[i]��ͬ��Cache������i��������last[i]
			}
		}
	}
	ll ans = min(dp[n][0], dp[n][1]);
	printf("%lld", ans);
	return 0;
}