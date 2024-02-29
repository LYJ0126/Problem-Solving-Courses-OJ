#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

int n, a[200008], b[200008];
long long ans = 0;
void merge(int l, int mid, int r)//�ϲ�
{
	int i = l, j = mid + 1, k = l;//i��¼����������λ�ã�j��¼�Ұ���������λ��
	while (i <= mid && j <= r) {//���ұȽϺϲ�
		if (a[i] <= a[j]) {
			b[k] = a[i];
			i++;
			k++;
		}
		else {
			ans += (mid - i + 1);
			b[k] = a[j];
			j++;
			k++;
		}
	}
	//��ʣ�µ����ϲ�����һ����Ѿ�����
	while (i <= mid) {
		b[k] = a[i];
		k++;
		i++;
	}
	while (j <= r) {
		b[k] = a[j];
		k++;
		j++;
	}
	//b���鸳ֵ��a
	for (int t = l; t <= r; t++) {
		a[t] = b[t];
	}
}
void mergesort(int l, int r)//�鲢����
{
	if (l < r) {
		int mid = (l + r) >> 1;//�м���
		mergesort(l, mid);
		mergesort(mid + 1, r);
		merge(l, mid, r);
	}
}
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	mergesort(1, n);
	cout << ans;
	return 0;
}