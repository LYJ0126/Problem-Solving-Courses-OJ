#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

int T, n, p[1001], k;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int i = 0; i < T; ++i) {
		cin >> n;
		for (int j = 1; j <= n; ++j) {
			cin >> p[j];
		}
		cin >> k;
		//���ҵ�ѭ���ڵĳ���
		int len = 0;
		bool flag = false;//����Ƿ��ҵ�ѭ����
		vector<int>temp1(n + 1);
		for (int j = 1; j <= n; ++j) temp1[j] = p[j];//����һ��p
		while (!flag) {
			vector<int>temp2(n + 1);
			//��һ��
			for (int j = 1; j <= n; ++j) temp2[j] = temp1[temp1[j]];
			temp1 = temp2;
			++len;
			//�ж��Ƿ��ҵ�ѭ����
			int pos = 1;
			while (pos <= n && temp1[pos] == p[pos]) ++pos;
			if (pos > n) flag = true;//�ҵ�ѭ����
		}
		int rest = len - k % len;//����k��֮�󣬻�ʣ�¶��ٲ�����ʼ״̬
		while (rest--) {
			vector<int>temp(n + 1);
			for (int j = 1; j <= n; ++j) temp[j] = p[p[j]];
			for (int j = 1; j <= n; ++j) p[j] = temp[j];
		}
		//���
		for (int j = 1; j <= n; ++j) cout << p[j] << " ";
		cout << endl;
	}
	return 0;
}