#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

typedef unsigned int uint;
//此题较为特殊，mod=2^32，运算时溢出就是取模
//此题需要确定长边和短边，用vector存储，方便后续操作
uint n, m, K;
vector<vector<uint>>matrix;
vector<vector<uint>>sum;//存储二维前缀和
uint C[11][11];//组合数
//计算前缀和
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

//快速幂
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

//组合数
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
	//保证短边在前，长边在后
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
				cin >> matrix[j][i];//矩阵转置
			}
		}
	}
	prefix_sum();
	init_C();
	//枚举子矩阵在短边一侧的两个端点，剩下的相当于求1*long_edge上所有子矩阵和的K次方的和
	uint ans = 0;
	for (int a = 0; a <= short_edge; ++a) {
		for (int b = a + 1; b <= short_edge; ++b) {
			for (int k = 0; k <= K; ++k) {
				//经过转化后的求和式外层是k从0到K的循环,内层循环计算完后求出的答案乘(-1)^kC(K,k)再加到ans上
				uint temp = 0;
				vector<uint>sum_k_prefix(long_edge + 1, 0);//存储(a,b]*long_edge上子矩阵前缀和的k次方的前缀和
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