#include<iostream>
#include<cmath>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;

//���������پ���|xi-xj|+|yi-yj|,����ֵ�͵���ʽһ�㲻�ô������������ѧ����һ�����ɣ�����ת��Ϊ�б�ѩ����롣
//��Xi=xi+yi,Yi=xi-yi����ôԭ����Ҫ���|xi-xj|+|yi-yj|<=C�͵ȼ���|Xi-Xj|<=C,|Yi-Yj|<=C��
//�������������������վ��ֱ��ͨ�š�������벢�鼯�У��Դ�����ͨ�ŵ������

/*
�����е㰴x�����������δ�ÿ���㿪ʼ��һ������ά��һ��X����֮��<=c�Ķ��У����뵽��y���������set�У�ÿ�ӽ�һ���㣬
��set�в�����ǰ���������ǰ/����������Y֮��<=c�Ͱ�������ǰ/�����ӽ����鼯��
*/

const int N = 100005;
const int INF = 1e9 + 7;
struct node
{
	int x, y;
	node() {}
	node(int x, int y) :x(x), y(y) {}
}p[N];
int blocksize[N];//���С
//���鼯
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
set<pair<int, int>> s;//�洢��վ���б�ѩ��������ͱ��
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
		p[i] = node(x + y, x - y);//ת��Ϊ�б�ѩ�����
		fa[i] = i;//��ʼ�����鼯
	}
	sort(p + 1, p + n + 1, [&](node a, node b) {return a.x < b.x; });//����X��������
	int tail = 1;//����βָ��
	s.insert(make_pair(INF, n + 1));
	s.insert(make_pair(-INF, 0));
	for (int i = 1; i <= n; ++i) {
		s.insert(make_pair(p[i].y, i));//����վ���б�ѩ��������ͱ�Ų���set��
		while (tail < n && (p[tail + 1].x - p[i].x <= c)) {
			tail++;//�������ڼ������һ���
			s.insert(make_pair(p[tail].y, tail));
			//��ʱ���������еĻ�վ���б�ѩ��������ֵ������c
			pair<int, int>pre = *(--(s.find(make_pair(p[tail].y, tail))));//�ҵ���ǰ��վ��ǰ��
			pair<int, int>suc = *(++(s.find(make_pair(p[tail].y, tail))));//�ҵ���ǰ��վ�ĺ��
			if (p[tail].y - pre.first <= c) merge(tail, pre.second);//���ǰ���͵�ǰ��վ���б�ѩ������������ֵ������c����ô�ϲ�
			if (suc.first - p[tail].y <= c) merge(tail, suc.second);//�����̺͵�ǰ��վ���б�ѩ������������ֵ������c����ô�ϲ�
		}
		s.erase(make_pair(p[i].y, i));//ɾ����������ͷ���Ļ�վ
	}
	int num = 0, maximumblock = 0;
	for (int i = 1; i <= n; ++i)
	{
		int id = findfa(i);
		if (id == i) num++;//ͳ�Ʋ��鼯�еĿ���
		blocksize[id]++;//ͳ��ÿ����Ĵ�С
	}
	for (int i = 1; i <= n; ++i)
	{
		maximumblock = max(maximumblock, blocksize[i]);//�ҵ����Ŀ�
	}
	cout << num << '\n' << maximumblock;
	return 0;
}