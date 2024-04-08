#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;

//tips��ÿ���㵽����·���ϲ�ͬ��gcdȡֵ��log_2n������,������dfs��ʱ����Դ洢ÿ��������������gcdֵ�Լ�������
//�������Լ��ٲ�ѯ

typedef unsigned long long ull;
const ull mod = 1e9 + 7;
ull n, ans = 0;
vector<ull>p;//��¼ÿ����ׯ(��)�ġ����ٶȡ�
vector<vector<int>>tree;//��¼���Ľṹ,1Ϊ���ڵ�
vector<vector<ull>>gcds;//��¼ÿ���㵽����ڵ�(��������)��gcdֵ�͸���,����gcds[i][j]��17λ��ʾ��gcdֵ�ĸ�����ǰ47λ��ʾgcdֵ

ull gcd(ull a, ull b) {//�����Լ��
	if (b == 0) return a;
	return gcd(b, a % b);
}

void dfs(int u, int fa)
{
	for (int v : tree[u]) {
		if (v == fa) continue;//���߻�ͷ·
		dfs(v, u);
	}
	//��u����������gcdֵ�͸����洢����
	gcds[u].push_back((p[u] << 17) + 1);//�������ķ��ٶ�(gcd(p[u],p[u])=p[u])
	ans = (ans + p[u]) % mod;
	//����u���ӽڵ�(ֱ�Ӻ��),�����µ�gcdֵ�͸���
	for (int v : tree[u]) {
		if (v == fa) continue;
		int sz = gcds[v].size();
		for (int i = 0; i < sz; ++i) {
			ull g = gcd(p[u], gcds[v][i] >> 17);//�����µ�gcdֵ
			ull cnt = gcds[v][i] & 0x1ffff;//�����gcdֵ�ĸ���
			ans = (ans + g * cnt % mod) % mod;
			//���µ�gcdֵ�͸����洢����
			//��gcds[u]�в����Ƿ��Ѿ����ڸ�gcdֵ
			int j = 0, u_sz = gcds[u].size();
			for (; j < u_sz; ++j) {
				if (gcds[u][j] >> 17 == g) {
					gcds[u][j] += cnt;//���¸���
					break;
				}
			}
			if (j == u_sz) gcds[u].push_back((g << 17) + cnt);//����µ�gcdֵ�͸���
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	p.resize(n + 1);
	tree.resize(n + 1);
	gcds.resize(n + 1);
	for (int i = 1; i <= n; ++i) cin >> p[i];
	int u, v;
	for (int i = 1; i < n; ++i) {
		cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	dfs(1, 0);
	cout << ans;
	return 0;
}