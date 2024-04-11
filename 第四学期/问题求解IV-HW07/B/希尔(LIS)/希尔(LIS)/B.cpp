#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

int n, k, a[401];
int dp[401];
int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	//修改的区间肯定是都能被使用的(全部赋为一样的值就可以),那么修改区间长度尽量长，即为k
	//枚举区间左端点，剩余的序列中求最长不下降子序列
	int ans = 0, left;//记录最长不下降子序列的长度
	int ansleft = 0;//记录最终所选区间的左端点
	vector<int>anspos;//记录最长不下降子序列的位置
	for (left = 1; left <= n - k + 1; ++left) {//枚举区间左端点
		//求出剩余的序列中最长不下降子序列,并记录最值以及位置
		//dp初始化
		for (int i = 1; i <= n; ++i) if (i < left || i >= left + k) dp[i] = 1;
		vector<int>temppos(n + 1, 0);//记录以i结尾的最长不下降子序列的前一个位置
		//dp
		for (int i = 1; i <= n; ++i) {
			if (i >= left && i <= left + k - 1) continue;
			for (int j = 1; j < i; ++j) {
				if (j >= left && j <= left + k - 1) continue;
				if (a[j] <= a[i]) {
					if (dp[i] < dp[j] + 1) {
						temppos[i] = j;
						dp[i] = dp[j] + 1;
					}
				}
			}
		}
		//找到最长不下降子序列最后一个位置
		int lastpos = 1;
		for (int i = 1; i <= n; ++i) {
			if (i >= left && i <= left + k - 1) continue;
			if (dp[i] > dp[lastpos]) lastpos = i;
		}
		if (dp[lastpos] > ans) {//更新答案
			ans = dp[lastpos];
			ansleft = left;
			//记录当前最长不下降子序列,注意最后要逆序输出
			anspos.clear();
			int id = lastpos;
			while (id) {
				anspos.push_back(id);
				id = temppos[id];
			}
		}
	}
	cout << ans + k << endl;
	cout << ansleft << " " << ansleft + k - 1 << endl;
	reverse(anspos.begin(), anspos.end());
	int len = anspos.size();
	if (len == 0) {
		for (int i = ansleft; i < ansleft + k; ++i) cout << i << " ";
		return 0;
	}
	if (anspos[len - 1] < ansleft) {
		for (int i = 0; i < len; ++i) cout << anspos[i] << " ";
		for (int i = ansleft; i < anspos[len - 1]; ++i) cout << i << " ";
	}
	else if (anspos[0] > ansleft + k - 1) {
		for (int i = ansleft; i < ansleft + k; ++i) cout << i << " ";
		for (int i = 0; i < len; ++i) cout << anspos[i] << " ";
	}
	else {
		int i = 0;
		while (anspos[i] < ansleft) cout << anspos[i++] << " ";
		for (int j = ansleft; j < ansleft + k; ++j) cout << j << " ";
		while (i < len) cout << anspos[i++] << " ";
	}
	return 0;
}