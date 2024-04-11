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
	ll positive = 0;//��¼�����ĸ���
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (a[i] > 0) positive++;
		sum += a[i];
		if (i == 1 || i == n)continue;
		b[i - 1] = -a[i];
	}
	//��������������С�ڵ���2�����
	if (positive <= 2) {
		sort(a.begin() + 1, a.end());
		cout << a[n] + a[n - 1] + a[n - 2] << endl;
		return 0;
	}
	//���ڻ��ε���⣬����ת��Ϊ���������������ֵ
	//ͷβ��һ��ѡ����Ϊ������������3������Ӷκ�
	//ͷβһ��ѡ���������ʣ�������е�3����С�Ӷκͣ�Ȼ�����ܺͼ�ȥ��С�Ӷκ�
	//����dp[i][j],��ʾǰj���i�Ӷε�����,�ҵ�j�����ѡ
	//1.�ѵ�j����뵽��j-1����Ӷ��� dp[i][j]=max(dp[i][j],dp[i][j-1]+a[j])
	//2.�ѵ�j����Ϊһ���µ��Ӷ� dp[i][j]=max(dp[i][j],dp[i-1][k]+a[j]) i<=k<j
	//�ȼ���ͷβ��һ��ѡ�����
	vector<ll>temp(n + 1);//temp[k]��ʾdp[i-1][k]�����ֵ
	for (int i = 1; i <= 3; ++i) {
		vector<ll>temp2(n + 1);
		ll tempmax = -INF;
		for (int j = i; j <= n; ++j) {
			ll t1 = -INF;
			if (j > i) t1 = dp[i][j - 1];//j==iʱ��dp[i][j-1]������(�����ܽ�����i�����ֳ�i��),��t1=-INF
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
	//����ͷβһ��ѡ�����
	//����ԭ������������5�������
	if (n < 5) {
		if (n == 3) ans = sum;
		else {
			ans = -INF;
			for (int i = 1; i <= n; ++i) {//4ѡ��
				ans = max(ans, sum - a[i]);
			}
			ans = max(ans, sum);//ȫѡ
		}
	}
	else {//����b����3���Ӷε�����,b�����Ѿ���ȥa��ͷβ
		for (int i = 0; i <= n; ++i) temp[i] = 0;
		for (int i = 1; i <= 3; ++i) {
			vector<ll>temp2(n - 1);
			ll tempmax = -INF;
			for (int j = i; j <= n - 2; ++j) {
				ll t1 = -INF;
				if (j > i) t1 = dp[i][j - 1];//j==iʱ��dp[i][j-1]������(�����ܽ�����i�����ֳ�i��),��t1=-INF
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