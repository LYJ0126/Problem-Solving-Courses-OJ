#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

string s;
//注意s中的字符可能有'0',且很长,所以不能直接转换成int
inline int compare(int left1, int right1, int left2, int right2)
{
	//比较s[left1,right1]和s[left2,right2]
	//返回1表示前者大,返回-1表示后者大,返回0表示相等
	//先去掉前导0
	while (left1 <= right1 && s[left1] == '0')left1++;
	while (left2 <= right2 && s[left2] == '0')left2++;
	if (left1 > right1) {//前者全是0
		if (left2 > right2) return 0;//后者也全是0
		else return -1;//后者不全是0
	}
	if (left2 > right2) return 1;//前者不全是0,后者全是0
	//前者和后者都不全是0
	if (right1 - left1 > right2 - left2) return 1;//前者长度大
	if (right1 - left1 < right2 - left2) return -1;//后者长度大
	//前者和后者长度相等
	while (left1 <= right1 && left2 <= right2) {
		if (s[left1] > s[left2]) return 1;
		if (s[left1] < s[left2]) return -1;
		left1++; left2++;
	}
	return 0;
}

//设f[i]为s[0,i]的最好划分方案中最后一个数的起始位置
//那么应当有s[f[f[i]-1],f[i]-1]<s[f[i],i],且f[i]应当尽可能大(接近i)
//f[0]=0
int f[1001];
//要使字典序最大
//设g[i]为s[i,n-1]的最好划分方案中第一个数的结束位置
//那么应当有s[i,g[i]]<s[g[i]+1,g[g[i]+1]],且g[i]应当尽可能大
int g[1001];

int main()
{
	cin >> s;
	int n = s.size();
	//计算f
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
	//根据f初始化g
	//从f[n-1]开始到n-1，g[i]都为n-1。这是保证最后一个大事记纪念度最小，后面则是在此前提下计算g
	for (int i = f[n - 1]; i < n; ++i) g[i] = n - 1;
	//计算g
	for (int i = f[n - 1] - 1; i >= 0; --i) {
		if (compare(i, n - 1, f[n - 1], g[n - 1]) == 0) {//说明从i到f[n-1]-1都是'0'
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
	//输出结果
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