#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include <stdio.h>
using namespace std;

int n, m, r = 1, s, u = -1, sx = 0, sy = 0;
char a[1001][1001];
int a2[1001][1001];
int check[1001][1001];
int gx[1000001], gy[1000001];
int quex[1000001], quey[1000001], questep[1000001];
int nex[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };

int bfs()
{
	int head = 1, tail = 1, flag = 0, i, j, nx, ny;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
		{

		}
	quex[tail] = sx;
	quey[tail] = sy;
	questep[tail] = 0;
	tail++;
	while (head < tail)
	{
		for (int f = 0; f <= 3; f++)
		{
			nx = quex[head] + nex[f][0];
			ny = quey[head] + nex[f][1];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && a2[nx][ny] == 0)
			{
				a2[nx][ny] = 1;
				quex[tail] = nx;
				quey[tail] = ny;
				questep[tail] = questep[head] + 1;
				tail++;
			}
			if (check[nx][ny] == -2) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			return questep[tail - 1];
		}
		head++;
	}
	if (flag == 0) {
		return 0;
	}
}
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			cin >> a[i][j];
			if (a[i][j] == 'P') {
				a2[i][j] = 0;
			}
			else if (a[i][j] == 'G') {
				a2[i][j] = 0;
				check[i][j] = -2;
			}
			else if (a[i][j] == 'B') {
				a2[i][j] = -1;
			}
			else if (a[i][j] = 'D') {
				a2[i][j] = 1;
				sx = i;
				sy = j;
			}
		}
	int num = bfs();
	if (num == 0) {
		cout << u;
	}
	else cout << num << endl;
	return 0;
}