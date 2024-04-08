#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

typedef unsigned long long ull;
ull primes[40000];
bool vis[40000];
int cnt = 0;
void init()//获取质数
{
	//线性筛
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i < 40000; ++i) {
		if (!vis[i]) primes[++cnt] = i;
		for (int j = 1; j <= cnt && i * primes[j] < 40000; ++j) {
			vis[i * primes[j]] = 1;
			if (i % primes[j] == 0) break;
		}
	}
}

ull GCD(ull a, ull b)//求最大公约数
{
	return b == 0 ? a : GCD(b, a % b);
}

ull count(ull m, ull n, ull gcd, ull lcm)//知道m,n,gcd(m,x),lcm(n,x)，求x可能的个数
{
	if (m % gcd != 0 || lcm % n != 0 || lcm % gcd != 0)return 0;//如果m不能被gcd整除，或者lcm不能被n整除，或者lcm不能被gcd整除，那么x一定不存在
	ull ans = 1;
	ull s = lcm / gcd;
	ull mm = m, nn = n;
	for (int i = 1; i <= cnt; ++i) {
		if (s % primes[i] == 0) {
			ull t = 0;
			while (s % primes[i] == 0) s /= primes[i], ++t;//s含有t个primes[i]
			ull a = 0, b = 0;
			while (m % primes[i] == 0) m /= primes[i], ++a;//m含有a个primes[i]
			while (n % primes[i] == 0) n /= primes[i], ++b;//n含有b个primes[i]
			if ((lcm / nn) % primes[i] == 0) continue;
			//此时lcm的质因子primes[i]的次数大于n的质因子primes[i]的次数，说明lcm的prime[i]的次数由x提供,故x的质因数primes[i]的次数只有一种情况,t=xi-a
			if ((mm / gcd) % primes[i] == 0) continue;
			//此时m的质因子primes[i]的次数大于gcd的质因子primes[i]的次数，说明gcd的prime[i]的次数由x提供,故x的质因数primes[i]的次数只有一种情况,t=n-xi
			if (t == b - a) ans *= (t + 1);//x的质因数primes[i]的次数有t+1种情况
			else return 0;//否则无解
		}
		if (s == 1)break;
	}
	if (s != 1) {
		//此时s是一个大于40000的质数,即l此时lcm为一个大于40000的质数，gcd=1
		if (n > 1) {
			if (n != s) return 0;
			//n==s
			if (n != m) ans *= 2;//x有两种情况，1或者s
			//否则x只有一种情况，1
		}
		else {//n==1,x==s.
			if (s == m) return 0;//x==s==m,与gcd=1矛盾
			//否则x只有一种情况，s
		}
	}
	return ans;
}

//快读
inline ull quick_read() {
	ull x = 0;
	char ch = getchar();
	while (ch < '0' || ch>'9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x;
}
//快写
inline void quick_write(ull x) {
	if (x > 9) quick_write(x / 10);
	putchar(x % 10 + '0');
}

int main()
{
	init();
	ull T;
	ull m, n, gcd, lcm;
	T = quick_read();
	while (T--) {
		m = quick_read(), n = quick_read(), gcd = quick_read(), lcm = quick_read();
		quick_write(count(m, n, gcd, lcm));
		putchar('\n');
	}
	return 0;
}