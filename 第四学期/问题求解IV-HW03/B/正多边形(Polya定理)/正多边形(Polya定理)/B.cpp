#include<iostream>
#include<cmath>
using namespace std;


//此题参考链接https://zhuanlan.zhihu.com/p/265991683
//题目条件给出n为偶数。最后计算公式为(1/2n)(\sigma_{k=1}^{n}m^(\gcd(k,n))+(n/2)m^{n/2}+(n/2)m^{(n/2)+1})
typedef long long ll;
const ll mod = 998244353;
ll fastpower(ll base, ll power)
{
	ll result = 1;
	while (power)
	{
		if (power & 1) result = result * base % mod;
		base = base * base % mod;
		power >>= 1;
	}
	return result;
}
ll gcd(ll a, ll b)
{
	return b ? gcd(b, a % b) : a;
}
int main()
{
	int n, m;
	cin >> n >> m;
	ll ans = 0;
	for (int i = 1; i <= n; ++i) ans = (ans + fastpower(m, gcd(i, n))) % mod;
	ans = (ans + (n / 2) * fastpower(m, n / 2) % mod) % mod;
	ans = (ans + (n / 2) * fastpower(m, (n / 2) + 1) % mod) % mod;
	ans = ans * fastpower(2 * n, mod - 2) % mod;//因为mod为质数,2n的逆元为2n的mod-2次方
	cout << ans;
	return 0;
}