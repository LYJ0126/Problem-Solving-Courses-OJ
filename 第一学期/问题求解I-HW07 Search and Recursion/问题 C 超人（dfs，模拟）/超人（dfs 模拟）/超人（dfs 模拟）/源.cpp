#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int T[12][12], mission[12], a[12], choose[12][2], choosed[12][2], sj[52] = { 0 };
/*
	T[i][0]表示第i个人物的时间段有几个，后面T[i][奇数]表示开始时间，T[i][偶数]表示结束时间
	mission前k个是必须完成的任务的编号，通过数组a的标记过渡后，后m-k个是非必须任务的编号
	choose为递归时每一步所选择的任务及时间段，其中choose[i][0]为任务编号，choose[i][1]为时间段
	sj标记时间，0为未被占用，1为已占用
*/
int n, m, k;
const int no = -1;
bool flag = false;//flag表示能否完成所以必须任务
void dfs(int n, int num)
{
	if (n > k) {
		flag = true;
	}
	if (n == m + 1) {
		//找出目前选定的最佳方案有多少个任务选中
		int sum2 = 0;
		for (int i = 0; i <= 11; i++) {
			if (choosed[i][0] != 0) {
				sum2++;
			}
		}
		//若此时有更好的方案，choose变为choosed
		if (num - 1 > sum2) {
			for (int i = 0; i <= 11; i++) {
				for (int j = 0; j <= 1; j++) {
					choosed[i][j] = choose[i][j];
				}
			}
		}
		return;
	}
	//先把必须任务完成
	if (n <= k) {
		for (int j = 1; j <= 2 * T[mission[n]][0] - 1; j += 2) {
			int check = 0;
			//检查是否有时间段冲突
			for (int i = T[mission[n]][j]; i < T[mission[n]][j + 1]; i++) {
				if (sj[i] == 1) {
					check = 1;
					break;
				}
			}
			//有冲突，则看下一个时间段
			if (check == 1) {
				continue;
			}
			//否则选定该时间段
			else {
				choose[n][0] = mission[n];
				choose[n][1] = (j + 1) / 2;
				for (int i = T[mission[n]][j]; i < T[mission[n]][j + 1]; i++)
				{
					sj[i] = 1;
				}
				//下一步
				dfs(n + 1, num + 1);
				//回溯
				for (int i = T[mission[n]][j]; i < T[mission[n]][j + 1]; i++) {
					sj[i] = 0;
				}
				choose[n][1] = 0;
				choose[n][0] = 0;
			}
		}
	}
	//必须任务都可完成后，选择非必须任务
	if (n > k) {
		for (int t = 1; t <= 2 * T[mission[n]][0] - 1; t += 2) {
			int check = 0;
			for (int i = T[mission[n]][t]; i < T[mission[n]][t + 1]; i++) {
				if (sj[i] == 1) {
					check = 1;
					break;
				}
			}
			if (check == 1) {
				continue;
			}
			else {
				choose[n][0] = mission[n];
				choose[n][1] = (t + 1) / 2;
				for (int i = T[mission[n]][t]; i < T[mission[n]][t + 1]; i++)
				{
					sj[i] = 1;
				}
				dfs(n + 1, num + 1);
				for (int i = T[mission[n]][t]; i < T[mission[n]][t + 1]; i++) {
					sj[i] = 0;
				}
				choose[n][1] = 0;
				choose[n][0] = 0;
			}
		}
		//如果编号为mission[n]这个任务的所有时间段都不行，跳过该任务，看下一个任务
		dfs(n + 1, num);
	}
}
int main()
{

	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++)
	{
		cin >> T[i][0];
		for (int j = 1; j <= 2 * T[i][0]; j++)
		{
			cin >> T[i][j];
		}
	}
	for (int i = 1; i <= k; i++) {
		cin >> mission[i];
		a[mission[i]] = 1;
	}
	int s = k + 1;
	for (int i = 1; i <= m; i++)
	{
		if (a[i] == 0) {
			mission[s] = i;
			s++;
		}
	}
	dfs(1, 1);
	if (flag) {//如果可行
		int sum3 = 0;//sum3表示可以完成的任务数
		for (int i = 0; i <= 11; i++) {
			if (choosed[i][0] != 0)
				sum3++;
		}
		cout << sum3 << endl;
		for (int i = 1; i <= 11; i++) {
			if (choosed[i][0] != 0) {
				cout << choosed[i][0] << ' ' << choosed[i][1] << endl;
			}
		}
	}
	else {
		cout << no;
	}
	return 0;
}
