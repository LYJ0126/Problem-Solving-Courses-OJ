#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
const unsigned long long mod = 998244353;

typedef unsigned long long ull;
ull n, m, a, b, c, x, y;
//Ԥ����������еĽ׳˺�����Ԫ
ull fac[10000005], inv[10000005];
void init1()//Ԥ����׳�
{
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * (ull)i % mod;
}
//������
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
//Ԥ����������н׳˵���Ԫ
void init2()
{
	//�׳���Ԫ�ĵ��ƹ�ʽ
	//n!����Ԫ = (n+1)!����Ԫ * (n+1) % mod
	//���������n!����Ԫ
	inv[n] = qpow(fac[n], mod - 2);//n!����Ԫ
	for (int i = n - 1; i >= 0; --i) {
		inv[i] = inv[i + 1] * (ull)(i + 1) % mod;
	}
}
//�������
inline ull C(int nn, int mm)
{
	if (nn < mm) return 0;
	return fac[nn] * inv[mm] % mod * inv[nn - mm] % mod;
}

int main()
{
	cin >> n >> m >> a >> b >> c >> x >> y;
	init1();//Ԥ����׳�
	init2();//Ԥ����׳˵���Ԫ
	//����a��ǰ����Ա��ѡ�����
	//ö����a��������i����ѡΪǰ��,�ٴ�c��ȫ����ѡx-i����Ϊǰ�档�ٴ�ʣ�µ�c-x+i��ȫ�ܺ�b��������ѡy����Ϊ����������
	// ʣ�µ�n-x-y������ѡm-x-y����Ϊ�油�����ռ��㹫ʽΪC(a,i)C(c,x-i)C(c-x+i+b,y)C(n-x-y,m-x-y)
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