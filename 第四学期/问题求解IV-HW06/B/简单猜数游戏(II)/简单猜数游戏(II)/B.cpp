#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

typedef unsigned long long ull;
ull primes[40000];
bool vis[40000];
int cnt = 0;
void init()//��ȡ����
{
	//����ɸ
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i < 40000; ++i) {
		if (!vis[i]) primes[++cnt] = i;
		for (int j = 1; j <= cnt && i * primes[j] < 40000; ++j) {
			vis[i * primes[j]] = 1;
			if (i % primes[j] == 0) break;
		}
	}
}

ull GCD(ull a, ull b)//�����Լ��
{
	return b == 0 ? a : GCD(b, a % b);
}

ull count(ull m, ull n, ull gcd, ull lcm)//֪��m,n,gcd(m,x),lcm(n,x)����x���ܵĸ���
{
	if (m % gcd != 0 || lcm % n != 0 || lcm % gcd != 0)return 0;//���m���ܱ�gcd����������lcm���ܱ�n����������lcm���ܱ�gcd��������ôxһ��������
	ull ans = 1;
	ull s = lcm / gcd;
	ull mm = m, nn = n;
	for (int i = 1; i <= cnt; ++i) {
		if (s % primes[i] == 0) {
			ull t = 0;
			while (s % primes[i] == 0) s /= primes[i], ++t;//s����t��primes[i]
			ull a = 0, b = 0;
			while (m % primes[i] == 0) m /= primes[i], ++a;//m����a��primes[i]
			while (n % primes[i] == 0) n /= primes[i], ++b;//n����b��primes[i]
			if ((lcm / nn) % primes[i] == 0) continue;
			//��ʱlcm��������primes[i]�Ĵ�������n��������primes[i]�Ĵ�����˵��lcm��prime[i]�Ĵ�����x�ṩ,��x��������primes[i]�Ĵ���ֻ��һ�����,t=xi-a
			if ((mm / gcd) % primes[i] == 0) continue;
			//��ʱm��������primes[i]�Ĵ�������gcd��������primes[i]�Ĵ�����˵��gcd��prime[i]�Ĵ�����x�ṩ,��x��������primes[i]�Ĵ���ֻ��һ�����,t=n-xi
			if (t == b - a) ans *= (t + 1);//x��������primes[i]�Ĵ�����t+1�����
			else return 0;//�����޽�
		}
		if (s == 1)break;
	}
	if (s != 1) {
		//��ʱs��һ������40000������,��l��ʱlcmΪһ������40000��������gcd=1
		if (n > 1) {
			if (n != s) return 0;
			//n==s
			if (n != m) ans *= 2;//x�����������1����s
			//����xֻ��һ�������1
		}
		else {//n==1,x==s.
			if (s == m) return 0;//x==s==m,��gcd=1ì��
			//����xֻ��һ�������s
		}
	}
	return ans;
}

//���
inline ull quick_read() {
	ull x = 0;
	char ch = getchar();
	while (ch < '0' || ch>'9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x;
}
//��д
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