#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

//���
int input() {
	int x = 0;
	char ch = getchar();
	while (ch < '0' || ch>'9') ch = getchar();
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x;
}
//��д
void output(int x) {
	if (x > 9) output(x / 10);
	putchar(x % 10 + '0');
}
const int maxn = 1e7 + 1;
int f[maxn];//f[i]��ʾi�ĸ��ڵ�
//int dep[maxn];//dep[i]��ʾi�����
//�κ�һ������Ӧ�Ľڵ㣬�丸�ڵ�Ϊ������������С������
//�ҳ�ÿ��������С�����ӣ������ҳ�ÿ�����ĸ��ڵ�
//���ĸ��ڵ�Ϊ1

bool vis[maxn], hasf[maxn];
void init()
{
	vis[0] = vis[1] = true;
	memset(hasf, 0, sizeof(hasf));
	//����ɸ
	for (int i = 2; i < maxn; ++i) {
		if (!vis[i]) {
			f[i] = 1;//�����ĸ��ڵ�Ϊ1
			hasf[i] = true;//�ҵ��˸��ڵ�
			//dep[i] = 1;
			if (1LL * i * i < maxn) {
				for (int j = i + i; j < maxn; j += i) {
					vis[j] = true;
					if (!hasf[j]) {
						hasf[j] = true;
						int fa = j / i;
						f[j] = fa;
					}
					//dep[j] = dep[fa] + 1;
				}
			}
		}
	}
}
//��LCA
int LCA(int x, int y) {
	while (x != y) {
		if (x > y) x = f[x];
		else y = f[y];
	}
	return x;
	/*while (dep[x] > dep[y]) x = f[x];
	while (dep[y] > dep[x]) y = f[y];
	while (x != y) {
		x = f[x];
		y = f[y];
	}
	return x;*/
}
int main() {
	init();
	int q = input();
	for (int i = 0; i < q; ++i) {
		int x = input(), y = input();
		output(LCA(x, y));
		putchar('\n');
	}
	return 0;
}