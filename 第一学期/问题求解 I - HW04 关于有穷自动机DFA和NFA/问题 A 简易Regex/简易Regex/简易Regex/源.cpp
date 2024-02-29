#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

int first_edge[1000], to[1000], nedge[1000];
char charonedge[1000];
char s1[200], s2[200];

int t = 0;
void insert(int x, int y, char ch) {
	t++;
	charonedge[t] = ch;
	to[t] = y;
	nedge[t] = first_edge[x];
	first_edge[x] = t;
}

int i = 0;
int dot = 1;
void init()
{
	while (i < strlen(s1))
	{
		if (((s1[i] != '?') && (s1[i] != '*') && (s1[i] != '+') && (s1[i] != '[') && (s1[i] != '.')) && ((s1[i + 1] != '?') && (s1[i + 1] != '*') && (s1[i + 1] != '+')))
		{
			insert(dot, dot + 1, s1[i]);
			dot++;
			i++;
		}
		else if ((s1[i + 1] == '?') && (s1[i] != ']'))
		{
			insert(dot, dot + 1, '$');
			insert(dot, dot + 1, s1[i]);
			dot++;
			i += 2;
		}
		else if ((s1[i] == '?') && (s1[i - 1] == ']'))
		{
			insert(dot - 1, dot, '$');
			i++;
		}
		else if ((s1[i + 1] == '*') && (s1[i] != ']'))
		{
			insert(dot, dot, s1[i]);
			i += 2;
		}
		else if ((s1[i + 1] == '+') && (s1[i] != ']'))
		{
			insert(dot, dot + 1, s1[i]);
			insert(dot + 1, dot + 1, s1[i]);
			dot++;
			i += 2;
		}
		else if ((s1[i] == '+') && (s1[i - 1] == ']'))
		{
			int n;
			for (int j = i - 1; s1[j] != '['; j--)
			{
				n = j;
			}
			for (int s = n; s <= i - 2; s++)
			{
				insert(dot, dot, s1[s]);
			}
			i++;
		}
		else if (s1[i] == '[')
		{
			int k;
			for (int j = i; s1[j] != ']'; j++)
			{
				k = j;
			}
			if (s1[k + 2] == '*')
			{
				for (int s = i + 1; s <= k; s++)
				{
					insert(dot, dot, s1[s]);
				}
				i = k + 3;
			}
			else {
				for (int s = i + 1; s <= k; s++)
				{
					insert(dot, dot + 1, s1[s]);
				}
				dot++;
				i = k + 2;
			}
		}
		else if (s1[i] == '.')
		{
			insert(dot, dot + 1, '.');
			dot++;
			i++;
		}
	}
	return;
}


bool sch(int point, int pos)
{
	if (pos == strlen(s2) && point == dot)
	{
		return true;
	}
	bool tt = false;
	for (int z = first_edge[point]; z != 0; z = nedge[z])
	{
		if (charonedge[z] == s2[pos] || charonedge[z] == '.')
		{
			tt = tt || sch(to[z], pos + 1);
		}
		else if (charonedge[z] == '$')
			tt = tt || sch(to[z], pos);
	}
	return tt;
}

int main()
{
	scanf("%s", &s1);
	scanf("%s", &s2);
	init();
	if (sch(1, 0)) cout << "Yes";
	else cout << "No";
	return 0;
}