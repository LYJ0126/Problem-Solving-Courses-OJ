#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long ll;
ll n;
vector<ll>a, b;
vector<vector<ll>>dp;
ll INF = 0x3f3f3f3f3f3f3f3f;
int main()
{
	ll sum = 0;
	cin >> n;
	a.resize(n + 1);
	b.resize(n - 1);
	dp.resize(4, vector<ll>(n + 1));
	ll positive = 0;//记录正数的个数
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (a[i] > 0) positive++;
		sum += a[i];
		if (i == 1 || i == n)continue;
		b[i - 1] = -a[i];
	}
	//特判正整数个数小于等于2的情况
	if (positive <= 2) {
		sort(a.begin() + 1, a.end());
		cout << a[n] + a[n - 1] + a[n - 2] << endl;
		return 0;
	}
	//对于环形的求解，可以转换为两个线性求解的最大值
	//头尾不一起选，则为求解线性数组的3个最大子段和
	//头尾一起选，则先求解剩下数组中的3个最小子段和，然后用总和减去最小子段和
	//考虑dp[i][j],表示前j项构成i子段的最大和,且第j项必须选
	//1.把第j项加入到第j-1项的子段中 dp[i][j]=max(dp[i][j],dp[i][j-1]+a[j])
	//2.把第j项作为一个新的子段 dp[i][j]=max(dp[i][j],dp[i-1][k]+a[j]) i<=k<j
	//先计算头尾不一起选的情况
	vector<ll>temp(n + 1);//temp[k]表示dp[i-1][k]的最大值
	for (int i = 1; i <= 3; ++i) {
		vector<ll>temp2(n + 1);
		ll tempmax = -INF;
		for (int j = i; j <= n; ++j) {
			ll t1 = -INF;
			if (j > i) t1 = dp[i][j - 1];//j==i时，dp[i][j-1]不存在(不肯能将少于i个数分成i段),即t1=-INF
			ll t2 = 0;
			if (j - 1 >= 1) t2 = temp[j - 1];
			dp[i][j] = max(t1, t2) + a[j];
			if (dp[i][j] > tempmax) tempmax = dp[i][j];
			temp2[j] = tempmax;
		}
		temp = temp2;
	}
	ll ans = -INF;
	for (int j = 1; j <= n; ++j) ans = max(ans, dp[3][j]);
	//计算头尾一起选的情况
	//特判原来数个数不足5个的情况
	if (n < 5) {
		if (n == 3) ans = sum;
		else {
			ans = -INF;
			for (int i = 1; i <= n; ++i) {//4选三
				ans = max(ans, sum - a[i]);
			}
			ans = max(ans, sum);//全选
		}
	}
	else {//计算b数组3个子段的最大和,b数组已经除去a的头尾
		for (int i = 0; i <= n; ++i) temp[i] = 0;
		for (int i = 1; i <= 3; ++i) {
			vector<ll>temp2(n - 1);
			ll tempmax = -INF;
			for (int j = i; j <= n - 2; ++j) {
				ll t1 = -INF;
				if (j > i) t1 = dp[i][j - 1];//j==i时，dp[i][j-1]不存在(不肯能将少于i个数分成i段),即t1=-INF
				ll t2 = 0;
				if (j - 1 >= 1) t2 = temp[j - 1];
				dp[i][j] = max(t1, t2) + b[j];
				if (dp[i][j] > tempmax) tempmax = dp[i][j];
				temp2[j] = tempmax;
			}
			temp = temp2;
		}
		ll tempans = -INF;
		for (int j = 1; j <= n - 2; ++j) tempans = max(tempans, dp[3][j]);
		ans = max(ans, sum + tempans);
	}
	cout << ans << endl;
	return 0;
}