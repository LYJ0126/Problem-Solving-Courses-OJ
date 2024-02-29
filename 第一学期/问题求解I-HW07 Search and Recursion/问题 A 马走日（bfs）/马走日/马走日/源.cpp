#include<iostream>
#include<cmath>
#include<algorithm>

using namespace std;
int n, m, x, y;
int board[503][503], book[503][503];
int ne[8][2] = { {-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1} };
int head, tail, i, j, k, nx, ny;
//∂”¡–
struct point
{
    int x;
    int y;
    int s;
}queue[250005];
int main()
{
    cin >> n >> m >> x >> y;
    head = 1, tail = 1;
    queue[tail].x = x;
    queue[tail].y = y;
    queue[tail].s = 0;
    tail++;
    book[x][y] = 1;
    //π„À—
    while (head < tail)
    {
        for (k = 0; k <= 7; k++)
        {
            nx = queue[head].x + ne[k][0];
            ny = queue[head].y + ne[k][1];
            if (nx<1 || nx>n || ny<1 || ny>m || book[nx][ny] == 1)
                continue;
            else
            {
                book[nx][ny] = 1;
                queue[tail].x = nx;
                queue[tail].y = ny;
                queue[tail].s = queue[head].s + 1;
                board[nx][ny] = queue[tail].s;
                tail++;
            }
        }
        head++;
    }
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
        {
            if (board[i][j] == 0 && !(i == x && j == y))
                board[i][j] = -1;
        }
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
        {
            cout << board[i][j] << " \n"[j == m];
        }
    return 0;
}