
//暴力做法是三重循环，时间复杂度为O(n^3)
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;
int n, x, y, color, ans = 0;
int graph[210][210];
int main()
{
	cin >> n;
	int num = n * (n - 1) / 2;
	for (int i = 1; i <= num; i++) {
		cin >> x >> y >> color;
		graph[x][y] = color;
		graph[y][x] = color;
	}
	for (int i = 1; i <= n - 2; i++) {
		for (int j = i + 1; j <= n - 1; j++) {
			for (int k = j + 1; k <= n; k++) {
				if (graph[i][j] == graph[j][k] && graph[i][k] == graph[i][j]) ans++;
			}
		}
	}
	cout << ans;
	return 0;
}