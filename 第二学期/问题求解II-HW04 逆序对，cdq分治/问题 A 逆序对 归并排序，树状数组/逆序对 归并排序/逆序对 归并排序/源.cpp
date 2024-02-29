#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

int n, a[200008], b[200008];
long long ans = 0;
void merge(int l, int mid, int r)//合并
{
	int i = l, j = mid + 1, k = l;//i记录左半边最靠左的数位置，j记录右半边最靠左是数位置
	while (i <= mid && j <= r) {//左右比较合并
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
	//对剩下的数合并，有一半边已经空了
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
	//b数组赋值给a
	for (int t = l; t <= r; t++) {
		a[t] = b[t];
	}
}
void mergesort(int l, int r)//归并排序
{
	if (l < r) {
		int mid = (l + r) >> 1;//中间数
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