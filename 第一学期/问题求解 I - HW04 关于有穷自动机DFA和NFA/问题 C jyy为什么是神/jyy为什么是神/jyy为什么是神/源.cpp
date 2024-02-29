#include<iostream>
using namespace std;

char a[1000008];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    long long int j = 0, jy = 0, jyy = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == 'j')
        {
            j++;
        }
        if (a[i] == 'y')
        {
            long long int t = jy;
            jy = jy + j;
            jyy = jyy + t;
        }
        if (jyy >= 998244353)
        {
            jyy = jyy % 998244353;
        }
    }
    cout << jyy << endl;
    return 0;
}