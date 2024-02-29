#include<iostream>
using namespace std;

int n, f[1000002], x, y, sum = 0;
//��ʼ��
void init()
{
	int i;
	for (i = 1; i <= n; i++)
	{
		f[i] = i;
	}
	return;
}
//Ѱ��һ��Ԫ�صĸ��ڵ�
int getf(int s)
{
	if (f[s] == s) {
		return s;
	}
	else
	{
		f[s] = getf(f[s]);
		return f[s];
	}
}
//������Ԫ�����ڵ������϶�Ϊһ��y���ڵ����ĸ��ڵ�ָ��x�������ĸ��ڵ㣩
void merge(int x, int y)
{
	int t1 = getf(x);
	int t2 = getf(y);
	if (t1 != t2) {
		f[t2] = t1;
	}
	return;
}
int main()
{
	cin >> n;
	init();
	for (int i = 1; i <= n; i++)
	{
		cin >> x >> y;
		merge(x, y);
	}
	for (int i = 1; i <= n; i++)
	{
		if (f[i] == i)
			sum++;
	}
	cout << n - sum << endl;
	return 0;
}