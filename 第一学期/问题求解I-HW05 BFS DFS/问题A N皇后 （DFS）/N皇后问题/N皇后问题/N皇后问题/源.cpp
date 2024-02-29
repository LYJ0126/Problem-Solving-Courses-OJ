#include<iostream>
#include<cmath>
using namespace std;
int n;
int queenpos[100];
//�����õĻʺ�λ�ã����Ͻǣ�0,0��
void nqueen(int k)//��0��k-1�лʺ��Ѿ��ںõ�����£��ڵ�k�еĻʺ�
{
	int i;
	if (k == n)
	{
		for (i = 0; i < n; i++) {
			cout << queenpos[i] + 1 << ' ';
		}
		cout << endl;
		return;
	}
	for (i = 0; i < n; i++)//�𲽳��Ե�k���ʺ��λ��
	{
		int j;
		for (j = 0; j < k; j++)//���Ѿ��ںõ�k���ʺ��λ�ñȽϣ����Ƿ��ͻ
		{
			if (queenpos[j] == i || abs(queenpos[j] - i) == abs(k - j)) {
				break;//��ͻ������һ��λ��
			}
		}
		if (j == k) {
			queenpos[k] = i;
			nqueen(k + 1);
		}
	}
}
int main()
{
	cin >> n;
	nqueen(0);
	return 0;
}