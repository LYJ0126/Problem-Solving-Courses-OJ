#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

int num[101];
int group[4];//3组中每个组中的数的和
bool dfs(int id, int n, int target)
{
	if (id == n + 1) return true;
	for (int i = 1; i <= 3; ++i)
	{
		if (i > 1 && group[i] == group[i - 1]) continue;//剪枝，如果当前组和上一组的和相等，那么就不用再尝试了
		if (group[i] + num[id] > target) continue;//剪枝，如果当前组的和加上当前数大于目标值，那么就不用再尝试了
		group[i] += num[id];
		if (dfs(id + 1, n, target)) return true;
		group[i] -= num[id];//回溯
	}
	return false;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T, n;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> n;
		int sum = 0;
		for (int i = 1; i <= n; ++i)
		{
			cin >> num[i];
			sum += num[i];
		}
		if (sum % 3 != 0) {
			cout << "No" << '\n';
			continue;
		}
		int target = sum / 3;
		sort(num + 1, num + n + 1, greater<int>());//降序排列。先让大的数选择分到哪个组，增加剪枝效率
		memset(group, 0, sizeof(group));
		if (dfs(1, n, target)) cout << "Yes" << '\n';
		else cout << "No" << '\n';
	}
	return 0;
}