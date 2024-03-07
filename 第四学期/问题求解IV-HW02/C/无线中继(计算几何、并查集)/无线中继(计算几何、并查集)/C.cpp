#include<iostream>
#include<cmath>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;

//对于曼哈顿距离|xi-xj|+|yi-yj|,绝对值和的形式一般不好处理。计算机几何学中有一个技巧，就是转化为切比雪夫距离。
//令Xi=xi+yi,Yi=xi-yi。那么原题所要求的|xi-xj|+|yi-yj|<=C就等价于|Xi-Xj|<=C,|Yi-Yj|<=C。
//符合这个条件的两个基站能直接通信。将其加入并查集中，以处理间接通信的情况。

/*
把所有点按x坐标排序，依次从每个点开始朝一个方向维护一个X坐标之差<=c的队列，加入到按y坐标排序的set中，每加进一个点，
在set中查找其前后驱，如果前/后驱与他的Y之差<=c就把他和他前/后驱加进并查集。
*/

const int N = 100005;
const int INF = 1e9 + 7;
struct node
{
	int x, y;
	node() {}
	node(int x, int y) :x(x), y(y) {}
}p[N];
int blocksize[N];//块大小
//并查集
int fa[N];
int findfa(int x)
{
	if (fa[x] == x) return x;
	else return fa[x] = findfa(fa[x]);
}
void merge(int x, int y)
{
	int fx = findfa(x);
	int fy = findfa(y);
	if (fx != fy) fa[fy] = fx;
}
set<pair<int, int>> s;//存储基站的切比雪夫纵坐标和编号
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, c;
	cin >> n >> c;
	int x, y;
	for (int i = 1; i <= n; i++)
	{
		cin >> x >> y;
		p[i] = node(x + y, x - y);//转化为切比雪夫距离
		fa[i] = i;//初始化并查集
	}
	sort(p + 1, p + n + 1, [&](node a, node b) {return a.x < b.x; });//按照X坐标排序
	int tail = 1;//队列尾指针
	s.insert(make_pair(INF, n + 1));
	s.insert(make_pair(-INF, 0));
	for (int i = 1; i <= n; ++i) {
		s.insert(make_pair(p[i].y, i));//将基站的切比雪夫纵坐标和编号插入set中
		while (tail < n && (p[tail + 1].x - p[i].x <= c)) {
			tail++;//滑动窗口继续向右滑动
			s.insert(make_pair(p[tail].y, tail));
			//此时滑动窗口中的基站的切比雪夫横坐标差值不超过c
			pair<int, int>pre = *(--(s.find(make_pair(p[tail].y, tail))));//找到当前基站的前驱
			pair<int, int>suc = *(++(s.find(make_pair(p[tail].y, tail))));//找到当前基站的后继
			if (p[tail].y - pre.first <= c) merge(tail, pre.second);//如果前驱和当前基站的切比雪夫纵坐标差绝对值不超过c，那么合并
			if (suc.first - p[tail].y <= c) merge(tail, suc.second);//如果后继和当前基站的切比雪夫纵坐标差绝对值不超过c，那么合并
		}
		s.erase(make_pair(p[i].y, i));//删除滑动窗口头部的基站
	}
	int num = 0, maximumblock = 0;
	for (int i = 1; i <= n; ++i)
	{
		int id = findfa(i);
		if (id == i) num++;//统计并查集中的块数
		blocksize[id]++;//统计每个块的大小
	}
	for (int i = 1; i <= n; ++i)
	{
		maximumblock = max(maximumblock, blocksize[i]);//找到最大的块
	}
	cout << num << '\n' << maximumblock;
	return 0;
}