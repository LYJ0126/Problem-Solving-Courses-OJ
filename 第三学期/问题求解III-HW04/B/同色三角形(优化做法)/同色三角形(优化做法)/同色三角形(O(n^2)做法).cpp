#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

int n, x, y, color;
int graph[203][203];//�ڽӱ��ͼ
int main()
{
	cin >> n;
	int num = n * (n - 1) / 2;//����
	for (int i = 0; i < num; ++i) {
		cin >> x >> y >> color;
		graph[x][y] = graph[y][x] = color;
	}
	int total = n * (n - 1) * (n - 2) / 6;//����������ΪC(n,3)
	//����˼��������ֻҪ��������������ȥ��������(���迼�ǵ�������)��ɫ��ͬ�������ε�������������Ҫ�Ĵ�
	int temp = 0;//��¼����Ҫ��������θ���
	for (int i = 1; i <= n; i++) {//����ÿһ�����㣬��������������������ɫ��ͬ�ıߣ��Ǿ�������Ҫ��������
		int black = 0;
		for (int j = 1; j <= n; j++) {
			if (j == i) continue;//ע����i�Լ�������
			if (graph[i][j]) black++;
		}
		temp += (black * (n - 1 - black));
	}
	temp >>= 1;//һ����ɫ�����λᱻ������������ɫ�ڱ߶��㡱��������
	cout << total - temp;
	return 0;
}