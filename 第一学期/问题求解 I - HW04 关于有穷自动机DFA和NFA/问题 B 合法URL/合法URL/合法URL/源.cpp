#include<iostream>
#include<cstring>
#include<algorithm>
#include<ctype.h>
using namespace std;

int first_edge[1000], to[1000], nedge[1000];
char charonedge[1000];
char s[300];
int l;

int t = 0;
void insert(int x, int y, char ch) {
	t++;
	charonedge[t] = ch;
	to[t] = y;
	nedge[t] = first_edge[x];
	first_edge[x] = t;
}

bool sch(int point, int pos)
{
	if (pos == l && point == 17)
	{
		return true;
	}
	bool tt = false;
	for (int z = first_edge[point]; z != 0; z = nedge[z])
	{
		if (charonedge[z] == s[pos] || (charonedge[z] == '*' && isalpha(s[pos])) || (charonedge[z] == '$' && isdigit(s[pos])))
		{
			tt = tt || sch(to[z], pos + 1);
		}
		else if (charonedge[z] == '%')
			tt = tt || sch(to[z], pos);
	}
	return tt;
}
int main()
{
	insert(0, 1, '*');
	insert(0, 4, '%');
	insert(1, 1, '*');
	insert(1, 2, ':');
	insert(2, 3, '/');
	insert(3, 4, '/');
	insert(4, 5, '*');
	insert(4, 5, '$');
	insert(5, 4, '.');
	insert(5, 5, '*');
	insert(5, 5, '$');
	insert(5, 6, ':');
	insert(5, 8, '%');
	insert(5, 10, '?');
	insert(5, 14, '%');
	insert(5, 17, '%');
	insert(6, 7, '$');
	insert(7, 7, '$');
	insert(7, 8, '%');
	insert(8, 9, '/');
	insert(8, 10, '?');
	insert(8, 14, '%');
	insert(8, 17, '%');
	insert(9, 9, '*');
	insert(9, 9, '$');
	insert(9, 8, '%');
	insert(9, 10, '?');
	insert(9, 14, '%');
	insert(9, 17, '%');
	insert(10, 11, '*');
	insert(10, 11, '$');
	insert(11, 11, '*');
	insert(11, 11, '$');
	insert(11, 12, '=');
	insert(11, 13, '%');
	insert(12, 13, '*');
	insert(12, 13, '$');
	insert(13, 13, '*');
	insert(13, 13, '$');
	insert(13, 14, '%');
	insert(13, 10, '&');
	insert(14, 15, '#');
	insert(14, 17, '%');
	insert(15, 16, '*');
	insert(15, 16, '$');
	insert(16, 16, '*');
	insert(16, 16, '$');
	insert(16, 17, '%');

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		cin >> l;
		for (int j = 0; j < l; j++) {
			cin >> s[j];
		}
		if (sch(0, 0)) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}