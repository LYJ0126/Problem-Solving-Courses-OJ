#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int T[12][12], mission[12], a[12], choose[12][2], choosed[12][2], sj[52] = { 0 };
/*
	T[i][0]��ʾ��i�������ʱ����м���������T[i][����]��ʾ��ʼʱ�䣬T[i][ż��]��ʾ����ʱ��
	missionǰk���Ǳ�����ɵ�����ı�ţ�ͨ������a�ı�ǹ��ɺ󣬺�m-k���ǷǱ�������ı��
	chooseΪ�ݹ�ʱÿһ����ѡ�������ʱ��Σ�����choose[i][0]Ϊ�����ţ�choose[i][1]Ϊʱ���
	sj���ʱ�䣬0Ϊδ��ռ�ã�1Ϊ��ռ��
*/
int n, m, k;
const int no = -1;
bool flag = false;//flag��ʾ�ܷ�������Ա�������
void dfs(int n, int num)
{
	if (n > k) {
		flag = true;
	}
	if (n == m + 1) {
		//�ҳ�Ŀǰѡ������ѷ����ж��ٸ�����ѡ��
		int sum2 = 0;
		for (int i = 0; i <= 11; i++) {
			if (choosed[i][0] != 0) {
				sum2++;
			}
		}
		//����ʱ�и��õķ�����choose��Ϊchoosed
		if (num - 1 > sum2) {
			for (int i = 0; i <= 11; i++) {
				for (int j = 0; j <= 1; j++) {
					choosed[i][j] = choose[i][j];
				}
			}
		}
		return;
	}
	//�Ȱѱ����������
	if (n <= k) {
		for (int j = 1; j <= 2 * T[mission[n]][0] - 1; j += 2) {
			int check = 0;
			//����Ƿ���ʱ��γ�ͻ
			for (int i = T[mission[n]][j]; i < T[mission[n]][j + 1]; i++) {
				if (sj[i] == 1) {
					check = 1;
					break;
				}
			}
			//�г�ͻ������һ��ʱ���
			if (check == 1) {
				continue;
			}
			//����ѡ����ʱ���
			else {
				choose[n][0] = mission[n];
				choose[n][1] = (j + 1) / 2;
				for (int i = T[mission[n]][j]; i < T[mission[n]][j + 1]; i++)
				{
					sj[i] = 1;
				}
				//��һ��
				dfs(n + 1, num + 1);
				//����
				for (int i = T[mission[n]][j]; i < T[mission[n]][j + 1]; i++) {
					sj[i] = 0;
				}
				choose[n][1] = 0;
				choose[n][0] = 0;
			}
		}
	}
	//�������񶼿���ɺ�ѡ��Ǳ�������
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
		//������Ϊmission[n]������������ʱ��ζ����У����������񣬿���һ������
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
	if (flag) {//�������
		int sum3 = 0;//sum3��ʾ������ɵ�������
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
