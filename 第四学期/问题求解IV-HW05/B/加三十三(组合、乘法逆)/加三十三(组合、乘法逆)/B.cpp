#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
const unsigned long long mod = 998244353;

typedef unsigned long long ull;
ull n, m, a, b, c, x, y;
//预处理求出所有的阶乘和其逆元
ull fac[10000005], inv[10000005];
void init1()//预处理阶乘
{
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * (ull)i % mod;
}
//快速幂
ull qpow(ull aa, ull bb)
{
	ull ans = 1;
	while (bb)
	{
		if (bb & 1) ans = ans * aa % mod;
		aa = aa * aa % mod;
		bb >>= 1;
	}
	return ans;
}
//预处理求出所有阶乘的逆元
void init2()
{
	//阶乘逆元的递推公式
	//n!的逆元 = (n+1)!的逆元 * (n+1) % mod
	//快速幂求出n!的逆元
	inv[n] = qpow(fac[n], mod - 2);//n!的逆元
	for (int i = n - 1; i >= 0; --i) {
		inv[i] = inv[i + 1] * (ull)(i + 1) % mod;
	}
}
//求组合数
inline ull C(int nn, int mm)
{
	if (nn < mm) return 0;
	return fac[nn] * inv[mm] % mod * inv[nn - mm] % mod;
}

int main()
{
	cin >> n >> m >> a >> b >> c >> x >> y;
	init1();//预处理阶乘
	init2();//预处理阶乘的逆元
	//考虑a个前场队员的选择情况
	//枚举这a个人中有i个被选为前锋,再从c个全能中选x-i个人为前锋。再从剩下的c-x+i个全能和b个后卫中选y个人为后卫。最后从
	// 剩下的n-x-y个人中选m-x-y个人为替补。最终计算公式为C(a,i)C(c,x-i)C(c-x+i+b,y)C(n-x-y,m-x-y)
	ull ans = 0;
	for (int i = 0; i <= a; i++)
	{
		if (c < x - i || c - x + i + b < y) continue;
		ull tmp = C(a, i) * C(c, x - i) % mod;
		tmp = tmp * C(c - x + i + b, y) % mod;
		tmp = tmp * C(n - x - y, m - x - y) % mod;
		ans = (ans + tmp) % mod;
	}
	cout << ans % mod;
	return 0;
}