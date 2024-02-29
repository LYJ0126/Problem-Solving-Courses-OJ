#include<iostream>
#include<cmath>
using namespace std;

//ͨ���������ж��Ƿ��ǰ�Ⱥ���۰�Ⱥ��Ⱥ
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
	//�ж��Ƿ��ǰ�Ⱥ,���Ƿ���������
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
	//�ж��Ƿ����۰�Ⱥ,���Ƿ��е�λԪ
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
				else {//ǰ���Ѿ������е�λԪ�������ֳ���"��λԪ"
					monoid = false;
					break;
				}
			}
		}
	}
	//�ж��Ƿ���Ⱥ,���Ƿ�����Ԫ
	bool group = true;
	if (monoid) {
		for (int i = 1; i <= n; ++i) {
			bool inv = false;
			bool multiinv = false;//�ж���û���ظ���Ԫ
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
			else cout << 4;//�������۰�Ⱥ��һ�����������ĿҪ��Ӧ�����4������3
		}
		else cout << 2;
	}
	else cout << 1;
	return 0;
}