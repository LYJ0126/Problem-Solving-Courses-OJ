#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include<cstring>

using namespace std;
typedef unsigned long long int ull;
ull n, a;
string k;
//由于指数k非常大，利用欧拉定理，先k%φ(n)。然后再用快速幂求解。
//求φ(n)
//φ(x)=x*(1-1/p1)*(1-1/p2)*...*(1-1/pn)
ull phi(ull x)
{
	ull ans = x;
	for (ull i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			ans = ans / i * (i - 1);
			while (x % i == 0) x /= i;//把x中的质因子i全部除掉
		}
	}
	if (x > 1) ans = ans / x * (x - 1);//x是质数，质因子为x
	return ans;
}
//高精度求模
ull MOD(string K, ull b)
{
	ull ans = 0;
	int i = 0;
	while (K[i] == '0') ++i;//去掉前导0
	int len = K.length();
	for (; i < len; ++i) ans = ((ans * 10) % b + (K[i] - '0')) % b;
	return ans;
}
//快速幂
ull quick_pow(ull base, ull power, ull mod)
{
	ull ans = 1;
	while (power) {
		if (power & 1) ans = ans * base % mod;
		base = base * base % mod;
		power >>= 1;
	}
	return ans % mod;
}
int main()
{
	cin >> a >> k >> n;
	ull phi_n = phi(n);
	ull k_mod_phi_n = MOD(k, phi_n);
	cout << quick_pow(a, k_mod_phi_n, n);
	return 0;
}