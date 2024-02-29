#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<deque>
using namespace std;

//�����������鳤��С��kʱ����������һ������Ϊk�Ļ������ڣ���ǰ׺�������в�ѯ��ͬ�յ�ĳ��Ȳ�����k����������鲢������ֵ��
// ͬʱ�����i<k����ô��Ҫ���ǰ�����һ���������
//Ԥ����ԭ����ÿ������ȥx����ǰ׺��,ԭ����ÿ��������x����ǰ׺��
//С��kʱ��ÿ��s2[n]-s2[i]
//���ڵ���kʱ��Ԥ��������ô�1��j֮��ǰ׺����С��minimum[i]����ô��ʱ��Ϊs1[n]-minimum[i]+2kx��i==n-k��
//ͬʱ��Ҫ���ǰ���1�����
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
		s1[i] = s1[i - 1] + a[i] - x;//ǰ׺��1
		s2[i] = s2[i - 1] + a[i] + x;//ǰ׺��2
		if (i == 1) minimum[i] = s1[i];
		else {
			if (s1[i] < minimum[i - 1]) minimum[i] = s1[i];
			else minimum[i] = minimum[i - 1];
		}
	}
	ll ans1 = 0;
	//����������鳤��С��kʱ�����õ�������������ֵ
	for (int i = 1; i <= n; i++)
	{
		while (!q.empty() && s2[i] < s2[q.back()]) q.pop_back();
		q.push_back(i);
		if (i < k) ans1 = max(s2[i], ans1);//��1���ܰ�����ȥʱ��Ҫ����
		while (!q.empty() && i - q.front() >= k + 1) q.pop_front();
		ans1 = max(ans1, s2[i] - s2[q.front()]);
	}
	//����������鳤�ȴ��ڵ���kʱ
	ll ans2 = 0;
	ans2 = max(ans2, s1[k] + 2 * k * x);//�ȿ���1��k
	for (int i = k + 1; i <= n; i++) {//�ٴ�k+1��ʼ
		ans2 = max(ans2, s1[i] + 2 * k * x);//����1
		ans2 = max(ans2, s1[i] - minimum[i - k] + 2 * k * x);//������1
	}
	ll ans = max(ans1, ans2);
	printf("%lld", ans);
	return 0;
}