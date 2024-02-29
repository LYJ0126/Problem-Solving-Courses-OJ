#include<iostream>
#include<cmath>
using namespace std;
int n, a[9];
char board[10][10];
int placed[2][10], unplaced[10], tu[10][10];
int y = 0, t = 0, x = 0;
int check1(int k)
{
	int s = 0;
	for (int j = 0; j < n; j++)
	{
		if (tu[k][j] == 1) s++;
	}
	return s;
}
bool check2(int t)
{
	for (int i = 0; i < t; i++)
	{
		if (check1(placed[0][i]) > 1)
		{
			return false;
		}
	}
	return true;
}
bool queen1(int k)
{
	for (int i = 1; i < k; i++)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if ((placed[1][j] == placed[1][i]) || (abs(placed[0][j] - placed[0][i]) == abs(placed[1][i] - placed[1][j])))
			{
				return false;
			}
		}
	}
	return true;
}
void queen2(int k)
{
	int i;
	if (k == t && x < 1) {
		x++;
		cout << "Yes" << endl;
		for (int u = 0; u < n; u++) {
			for (int j = 0; j < n; j++) {
				if (tu[u][j] == 0) {
					cout << '.';
				}
				else cout << 'Q';
			}
			cout << endl;
		}
		return;
	}
	for (i = 0; i < n; i++)
	{
		int j;
		for (j = 0; j < y; j++)
		{
			if ((placed[1][j] == i) || (abs(placed[0][j] - unplaced[k]) == abs(placed[1][j] - i)))
			{
				break;
			}
		}
		if (j == y) {
			placed[0][y] = unplaced[k];
			placed[1][y] = i;
			tu[unplaced[k]][i] = 1;
			y++;
			queen2(k + 1);
			y--;
			tu[unplaced[k]][i] = 0;
		}
	}
}

int main()
{

	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			cin >> board[i][j];
			if (board[i][j] == 'Q')
			{
				tu[i][j] = 1;
				placed[0][y] = i;
				placed[1][y] = j;
				y++;
			}
			else {
				tu[i][j] = 0;
			}
		}
	for (int j = 0; j < y; j++)
	{
		a[placed[0][j]]++;
	}
	for (int i = 0; i < n; i++)
	{
		if (a[i] == 0)
		{
			unplaced[t] = i;
			t++;
		}
	}
	if (check2(y) && queen1(y))
	{
		queen2(0);
	}
	else {
		cout << "No" << endl;
		return 0;
	}
	if (x == 0)
	{
		cout << "No" << endl;
	}
	return 0;
}