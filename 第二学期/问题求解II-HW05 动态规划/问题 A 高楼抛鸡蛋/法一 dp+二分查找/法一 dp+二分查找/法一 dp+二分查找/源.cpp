#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

int k, n;
int dp[105][10005];//dp[i][j]��ʾi��������j��¥ʱ������Ҫ��dp[i][j]�β���ȷ��f
int main()
{
	cin >> k >> n;
    //��ʼ��
    // ��¥����Ϊһʱ
    for (int i = 1; i <= k; i++) {
        dp[i][1] = 1;
    }
    // ������ֻ��һ��ʱ
    for (int i = 1; i <= n; i++) {
        dp[1][i] = i;
    }
    //dp[i][j]=min(1<=x<=n){max{dp[i-1][x-1],dp[i][n-x]}}+1�������˼�һ
    for (int i = 2; i <= k; i++) {
        for (int j = 2; j <= n; j++) {

            // δʹ�ö��ֵĽⷨ xΪ��ѡ¥��
            // int minimum = Integer.MAX_VALUE;
            // for(int x=1; x<=j; x++){
            //     minimum = min(minimum, max(dp[i-1][x-1], dp[i][j-x]));
            // }
           //dp[i][j] = 1 + minimum;
            // ���ֲ���
            int left = 1;
            int right = j;
            while (right-left>1) {
                int mid = (left + right) / 2; // ��mid���Ӽ���
                int f1 = dp[i - 1][mid - 1]; // �������ˣ���Ӧ���������ĺ���f1=dp[i-1][x-1]
                int f2 = dp[i][j - mid]; // ����û�飬��Ӧ�����ݼ��ĺ���f2=dp[i][j-x]
                if (f1 > f2) { // ����Ӧ����mid���
                    right = mid;
                }
                else if (f1 < f2) { // ����Ӧ����mid�ұ�
                    left = mid;
                }
                else { // ��f1==f2��ʾǡ���ҵ�����
                    left = right = mid;
                }
            }
            // ��Χ��С�� right - left <= 1
            int leftval = max(dp[i - 1][left - 1], dp[i][j - left]);
            int rightval = max(dp[i - 1][right - 1], dp[i][j - right]);
            dp[i][j] = 1 + min(leftval, rightval);
        }
    }
    cout << dp[k][n];
    return 0;
}