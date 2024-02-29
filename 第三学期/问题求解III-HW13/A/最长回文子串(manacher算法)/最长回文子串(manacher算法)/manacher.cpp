
//��ͳ�Ķ�̬�滮�㷨��ʱ�临�Ӷ�ΪO(n^2)���ռ临�Ӷ�ΪO(n^2)���ᳬʱ
//����ʹ��manacher�㷨��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(n)
#include<iostream>
#include<cstring>
using namespace std;

//manacher
/*int manacher(char* s)
{
    int len = strlen(s);
    char *str = new char[2 * len + 2];
    str[0] = '$';//��ֹԽ��
    str[1] = '#';//��ֹԽ��
    for (int i = 0; i < len; i++)//���ַ���ת��Ϊ��������
    {
        str[2 * i + 2] = s[i];
        str[2 * i + 3] = '#';
    }
    int *p = new int[2 * len + 2];
    int mx = 0, id = 0, ans = 0;
    for (int i = 1; i < 2 * len + 2; i++)//����p[i]
    {
        if (mx > i)//mx>i˵��i��mx���ұߣ���ʱ�������öԳ���
            p[i] = min(p[2 * id - i], mx - i);
        else
            p[i] = 1;//mx<=i˵��i��mx���ұߣ���ʱֻ��һ��һ��ƥ��
        while (str[i + p[i]] == str[i - p[i]])//ƥ��
            p[i]++;
        if (mx < i + p[i])//����mx��id
        {
            mx = i + p[i];//mxΪ���ұߵ�λ��
            id = i;//idΪ���ұߵ�λ�õ�����
        }
        ans = max(ans, p[i] - 1);//���´�
    }
    delete[] str;
    delete[] p;
    return ans;
}*/
int manacher(char* str)
{
    if (str == NULL) return 0;//�մ�
    int len = strlen(str) * 2 + 1;//���������ַ���ĳ���
    char* temps = new char[len];//���������ַ�����ַ���
    int* p = new int[len];//p[i]��ʾ��iΪ���ĵ�������Ӵ��İ뾶
    int r, c, index, mx;//rΪ���ұߵ�λ�ã�cΪ���ұߵ�λ�õ����ģ�indexΪ��ǰλ�ã�mxΪ������Ӵ��İ뾶
    r = c = -1;//��ʼ��
    index = mx = 0;//��ʼ��
    for (int i = 0; i < len; ++i) temps[i] = i & 1 ? str[index++] : '$';//���������ַ�,����λ��Ϊԭ�ַ�����ż��λ��Ϊ�����ַ�
    for (int i = 0; i < len; ++i) {//����p[i]
        p[i] = r > i ? min(r - i, p[2 * c - i]) : 1;//��ʼ��p[i]
        while (i + p[i] < len && i - p[i] >= 0) {//ƥ��
            if (temps[i + p[i]] == temps[i - p[i]]) ++p[i];//ƥ��ɹ������ƥ��
            else break;//ƥ��ʧ�����˳�
        }
        if (i + p[i] > r) {//����r��c
            r = i + p[i];
            c = i;
        }
        mx = max(mx, p[i]);//���´�
    }
    delete[] temps;
    delete[] p;
    return mx - 1;//����������Ӵ��ĳ���
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