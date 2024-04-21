#include<iostream>
#include<cmath>
using namespace std;

typedef long long ll;
ll n, W, Q;//�̵��еĻ���������СL�ı�����С���Լ�СL���õļ�ֵ����
//���������ܴ��ô�ͳ��01���������ᳬʱ�ҳ��ڴ�
//ע�⵽��Ʒ��ֵ������ΪQ,Q<=100000,���Կ��Ǳ�ά
//dp[i][j]��ʾǰi����Ʒ�У���ֵΪj������£���С���������������������������dp[i][j]=INF
//dp[i][j]=min(dp[i-1][j],dp[i-1][j-v[i]]+w[i])
//Ϊ�˽�ʡ�ռ䣬����һά����
ll dp[100005];
ll w[2001], q[2001];//w[i]��ʾ��i����Ʒ�������q[i]��ʾ��i����Ʒ�ļ�ֵ
const ll INF = 0x3f3f3f3f3f3f3f3f;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> W >> Q;
	//��ʼ��
	dp[0] = 0;
	for (int i = 1; i <= Q; ++i) dp[i] = INF;
	ll maxvalue = 0;//��¼���ܵ�����ֵ
	ll minvolume = INF;//��¼��ֵΪQʱ��С���
	for (int i = 1; i <= n; ++i) cin >> w[i] >> q[i];
	for (int i = 1; i <= n; ++i)
	{
		for (int j = Q; j >= q[i]; --j)
		{
			if (dp[j] == INF && dp[j - q[i]] == INF) dp[j] = INF;//�޽�
			else {//�н�
				dp[j] = min(dp[j], dp[j - q[i]] + w[i]);
				if (dp[j] <= W) {//���ܳ�����������
					maxvalue = max(maxvalue, (ll)j);
					if (j == Q) minvolume = min(minvolume, dp[j]);
				}
			}
		}
	}
	if (maxvalue < Q || minvolume == INF) {
		cout << "No" << endl;
		cout << maxvalue << endl;
	}
	else {
		cout << "Yes" << endl;
		cout << minvolume << endl;
	}
	return 0;
}