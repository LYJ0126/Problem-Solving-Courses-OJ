#include<iostream>
#include<algorithm>
#include<cstring>
#include<cctype>
using namespace std;

int len;
char s1[300005];
char s2[300005];
int  position = 0;

void f(int a, int b) {
    if (a >= b) {
        return;
    }
    if (s1[a] == '[' && s1[b - 1] == ']') {
        f(a + 1, b - 1);
        return;
    }
    int lbracket = 0, rbracket = 0, beg1 = a, end1 = b, beg2 = a, end2 = b;
    int num = 1;
    if (isdigit(s1[a])) {
        num = 0;
        for (int i = a; ; i++)
        {
            if (isdigit(s1[i])) {
                num = num * 10 + s1[i] - '0';
            }
            else {
                beg1 = i;
                break;
            }
        }
    }
    for (int t = beg1; t < b; t++) {
        if (lbracket == 0 && t == b - 1) {
            for (int j = 1; j <= num; j++) {
                for (int k = beg1; k < b; k++) {
                    s2[position++] = s1[k];
                }
            }
            break;
        }
        if (lbracket == 0 && s1[t] == '[') {
            end1 = t;
            beg2 = t;
        }
        if (s1[t] == '[') {
            lbracket++;
        }
        if (s1[t] == ']') {
            rbracket++;
        }
        if (lbracket != 0 && rbracket != 0 && lbracket == rbracket) {
            end2 = t + 1;//
            for (int j = 1; j <= num; j++) {
                f(beg1, end1);
                f(beg2, end2);
                f(end2, b);
            }
            break;
        }
    }
    return;
}

int main() {
    memset(s2, 0, sizeof(s2));
    cin >> s1;
    len = strlen(s1);
    f(0, len);
    for (int i = 0; i < position; i++)
    {
        cout << s2[i];
    }
    return 0;
}