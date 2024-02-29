#include<iostream>
#include<cmath>
using namespace std;

//通过凯莱表判断是否是半群、幺半群、群
int table[51][51];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> table[i][j];
		}
	}
	//判断是否是半群,即是否满足结合律
	bool semigroup = true;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			for (int k = 1; k <= n; ++k) {
				if (table[table[i][j]][k] != table[i][table[j][k]]) {
					semigroup = false;
					break;
				}
			}
		}
	}
	//判断是否是幺半群,即是否有单位元
	bool monoid = false;
	int identity = 0;
	if (semigroup) {
		for (int i = 1; i <= n; ++i) {
			bool id = true;
			for (int j = 1; j <= n; ++j) {
				if (table[i][j] != j || table[j][i] != j) {
					id = false;
					break;
				}
			}
			if (id) {
				if (!monoid) {
					monoid = true;
					identity = i;
				}
				else {//前面已经检测出有单位元，现在又出现"单位元"
					monoid = false;
					break;
				}
			}
		}
	}
	//判断是否是群,即是否有逆元
	bool group = true;
	if (monoid) {
		for (int i = 1; i <= n; ++i) {
			bool inv = false;
			bool multiinv = false;//判断有没有重复逆元
			for (int j = 1; j <= n; ++j) {
				if ((table[i][j] == identity && table[j][i] != identity) || (table[j][i] == identity && table[i][j] != identity)) {
					inv = false;
					break;
				}
				else if (table[i][j] == identity && table[j][i] == identity) {
					if (!inv) {
						inv = true;
					}
					else {
						multiinv = true;
						break;
					}
				}
			}
			if (!inv) {
				group = false;
				break;
			}
			if (multiinv) {
				group = false;
				break;
			}
		}
	}
	if (n == 0) {
		cout << 5;
		return 0;
	}
	if (semigroup) {
		if (monoid) {
			if (group) {
				cout << 5;
			}
			else cout << 4;//独异点和幺半群是一个概念，按照题目要求，应该输出4而不是3
		}
		else cout << 2;
	}
	else cout << 1;
	return 0;
}