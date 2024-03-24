#include<iostream>
#include<cmath>
#include<bitset>
using namespace std;

const int maxn = 30000001;
bitset<maxn> isprime;
int prime[2000000];
int prime_num = 0;
//线性筛
void get_prime()
{
	isprime.set();
	isprime[0] = isprime[1] = 0;
	for (int i = 2; i < maxn; i++)
	{
		if (isprime[i])
		{
			prime[prime_num++] = i;
		}
		for (int j = 0; j < prime_num && i * prime[j] <= maxn; j++)
		{
			isprime[i * prime[j]] = 0;
			if (i % prime[j] == 0) break;
		}
	}
}
int main()
{
	int n;
	cin >> n;
	get_prime();
	int left, right;
	while (n--) {
		cin >> left >> right;
		if (left > right) {
			cout << 0 << "\n";
			continue;
		}
		//二分查找
		//查找第一个不小于left的素数的下标
		int l = 0, r = prime_num - 1;
		while (l <= r) {
			int mid = (l + r) / 2;
			if (prime[mid] < left) {
				l = mid + 1;
			}
			else {
				r = mid - 1;
			}
		}
		int left_index = l;
		//查找最后一个不大于right的素数的下标
		l = 0, r = prime_num - 1;
		while (l <= r) {
			int mid = (l + r) / 2;
			if (prime[mid] > right) {
				r = mid - 1;
			}
			else {
				l = mid + 1;
			}
		}
		int right_index = r;
		cout << right_index - left_index + 1 << "\n";
	}
	return 0;
}