#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

//快读
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
//快写
void output(int x) {
	if (x > 9) output(x / 10);
	putchar(x % 10 + '0');
}
const int maxn = 1e7 + 1;
int f[maxn];//f[i]表示i的父节点
//int dep[maxn];//dep[i]表示i的深度
//任何一个数对应的节点，其父节点为该数除以其最小质因子
//找出每个数的最小质因子，进而找出每个数的父节点
//树的根节点为1

bool vis[maxn], hasf[maxn];
void init()
{
	vis[0] = vis[1] = true;
	memset(hasf, 0, sizeof(hasf));
	//埃氏筛
	for (int i = 2; i < maxn; ++i) {
		if (!vis[i]) {
			f[i] = 1;//质数的父节点为1
			hasf[i] = true;//找到了父节点
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
//找LCA
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