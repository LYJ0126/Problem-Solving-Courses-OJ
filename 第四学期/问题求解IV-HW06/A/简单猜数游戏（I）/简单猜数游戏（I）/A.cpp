#include<iostream>
#include<cmath>
using namespace std;

typedef unsigned long long ull;
ull gcd(ull a, ull b)
{
	if (b == 0) return a;
	return gcd(b, a % b);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	ull n, k;
	cin >> n >> k;
	ull res = 1, a;
	//若lcm(a1,a2,a3,...,an) mod k = 0,则Bob可以猜出x的值，否则无法猜出
	//lcm(a1,a2,a3,...,an)可能很大，所以求lcm(a1,a2,a3,...,an) mod k
	//lcm(a,b)= a*b/gcd(a,b),那么lcm(a,b)%k = (a*b/gcd(a,b))%k = (a%k*(b/gcd(a,b))%k)%k
	for (int i = 0; i < n; ++i) {
		cin >> a;
		res = ((res % k) * ((a / gcd(res, a)) % k)) % k;
	}
	if (res == 0) cout << "Bob";
	else cout << "Alice";
	return 0;
}