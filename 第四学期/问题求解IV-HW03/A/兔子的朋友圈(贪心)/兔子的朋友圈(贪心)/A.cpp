#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long ll;
const int mod = 998244353;

ll gcd(ll a, ll b)
{
	return b ? gcd(b, a % b) : a;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	ll n, k;
	cin >> T;
	while (T--) {
		cin >> n >> k;
		vector<ll>num(n);
		for (int i = 0; i < n; ++i) cin >> num[i];
		sort(num.begin(), num.end(), greater<ll>());
		ll len = n / gcd(n, k);
		ll ans = 0;
		int head = 0;
		vector<ll>temp(n);//�����µ�˳��
		while (head < n) {
			int start = head + len / 2;//�ӵ�ǰ���м俪ʼ�����ҽ����������
			bool parity = true;
			for (int i = 0; i < len; ++i) {
				if (parity) {
					start += i;
					temp[start] = num[head + i];//���뵱ǰ�ڵ�i+1�����
				}
				else {
					start -= i;
					temp[start] = num[head + i];//���뵱ǰ�ڵ�i+1�����
				}
				parity = !parity;
			}
			head += len;
		}
		for (int i = 0; i < n; ++i) {
			if (i % len == len - 1) ans = (ans + temp[i] * temp[i + 1 - len]) % mod;
			else ans = (ans + temp[i] * temp[i + 1]) % mod;
		}
		cout << ans << '\n';
	}
	return 0;
}