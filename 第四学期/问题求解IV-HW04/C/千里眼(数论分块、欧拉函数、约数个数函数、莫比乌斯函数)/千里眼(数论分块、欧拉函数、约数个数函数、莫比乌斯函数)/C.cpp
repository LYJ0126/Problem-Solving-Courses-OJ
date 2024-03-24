#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

typedef long long ll;
//�����1-n��������ŷ������ֵ��Լ��������Ī����˹����ֵ
const int maxn = 1e7 + 10;
//phi,d,mu,prime,num�ֱ��ʾŷ������ֵ��Լ��������Ī����˹����ֵ����������С������ָ��
ll phi[maxn], d[maxn], mu[maxn], prime[maxn], num[maxn];
ll f[maxn];
bool vis[maxn];
void init(ll n) {
	phi[1] = d[1] = mu[1] = num[1] = 1;
	memset(vis, false, sizeof(vis));
	ll cnt = 0;
	for (ll i = 2; i <= n; ++i) {
		if (!vis[i]) {//i������
			prime[++cnt] = i;
			phi[i] = i - 1;
			d[i] = 2;
			mu[i] = -1;
			num[i] = 1;
		}
		for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
			vis[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];//��С������ָ������1,phi[i*prime[j]] = phi[i]*prime[j]
				num[i * prime[j]] = num[i] + 1;
				d[i * prime[j]] = d[i] / (num[i] + 1) * (num[i] + 2);//��С������ָ������1,d[i*prime[j]] = d[i]/num[i]*num[i+1]
				mu[i * prime[j]] = 0;//���ظ�������,Ī����˹����ֵΪ0
				break;
			}
			else {
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);//��С������ָ������1,phi[i*prime[j]] = phi[i]*phi(prime[j])
				num[i * prime[j]] = 1;//��С������ָ������1
				d[i * prime[j]] = d[i] * 2;//��ʱd[prim[j]]=2
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
}

int main() {
	int T;
	ll p, n;
	//cin >> T >> p;
	scanf("%d%lld", &T, &p);
	init(10000000);
	//�ɶԳ��ԣ�ֻ����x>y�������������x=y=1�����
	//������ʽΪ��_{i=1}^{n}f(i)floor(n/i)�����������۷ֿ���ټ���
	//�����(d[x]+mu[x])*phi[x]*2��ǰ׺��f[x]
	for (int x = 1; x <= 10000000; ++x) {
		f[x] = (f[x - 1] + (d[x] + mu[x]) * phi[x] * 2) % p;
	}
	while (T--) {
		//cin >> n;
		scanf("%lld", &n);
		ll ans = 0;
		//�ֿ����
		for (ll l = 1, r; l <= n; l = r + 1) {
			r = n / (n / l);
			ans = (ans + (f[r] - f[l - 1] + p) * (n / l)) % p;
		}
		ans = (ans + n * 2) % p;//����x=y=1�����
		cout << ans << '\n';
	}
	return 0;
}