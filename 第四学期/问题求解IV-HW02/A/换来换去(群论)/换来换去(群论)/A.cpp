#include<iostream>
#include<cmath>
using namespace std;

int T, x[4];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
	for (int i = 0; i < T; ++i) {
		cin >> x[1] >> x[2] >> x[3];
		//ԭ����Ⱥ�ǰ�����Ⱥ������д��x1^k1x2^k2x3^k3��
		//Ҫ�ص�ԭ����Ⱥ��ֻ��Ҫ��֤k1=k2=k3��ż����ͬ���ɡ�
		int tempx1 = x[1] & 1;
		int tempx2 = x[2] & 1;
		int tempx3 = x[3] & 1;
		if (tempx1 == tempx2 && tempx2 == tempx3) {
			cout << "y\n";
			for (int k = 1; k <= 3; ++k) {
				for (int j = 1; j <= x[k]; ++j) {
					cout << k << ' ';
				}
			}
			cout << '\n';
		}
		else cout << "n\n";
	}
	return 0;
}