#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

typedef unsigned int uint;
//�����Ϊ���⣬mod=2^32������ʱ�������ȡģ
//������Ҫȷ�����ߺͶ̱ߣ���vector�洢�������������
uint n, m, K;
vector<vector<uint>>matrix;
vector<vector<uint>>sum;//�洢��άǰ׺��
uint C[11][11];//�����
//����ǰ׺��
void prefix_sum()
{
	int short_edge = matrix.size();
	int long_edge = matrix[0].size();
	for (int i = 1; i < short_edge; ++i)
	{
		for (int j = 1; j < long_edge; ++j)
		{
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + matrix[i][j];
		}
	}
}

//������
inline uint quick_pow(uint a, uint b)
{
	uint res = 1;
	while (b)
	{
		if (b & 1)
		{
			res = res * a;
		}
		a = a * a;
		b >>= 1;
	}
	return res;
}

//�����
void init_C()
{
	for (int i = 0; i <= 10; ++i)
	{
		C[i][0] = 1;
	}
	for (int i = 1; i <= 10; ++i)
	{
		for (int j = 1; j <= i; ++j)
		{
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> K;
	uint long_edge = max(n, m);
	uint short_edge = min(n, m);
	matrix.resize(short_edge + 1, vector<uint>(long_edge + 1, 0));
	sum.resize(short_edge + 1, vector<uint>(long_edge + 1, 0));
	//��֤�̱���ǰ�������ں�
	if (n == short_edge)
	{
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				cin >> matrix[i][j];
			}
		}
	}
	else
	{
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j)
			{
				cin >> matrix[j][i];//����ת��
			}
		}
	}
	prefix_sum();
	init_C();
	//ö���Ӿ����ڶ̱�һ��������˵㣬ʣ�µ��൱����1*long_edge�������Ӿ���͵�K�η��ĺ�
	uint ans = 0;
	for (int a = 0; a <= short_edge; ++a) {
		for (int b = a + 1; b <= short_edge; ++b) {
			for (int k = 0; k <= K; ++k) {
				//����ת��������ʽ�����k��0��K��ѭ��,�ڲ�ѭ�������������Ĵ𰸳�(-1)^kC(K,k)�ټӵ�ans��
				uint temp = 0;
				vector<uint>sum_k_prefix(long_edge + 1, 0);//�洢(a,b]*long_edge���Ӿ���ǰ׺�͵�k�η���ǰ׺��
				for (int i = 1; i <= long_edge; ++i) {
					sum_k_prefix[i] = sum_k_prefix[i - 1] + quick_pow(sum[b][i] - sum[a][i], k);
				}
				for (int i = 0; i <= long_edge; ++i) {
					uint temp2 = quick_pow(sum[b][i] - sum[a][i], K - k) * (sum_k_prefix[long_edge] - sum_k_prefix[i]) * C[K][k];
					if ((K - k) & 1) temp -= temp2;
					else temp += temp2;
				}
				ans += temp;
			}
		}
	}
	cout << ans;
	return 0;
}