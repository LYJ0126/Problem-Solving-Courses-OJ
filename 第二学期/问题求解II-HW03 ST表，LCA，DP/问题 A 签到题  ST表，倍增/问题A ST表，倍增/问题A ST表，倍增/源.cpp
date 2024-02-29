#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<stdlib.h>
using namespace std;
typedef long long ll;
const int MOD = 998244353;

ll n, a0, k, b, mod;
ll a[1000005];
//下面是助教打的unsigned int128
typedef unsigned long long ull;
struct UINT128;
UINT128 mul(ull a, ull b);

struct UINT128 {
	static int table[40][128];
	static bool _init;
	ull hi, lo;
	UINT128() :hi(0), lo(0) {}
	UINT128(ull lo) :hi(0), lo(lo) {}
	UINT128(ull hi, ull lo) :hi(hi), lo(lo) {}
	UINT128(UINT128&& rhs)noexcept {
		this->hi = rhs.hi;
		this->lo = rhs.lo;
	}
	UINT128(const UINT128& rhs) {
		this->hi = rhs.hi;
		this->lo = rhs.lo;
	}
	static void init() {
		memset(UINT128::table, 0, sizeof(UINT128::table));
		UINT128::table[0][0] = 1;
		for (int i = 1; i < 128; i++) {
			for (int j = 0; j < 40; j++) {
				table[j][i] += table[j][i - 1] * 2;
				if (table[j][i] >= 10) {
					table[j][i] -= 10;
					table[j + 1][i] += 1;
				}
			}
		}
		int i;
		for (i = 39; UINT128::table[i][10] == 0; i--);
		UINT128::_init = 1;
	}
	UINT128 operator=(UINT128&& rhs)noexcept {
		this->hi = rhs.hi;
		this->lo = rhs.lo;
		return *this;
	}
	UINT128 operator=(const UINT128& rhs) {
		this->hi = rhs.hi;
		this->lo = rhs.lo;
		return *this;
	}
	UINT128 operator-()  const {
		UINT128 ret;
		ret.hi = ~hi;
		if (lo == 0) {
			ret.hi++;
			ret.lo = 0;
		}
		else {
			ret.lo = ~lo;
			ret.lo++;
		}
		return ret;
	}
	UINT128 operator+ (const UINT128& rhs)const {
		UINT128 ret;
		ret.hi = hi + rhs.hi;
		ret.lo = lo + rhs.lo;
		if (ret.lo < lo) {
			ret.hi++;
		}
		return ret;
	}
	UINT128 operator+ (UINT128&& rhs)const {
		UINT128 ret;
		ret.hi = hi + rhs.hi;
		ret.lo = lo + rhs.lo;
		if (ret.lo < lo) {
			ret.hi++;
		}
		return ret;
	}
	UINT128 operator- (const UINT128& rhs)const {
		return *this + (-rhs);
	}
	UINT128 operator- (UINT128&& rhs)const {
		return *this + (-rhs);
	}
	UINT128 operator<<(const int& rhs) const {
		UINT128 ret{ 0,0 };
		ret.hi = rhs >= 64 ? 0 : (hi << rhs);
		ull carry = 0;
		ret.lo = rhs >= 64 ? 0 : (lo << rhs);
		carry = (rhs >= 64) ? (lo << (rhs - 64)) : (lo >> (64 - rhs));
		ret.hi += carry;
		return ret;
	}
	UINT128 operator<<(int&& rhs) const {
		UINT128 ret{ 0,0 };
		ret.hi = rhs >= 64 ? 0 : (hi << rhs);
		ull carry = 0;
		ret.lo = rhs >= 64 ? 0 : (lo << rhs);
		carry = (rhs >= 64) ? (lo << (rhs - 64)) : (lo >> (64 - rhs));
		ret.hi += carry;
		return ret;
	}
	UINT128 operator>>(const int& rhs)const {
		UINT128 ret{ 0,0 };
		ret.lo = (rhs >= 64) ? 0 : (lo >> rhs);
		ull carry = 0;
		ret.hi = (rhs >= 64) ? 0 : (hi >> rhs);
		carry = (rhs >= 64) ? (hi >> (rhs - 64)) : (hi << (64 - rhs));
		ret.lo += carry;
		return ret;
	}
	UINT128 operator>>(int&& rhs)const {
		UINT128 ret{ 0,0 };
		ret.lo = (rhs >= 64) ? 0 : (lo >> rhs);
		ull carry = 0;
		ret.hi = (rhs >= 64) ? 0 : (hi >> rhs);
		carry = (rhs >= 64) ? (hi >> (rhs - 64)) : (hi << (64 - rhs));
		ret.lo += carry;
		return ret;
	}
	UINT128 operator*(const UINT128& rhs)const {
		UINT128 L = mul(lo, rhs.lo);
		ull H = lo * rhs.hi + hi * rhs.lo;
		return L + UINT128(H, 0);
	}
	UINT128 operator*(UINT128&& rhs)const {
		UINT128 L = mul(lo, rhs.lo);
		ull H = lo * rhs.hi + hi * rhs.lo;
		return L + UINT128(H, 0);
	}

	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator+ (const T& rhs)const {
		UINT128 ret;
		ret.lo = lo + rhs;
		if (ret.lo < lo) {
			ret.hi++;
		}
		return ret;
	}
	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator+ (T&& rhs)const {
		UINT128 ret;
		ret.lo = lo + rhs;
		if (ret.lo < lo) {
			ret.hi++;
		}
		return ret;
	}
	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator- (const T& rhs)const {
		return *this + -(UINT128)rhs;
	}
	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator- (T&& rhs)const {
		return *this + -(UINT128)rhs;
	}
	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator*(const T& rhs)const {
		UINT128 L = mul(lo, rhs);
		ull H = hi * rhs;
		return L + UINT128(H, 0);
	}
	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator*(T&& rhs)const {
		UINT128 L = mul(lo, rhs);
		ull H = hi * rhs;
		return L + UINT128(H, 0);
	}

	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128	operator%(const T& mod)const {
		ull ret = mul((hi % mod), ((1ull << 63) % mod) * 2).lo % mod;
		ret = (ret + (lo % mod)) % mod;
		return ret;
	}
	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128	operator%(T&& mod)const {
		ull ret = mul((hi % mod), ((1ull << 63) % mod) * 2).lo % mod;
		ret = (ret + (lo % mod)) % mod;
		return ret;
	}


	UINT128 operator+=(const UINT128& rhs) {
		return *this = *this + rhs;
	}
	UINT128 operator+=(UINT128&& rhs) {
		return *this = *this + rhs;
	}
	UINT128 operator-=(const UINT128& rhs) {
		return *this = *this - rhs;
	}
	UINT128 operator-=(UINT128&& rhs) {
		return *this = *this - rhs;
	}
	UINT128 operator*=(const UINT128& rhs) {
		return *this = *this * rhs;
	}
	UINT128 operator*=(UINT128&& rhs) {
		return *this = *this * rhs;
	}

	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator+=(const T& rhs) {
		return *this = *this + rhs;
	}
	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator+=(T&& rhs) {
		return *this = *this + rhs;
	}
	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator-=(const T& rhs) {
		return *this = *this - rhs;
	}
	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator-=(T&& rhs) {
		return *this = *this - rhs;
	}
	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator*=(const T& rhs) {
		return *this = *this * rhs;
	}
	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator*=(T&& rhs) {
		return *this = *this * rhs;
	}

	UINT128 operator<<=(const int& rhs) {
		hi = rhs >= 64 ? 0 : (hi << rhs);
		ull carry = 0;
		carry = (rhs >= 64) ? (lo << (rhs - 64)) : (lo >> (64 - rhs));
		lo = rhs >= 64 ? 0 : (lo << rhs);
		hi += carry;
		return *this;
	}
	UINT128 operator<<=(int&& rhs) {
		hi = rhs >= 64 ? 0 : (hi << rhs);
		ull carry = 0;
		carry = (rhs >= 64) ? (lo << (rhs - 64)) : (lo >> (64 - rhs));
		lo = rhs >= 64 ? 0 : (lo << rhs);
		hi += carry;
		return *this;
	}
	UINT128 operator>>=(const int& rhs) {
		lo = (rhs >= 64) ? 0 : (lo >> rhs);
		ull carry = 0;
		carry = (rhs >= 64) ? (hi >> (rhs - 64)) : (hi << (64 - rhs));
		hi = (rhs >= 64) ? 0 : (hi >> rhs);
		lo += carry;
		return *this;
	}
	UINT128 operator>>=(int&& rhs) {
		lo = (rhs >= 64) ? 0 : (lo >> rhs);
		ull carry = 0;
		carry = (rhs >= 64) ? (hi >> (rhs - 64)) : (hi << (64 - rhs));
		hi = (rhs >= 64) ? 0 : (hi >> rhs);
		lo += carry;
		return *this;
	}

	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator%=(const T& rhs) {
		return *this = *this % rhs;
	}
	template <typename T, std::enable_if_t<std::is_integral<T>::value, T> = 0 >
	UINT128 operator%=(T&& rhs) {
		return *this = *this % rhs;
	}

	bool operator<(const UINT128& rhs)const {
		return hi < rhs.hi || (hi == rhs.hi && lo < rhs.lo);
	}
	bool operator<(UINT128&& rhs)const {
		return hi < rhs.hi || (hi == rhs.hi && lo < rhs.lo);
	}
	operator bool() { return hi | lo; }
	operator int() { return lo; }
	operator unsigned() { return lo; }
	operator long long() { return lo; }
	operator ull() { return lo; }
	operator short() { return lo; }
	operator unsigned short() { return lo; }
	operator char() { return lo; }
	operator unsigned char() { return lo; }
};
int UINT128::table[40][128];
bool UINT128::_init = 0;

ostream& operator<<(ostream& out, UINT128 x) {
	if (!UINT128::_init) {
		UINT128::init();
	}
	int buf[41];
	memset(buf, 0, sizeof(buf));
	for (int i = 0; i < 128; i++) {
		UINT128 t = (x >> i);
		if (t.lo & 1) {
			for (int j = 0; j < 40; j++) {
				buf[j] += UINT128::table[j][i];
				if (buf[j] >= 10) {
					buf[j] -= 10;
					buf[j + 1] += 1;
				}
			}
		}
	}
	int i;
	for (i = 39; buf[i] == 0; i--);
	for (; i >= 0; i--) {
		out << buf[i];
	}
	return out;
}
UINT128 mul(ull a, ull b) {
	ull a_lo = a & (0xffffffff), a_hi = a >> 32, b_lo = b & (0xffffffff), b_hi = b >> 32;
	ull lo = a_lo * b_lo;
	ull mid1 = a_hi * b_lo, mid2 = a_lo * b_hi;
	ull hi = a_hi * b_hi;
	ull nlo = lo + ((mid1 & (0xffffffff)) << 32);
	if (nlo < lo)hi++;
	lo = nlo + ((mid2 & (0xffffffff)) << 32);
	if (lo < nlo)hi++;
	hi += mid1 >> 32;
	hi += mid2 >> 32;
	return UINT128(hi, lo);
}

//建立ST表
struct node
{
	ll minimum, maximum, OR;
};
node st[1000005][20];
ll querymin(int l, int r)
{
	int k = log2(r - l + 1);
	return min(st[l][k].minimum, st[r - (1 << k) + 1][k].minimum);
}
ll querymax(int l, int r)
{
	int k = log2(r - l + 1);
	return max(st[l][k].maximum, st[r - (1 << k) + 1][k].maximum);
}
ll queryor(int l, int r)
{
	int k = log2(r - l + 1);
	return st[l][k].OR | st[r - (1 << k) + 1][k].OR;
}
int main()
{
	cin >> n;
	cin >> a0 >> k >> b >> mod;
	a[0] = a0;
	for (int i = 1; i <= n; i++) a[i] = (a[i - 1] * k + b) % mod;
	//初始构建ST表
	for (int i = 1; i <= n; i++) {
		st[i][0].minimum = a[i];
		st[i][0].maximum = a[i];
		st[i][0].OR = a[i];
	}
	for (int j = 1; j <= 20; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++) {
			st[i][j].minimum = min(st[i][j - 1].minimum, st[i + (1 << (j - 1))][j - 1].minimum);
			st[i][j].maximum = max(st[i][j - 1].maximum, st[i + (1 << (j - 1))][j - 1].maximum);
			st[i][j].OR = st[i][j - 1].OR | st[i + (1 << (j - 1))][j - 1].OR;
		}
	UINT128 ans = 0;
	//以某个a[i]作为最小值，向两边倍增扩展，寻找以a[i]为最小值的最长区间，那么这个区间对应的区间4个参数
	//乘积就是以a[i]为最小值的最大成绩。比较所有的这种值，找出最大的就是答案。
	//复杂度为0(nlgn)
	for (int i = 1; i <= n; i++) {
		int left = i, right = i;
		for (int j = 20; j >= 0; j--) {
			if ((right + (1 << j)) > n) continue;
			if (a[i] == querymin(i, right + (1 << j))) {
				right += (1 << j);
			}
		}
		for (int j = 20; j >= 0; j--) {
			if ((left - (1 << j)) < 1) continue;
			if (a[i] == querymin(left - (1 << j), i)) {
				left -= (1 << j);
			}
		}
		UINT128 temp = 1;
		temp *= a[i];
		temp *= querymax(left, right);
		temp *= queryor(left, right);
		temp *= (right - left + 1);
		if (ans < temp) ans = temp;
	}
	ans %= 998244353;
	cout << (ll)ans;
	return 0;
}