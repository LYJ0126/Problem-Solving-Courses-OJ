#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

int k, n;
int dp[105][10005];//dp[i][j]表示i个鸡蛋，j层楼时，至少要仍dp[i][j]次才能确定f
int main()
{
	cin >> k >> n;
    //初始化
    // 当楼层数为一时
    for (int i = 1; i <= k; i++) {
        dp[i][1] = 1;
    }
    // 当鸡蛋只有一颗时
    for (int i = 1; i <= n; i++) {
        dp[1][i] = i;
    }
    //dp[i][j]=min(1<=x<=n){max{dp[i-1][x-1],dp[i][n-x]}}+1，别忘了加一
    for (int i = 2; i <= k; i++) {
        for (int j = 2; j <= n; j++) {

            // 未使用二分的解法 x为所选楼层
            // int minimum = Integer.MAX_VALUE;
            // for(int x=1; x<=j; x++){
            //     minimum = min(minimum, max(dp[i-1][x-1], dp[i][j-x]));
            // }
           //dp[i][j] = 1 + minimum;
            // 二分查找
            int left = 1;
            int right = j;
            while (right-left>1) {
                int mid = (left + right) / 2; // 在mid层扔鸡蛋
                int f1 = dp[i - 1][mid - 1]; // 鸡蛋碎了，对应单调递增的函数f1=dp[i-1][x-1]
                int f2 = dp[i][j - mid]; // 鸡蛋没碎，对应单调递减的函数f2=dp[i][j-x]
                if (f1 > f2) { // 交点应该在mid左边
                    right = mid;
                }
                else if (f1 < f2) { // 交点应该在mid右边
                    left = mid;
                }
                else { // 当f1==f2表示恰好找到交点
                    left = right = mid;
                }
            }
            // 范围缩小到 right - left <= 1
            int leftval = max(dp[i - 1][left - 1], dp[i][j - left]);
            int rightval = max(dp[i - 1][right - 1], dp[i][j - right]);
            dp[i][j] = 1 + min(leftval, rightval);
        }
    }
    cout << dp[k][n];
    return 0;
}