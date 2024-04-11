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
	//�޸ĵ�����϶��Ƕ��ܱ�ʹ�õ�(ȫ����Ϊһ����ֵ�Ϳ���),��ô�޸����䳤�Ⱦ���������Ϊk
	//ö��������˵㣬ʣ���������������½�������
	int ans = 0, left;//��¼����½������еĳ���
	int ansleft = 0;//��¼������ѡ�������˵�
	vector<int>anspos;//��¼����½������е�λ��
	for (left = 1; left <= n - k + 1; ++left) {//ö��������˵�
		//���ʣ�������������½�������,����¼��ֵ�Լ�λ��
		//dp��ʼ��
		for (int i = 1; i <= n; ++i) if (i < left || i >= left + k) dp[i] = 1;
		vector<int>temppos(n + 1, 0);//��¼��i��β������½������е�ǰһ��λ��
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
		//�ҵ�����½����������һ��λ��
		int lastpos = 1;
		for (int i = 1; i <= n; ++i) {
			if (i >= left && i <= left + k - 1) continue;
			if (dp[i] > dp[lastpos]) lastpos = i;
		}
		if (dp[lastpos] > ans) {//���´�
			ans = dp[lastpos];
			ansleft = left;
			//��¼��ǰ����½�������,ע�����Ҫ�������
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