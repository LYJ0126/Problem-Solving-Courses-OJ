#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

int n, m, x;
vector<vector<int>>graph1;//记录出度
vector<vector<int>>graph2;//记录入度
string op;
int main()
{
	cin >> n >> m;
	graph1.resize(m + 1);
	graph2.resize(m + 1);
	int pos = 0;
	bool jump = false;
	for (int i = 0; i < n; i++) {
		cin >> op;
		if (op == "BEGIN") {
			cin >> x;
			pos = x;
		}
		else if (op == "LABEL") {
			cin >> x;
			if (!jump) {
				graph1[pos].push_back(x);
				graph2[x].push_back(pos);
			}
			pos = x;
			jump = false;
		}
		else if (op == "GOTO") {
			cin >> x;
			graph1[pos].push_back(x);
			graph2[x].push_back(pos);
			jump = true;
			pos = x;
		}
		else if (op == "IF") {
			string tt;
			cin >> tt;
			cin >> tt;
			cin >> tt;
			cin >> tt;
			cin >> x;
			graph1[pos].push_back(x);
			graph2[x].push_back(pos);
		}
		else if (op == "END") {
			cin >> x;
			graph1[pos].push_back(x);
			graph2[x].push_back(pos);
		}
		else {
			char ss;
			cin >> ss;
		}
	}
	for (int i = 1; i <= m; i++) cout << graph2[i].size() << ' ';
	cout << endl;
	for (int i = 1; i <= m; i++) cout << graph1[i].size() << ' ';
	return 0;
}