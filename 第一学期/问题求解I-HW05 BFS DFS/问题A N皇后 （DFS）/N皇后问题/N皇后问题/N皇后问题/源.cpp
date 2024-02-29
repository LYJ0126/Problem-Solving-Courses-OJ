#include<iostream>
#include<cmath>
using namespace std;
int n;
int queenpos[100];
//存放算好的皇后位置，左上角（0,0）
void nqueen(int k)//在0到k-1行皇后已经摆好的情况下，摆第k行的皇后
{
	int i;
	if (k == n)
	{
		for (i = 0; i < n; i++) {
			cout << queenpos[i] + 1 << ' ';
		}
		cout << endl;
		return;
	}
	for (i = 0; i < n; i++)//逐步尝试第k个皇后的位置
	{
		int j;
		for (j = 0; j < k; j++)//和已经摆好的k个皇后的位置比较，看是否冲突
		{
			if (queenpos[j] == i || abs(queenpos[j] - i) == abs(k - j)) {
				break;//冲突，试下一个位置
			}
		}
		if (j == k) {
			queenpos[k] = i;
			nqueen(k + 1);
		}
	}
}
int main()
{
	cin >> n;
	nqueen(0);
	return 0;
}