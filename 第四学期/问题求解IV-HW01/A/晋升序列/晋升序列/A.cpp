#include<iostream>
#include<cmath>
using namespace std;


//对原来的表达式，假设头尾添加一左一右括号。下面，在中间n-1个运算符处，分别插入左括号和右括号，就可以构造出一种运算顺序。
//插入的第一对括号左右两边的表达式先进行运算，后面插入的第二对括号的表达式第二步运算，最终插入n-1对括号以构成整个的一种运算顺序。
//一种运算顺序对应一种插入n-1对括号的排序方式，故有(n-1)!种插入括号的方式，即有(n-1)!种运算顺序。

//对于所有状态数，每插入一对括号就会生成一些列新的状态。
//无括号插入，有1种状态，即初始状态。1对括号插入，有n-1种状态，2对括号插入，有C(n-1,2)种状态，3对括号插入，
//有C(n-1,3)种状态，……，n-1对括号插入，有C(n-1,n-1)种状态。
//所以，总的状态数为1+C(n-1,1)+C(n-1,2)+……+C(n-1,n-1)=2^(n-1)。

//注意，数据范围到了10^9数量级，而取模的数是10^7数量级，故当n>mod时，答案为0，这样可以减少计算量。
//另外，对于2^(n-1)的计算，可以用快速幂的方法进行计算。
typedef long long ll;
ll n, mod = 10000079;
ll fastpower(ll base, ll power)
{
	ll ans = 1;
	while (power)
	{
		if (power & 1)
			ans = ans * base % mod;
		base = base * base % mod;
		power >>= 1;
	}
	return ans;
}
int main()
{
	cin >> n;
	ll ans1 = 1;
	if (n > mod) ans1 = 0;
	else {
		for (int i = 1; i < n; ++i) {
			ans1 = ans1 * i % mod;
		}
	}
	ll ans2 = fastpower(2, n - 1);
	cout << ans1 << endl;
	cout << ans2 << endl;
	return 0;
}