#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;

int n;
string beginword, endword, s[20008];
int visited[20008];
/*bool check(string s1, string s2, int len) {
	int pos = -1;
	for (int i = 0; i < len; i++) {
		if (s1[i] != s2[i]) {
			pos = i;
			break;
		}
	}
	if (pos >= 0) {
		bool flag = true;
		for (int i = pos + 1; i < len; i++) {
			if (s1[i] != s2[i]) {
				flag = false;
				break;
			}
		}
		return flag;
	}
	return false;
}*/
int main()
{
	cin >> n;
	cin >> beginword >> endword;
	int endid = 0;
	int len = beginword.length();
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		if (s[i] == endword) endid = i;
	}
	s[0] = beginword;
	int step = 1;
	string cur = beginword;
	bool flag = false;
	queue<int>que;
	que.push(0);
	visited[0] = 1;
	while (!que.empty()) {
		step++;
		int size = que.size();
		while (size) {
			int u = que.front();
			que.pop();
			for (int j = 1; j <= n; j++) {
				if (!visited[j]) {
					int pos = 0;
					while (pos < len && s[u][pos] == s[j][pos]) pos++;
					if (pos == len) continue;
					bool tempflag = true;
					for (int k = pos + 1; k < len; k++) {
						if (s[u][k] != s[j][k]) {
							tempflag = false;
							break;
						}
					}
					if (tempflag) {
						if (j == endid) {
							flag = true;
							break;
						}
						que.push(j);
						visited[j] = 1;
					}
					/*if (check(s[u], s[j], len)) {
						if (j == endid) {
							flag = true;
							break;
						}
						que.push(j);
						visited[j] = 1;
					}*/
				}
			}
			if (flag) break;
			size--;
		}
		if (flag) break;
	}
	if (flag) cout << step;
	else cout << 0;
	return 0;
}