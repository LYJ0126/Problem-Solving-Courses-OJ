#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

int n, x, y, color;
int graph[203][203];//邻接表存图
int main()
{
	cin >> n;
	int num = n * (n - 1) / 2;//边数
	for (int i = 0; i < num; ++i) {
		cin >> x >> y >> color;
		graph[x][y] = graph[y][x] = color;
	}
	int total = n * (n - 1) * (n - 2) / 6;//总三角形数为C(n,3)
	//下面思考，我们只要用总三角形数减去有两条边(不需考虑第三条边)颜色不同的三角形的数量就是我们要的答案
	int temp = 0;//记录不合要求的三角形个数
	for (int i = 1; i <= n; i++) {//遍历每一个顶点，当这个顶点出发有两条颜色不同的边，那就是我们要的三角形
		int black = 0;
		for (int j = 1; j <= n; j++) {
			if (j == i) continue;//注意别把i自己算上了
			if (graph[i][j]) black++;
		}
		temp += (black * (n - 1 - black));
	}
	temp >>= 1;//一个异色三角形会被它的两个“异色邻边顶点”计算两次
	cout << total - temp;
	return 0;
}