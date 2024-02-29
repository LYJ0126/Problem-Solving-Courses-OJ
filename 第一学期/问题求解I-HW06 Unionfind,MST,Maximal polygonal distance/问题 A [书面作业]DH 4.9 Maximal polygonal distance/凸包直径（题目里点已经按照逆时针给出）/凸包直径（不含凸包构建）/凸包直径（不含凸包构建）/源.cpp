#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
int n, zero = 0;
ll maximum = -1;
//点
struct point {
	ll x, y;
}a[100010];
//三角形面积
ll S(point m, point n, point r)
{
	return abs(m.x * n.y + n.x * r.y + r.x * m.y - m.x * r.y - n.x * m.y - r.x * n.y);
}
//距离
ll dis(point m, point n)
{
	return (m.x - n.x) * (m.x - n.x) + (m.y - n.y) * (m.y - n.y);
}
int main()
{
	cin >> n;
	//注意从0开始，因为后面有k%n和（k+1）%n
	for (int i = 0; i < n; i++)
	{
		cin >> a[i].x >> a[i].y;
	}
	if (n == 1) cout << zero;
	else if (n == 2) cout << dis(a[0], a[1]);
	else {
		ll k = 2;
		for (int i = 0; i < n; i++) {
			//旋转卡壳
			while (true) {
				if (i < n - 1) {
					if (S(a[i], a[i + 1], a[k % n]) > S(a[i], a[i + 1], a[(k + 1) % n])) {
						maximum = max(maximum, max(dis(a[i], a[k % n]), dis(a[i + 1], a[k % n])));
						break;
					}
					else if (S(a[i], a[i + 1], a[k % n]) == S(a[i], a[i + 1], a[(k + 1) % n])) {
						ll m1 = max(dis(a[i], a[k % n]), dis(a[i + 1], a[k % n]));
						ll m2 = max(dis(a[i], a[(k + 1) % n]), dis(a[i + 1], a[(k + 1) % n]));
						maximum = max(maximum, max(m1, m2));
						k++;
						break;
					}
					else {
						k++;
					}
				}
				if (i == n - 1) {
					if (S(a[i], a[0], a[k % n]) > S(a[i], a[0], a[(k + 1) % n])) {
						maximum = max(maximum, max(dis(a[i], a[k % n]), dis(a[1], a[k % n])));
						break;
					}
					else if (S(a[i], a[0], a[k % n]) == S(a[i], a[0], a[(k + 1) % n])) {
						ll m1 = max(dis(a[i], a[k % n]), dis(a[0], a[k % n]));
						ll m2 = max(dis(a[i], a[(k + 1) % n]), dis(a[0], a[(k + 1) % n]));
						maximum = max(maximum, max(m1, m2));
						k++;
						break;
					}
					else {
						k++;
					}
				}
			}
		}
		cout << maximum;
	}
	return 0;
}