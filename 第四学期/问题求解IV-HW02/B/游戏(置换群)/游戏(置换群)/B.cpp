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
		//先找到循环节的长度
		int len = 0;
		bool flag = false;//标记是否找到循环节
		vector<int>temp1(n + 1);
		for (int j = 1; j <= n; ++j) temp1[j] = p[j];//复制一份p
		while (!flag) {
			vector<int>temp2(n + 1);
			//走一步
			for (int j = 1; j <= n; ++j) temp2[j] = temp1[temp1[j]];
			temp1 = temp2;
			++len;
			//判断是否找到循环节
			int pos = 1;
			while (pos <= n && temp1[pos] == p[pos]) ++pos;
			if (pos > n) flag = true;//找到循环节
		}
		int rest = len - k % len;//走了k步之后，还剩下多少步到初始状态
		while (rest--) {
			vector<int>temp(n + 1);
			for (int j = 1; j <= n; ++j) temp[j] = p[p[j]];
			for (int j = 1; j <= n; ++j) p[j] = temp[j];
		}
		//输出
		for (int j = 1; j <= n; ++j) cout << p[j] << " ";
		cout << endl;
	}
	return 0;
}