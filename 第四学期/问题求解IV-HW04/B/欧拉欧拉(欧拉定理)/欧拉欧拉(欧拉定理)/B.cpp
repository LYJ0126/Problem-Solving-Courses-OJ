#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include<cstring>

using namespace std;
typedef unsigned long long int ull;
ull n, a;
string k;
//����ָ��k�ǳ�������ŷ��������k%��(n)��Ȼ�����ÿ�������⡣
//���(n)
//��(x)=x*(1-1/p1)*(1-1/p2)*...*(1-1/pn)
ull phi(ull x)
{
	ull ans = x;
	for (ull i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			ans = ans / i * (i - 1);
			while (x % i == 0) x /= i;//��x�е�������iȫ������
		}
	}
	if (x > 1) ans = ans / x * (x - 1);//x��������������Ϊx
	return ans;
}
//�߾�����ģ
ull MOD(string K, ull b)
{
	ull ans = 0;
	int i = 0;
	while (K[i] == '0') ++i;//ȥ��ǰ��0
	int len = K.length();
	for (; i < len; ++i) ans = ((ans * 10) % b + (K[i] - '0')) % b;
	return ans;
}
//������
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