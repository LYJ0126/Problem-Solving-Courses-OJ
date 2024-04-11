#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

string s;
//ע��s�е��ַ�������'0',�Һܳ�,���Բ���ֱ��ת����int
inline int compare(int left1, int right1, int left2, int right2)
{
	//�Ƚ�s[left1,right1]��s[left2,right2]
	//����1��ʾǰ�ߴ�,����-1��ʾ���ߴ�,����0��ʾ���
	//��ȥ��ǰ��0
	while (left1 <= right1 && s[left1] == '0')left1++;
	while (left2 <= right2 && s[left2] == '0')left2++;
	if (left1 > right1) {//ǰ��ȫ��0
		if (left2 > right2) return 0;//����Ҳȫ��0
		else return -1;//���߲�ȫ��0
	}
	if (left2 > right2) return 1;//ǰ�߲�ȫ��0,����ȫ��0
	//ǰ�ߺͺ��߶���ȫ��0
	if (right1 - left1 > right2 - left2) return 1;//ǰ�߳��ȴ�
	if (right1 - left1 < right2 - left2) return -1;//���߳��ȴ�
	//ǰ�ߺͺ��߳������
	while (left1 <= right1 && left2 <= right2) {
		if (s[left1] > s[left2]) return 1;
		if (s[left1] < s[left2]) return -1;
		left1++; left2++;
	}
	return 0;
}

//��f[i]Ϊs[0,i]����û��ַ��������һ��������ʼλ��
//��ôӦ����s[f[f[i]-1],f[i]-1]<s[f[i],i],��f[i]Ӧ�������ܴ�(�ӽ�i)
//f[0]=0
int f[1001];
//Ҫʹ�ֵ������
//��g[i]Ϊs[i,n-1]����û��ַ����е�һ�����Ľ���λ��
//��ôӦ����s[i,g[i]]<s[g[i]+1,g[g[i]+1]],��g[i]Ӧ�������ܴ�
int g[1001];

int main()
{
	cin >> s;
	int n = s.size();
	//����f
	f[0] = 0;
	for (int i = 1; i < n; ++i) {
		int j = i;
		while (j > 0) {
			int temp = compare(f[j - 1], j - 1, j, i);
			if (temp == -1) break;//s[f[j-1],j-1]<s[j,i]
			j--;
		}
		f[i] = j;
	}
	//for (int i = 0; i < n; ++i)cout << f[i] << ' ';
	//����f��ʼ��g
	//��f[n-1]��ʼ��n-1��g[i]��Ϊn-1�����Ǳ�֤���һ�����¼Ǽ������С�����������ڴ�ǰ���¼���g
	for (int i = f[n - 1]; i < n; ++i) g[i] = n - 1;
	//����g
	for (int i = f[n - 1] - 1; i >= 0; --i) {
		if (compare(i, n - 1, f[n - 1], g[n - 1]) == 0) {//˵����i��f[n-1]-1����'0'
			g[i] = n - 1;
			continue;
		}
		int j = n - 2;
		while (j >= i) {
			int temp = compare(i, j, j + 1, g[j + 1]);
			if (temp == -1) break;//s[i,j]<s[j+1,g[j+1]]
			j--;
		}
		g[i] = j;
	}
	//cout << endl;
	//for (int i = 0; i < n; ++i)cout << g[i] << ' ';
	//������
	int left = 0, right = g[0];
	for (int i = left; i <= right; ++i) cout << s[i];
	left = right + 1;
	while (left < n) {
		right = g[left];
		cout << ',';
		for (int i = left; i <= right; ++i) cout << s[i];
		left = right + 1;
	}
	return 0;
}