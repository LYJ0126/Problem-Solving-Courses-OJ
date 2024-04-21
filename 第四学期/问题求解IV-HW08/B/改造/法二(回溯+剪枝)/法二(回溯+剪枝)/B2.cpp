#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

int num[101];
int group[4];//3����ÿ�����е����ĺ�
bool dfs(int id, int n, int target)
{
	if (id == n + 1) return true;
	for (int i = 1; i <= 3; ++i)
	{
		if (i > 1 && group[i] == group[i - 1]) continue;//��֦�������ǰ�����һ��ĺ���ȣ���ô�Ͳ����ٳ�����
		if (group[i] + num[id] > target) continue;//��֦�������ǰ��ĺͼ��ϵ�ǰ������Ŀ��ֵ����ô�Ͳ����ٳ�����
		group[i] += num[id];
		if (dfs(id + 1, n, target)) return true;
		group[i] -= num[id];//����
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
		sort(num + 1, num + n + 1, greater<int>());//�������С����ô����ѡ��ֵ��ĸ��飬���Ӽ�֦Ч��
		memset(group, 0, sizeof(group));
		if (dfs(1, n, target)) cout << "Yes" << '\n';
		else cout << "No" << '\n';
	}
	return 0;
}