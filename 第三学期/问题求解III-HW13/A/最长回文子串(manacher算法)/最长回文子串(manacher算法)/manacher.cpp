
//传统的动态规划算法，时间复杂度为O(n^2)，空间复杂度为O(n^2)，会超时
//这里使用manacher算法，时间复杂度为O(n)，空间复杂度为O(n)
#include<iostream>
#include<cstring>
using namespace std;

//manacher
/*int manacher(char* s)
{
    int len = strlen(s);
    char *str = new char[2 * len + 2];
    str[0] = '$';//防止越界
    str[1] = '#';//防止越界
    for (int i = 0; i < len; i++)//将字符串转换为奇数长度
    {
        str[2 * i + 2] = s[i];
        str[2 * i + 3] = '#';
    }
    int *p = new int[2 * len + 2];
    int mx = 0, id = 0, ans = 0;
    for (int i = 1; i < 2 * len + 2; i++)//计算p[i]
    {
        if (mx > i)//mx>i说明i在mx的右边，此时可以利用对称性
            p[i] = min(p[2 * id - i], mx - i);
        else
            p[i] = 1;//mx<=i说明i在mx的右边，此时只能一个一个匹配
        while (str[i + p[i]] == str[i - p[i]])//匹配
            p[i]++;
        if (mx < i + p[i])//更新mx和id
        {
            mx = i + p[i];//mx为最右边的位置
            id = i;//id为最右边的位置的中心
        }
        ans = max(ans, p[i] - 1);//更新答案
    }
    delete[] str;
    delete[] p;
    return ans;
}*/
int manacher(char* str)
{
    if (str == NULL) return 0;//空串
    int len = strlen(str) * 2 + 1;//插入特殊字符后的长度
    char* temps = new char[len];//插入特殊字符后的字符串
    int* p = new int[len];//p[i]表示以i为中心的最长回文子串的半径
    int r, c, index, mx;//r为最右边的位置，c为最右边的位置的中心，index为当前位置，mx为最长回文子串的半径
    r = c = -1;//初始化
    index = mx = 0;//初始化
    for (int i = 0; i < len; ++i) temps[i] = i & 1 ? str[index++] : '$';//插入特殊字符,奇数位置为原字符串，偶数位置为特殊字符
    for (int i = 0; i < len; ++i) {//计算p[i]
        p[i] = r > i ? min(r - i, p[2 * c - i]) : 1;//初始化p[i]
        while (i + p[i] < len && i - p[i] >= 0) {//匹配
            if (temps[i + p[i]] == temps[i - p[i]]) ++p[i];//匹配成功则继续匹配
            else break;//匹配失败则退出
        }
        if (i + p[i] > r) {//更新r和c
            r = i + p[i];
            c = i;
        }
        mx = max(mx, p[i]);//更新答案
    }
    delete[] temps;
    delete[] p;
    return mx - 1;//返回最长回文子串的长度
}
char s[100005];
int main()
{
    cin >> s;
    cout << manacher(s);
    return 0;
}
/*
input:
daabaac
output:
5
*/