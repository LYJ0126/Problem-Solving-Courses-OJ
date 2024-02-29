#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include<cstdio>
using namespace std;
int ddian[10], zdian[10], zput[10], comment[10], z[4][4], d[4][4];
int zeliminate[4][4], deliminate[4][4], ztop[4], dtop[4], dian[7], sumz, sumd, place[9], flag = 0;
/*
ddian为开始dxy9步分别放的点数
zdian为z9步分别放的点数
zput为z每一步放的列
comment为dxy对每一步的评价
z,d为两方棋盘
zeliminate为z被消掉的点的位置
deliminate为dxy被消掉的点的位置
ztop,dtop分别是对应的列的点数+1（如z棋盘第一列已经放了两个骰子，则ztop[1]==3）
place表示复盘后dxy每一步放的列
*/
void dfs(int k, int q) {
    //算分
    if (k == 9) {
        sumz = 0;
        sumd = 0;
        for (int i = 1; i <= 3; i++) {
            memset(dian, 0, sizeof(dian));
            for (int j = 0; j < 3; j++) if (zeliminate[i][j] == 0) dian[z[i][j]]++;
            for (int j = 1; j <= 6; j++) sumz += j * dian[j] * dian[j];
        }
        for (int i = 1; i <= 3; i++) {
            memset(dian, 0, sizeof(dian));
            for (int j = 0; j < 3; j++) if (deliminate[i][j] == 0) dian[d[i][j]]++;
            for (int j = 1; j <= 6; j++) sumd += j * dian[j] * dian[j];
        }
        if (sumz < sumd) flag = 1;
        return;
    }
    //z先出手
    if (q == 1)
    {
        //z放置
        z[zput[k + 1]][ztop[zput[k + 1]]] = zdian[k + 1];
        ztop[zput[k + 1]]++;
        //d消除
        for (int i = 0; i < dtop[zput[k + 1]]; i++) {
            if (deliminate[zput[k + 1]][i] == 0 && d[zput[k + 1]][i] == zdian[k + 1]) deliminate[zput[k + 1]][i] = 1;
        }
        //d放置
        for (int i = 1; i <= 3; i++) {
            if (dtop[i] < 3 && ((comment[k + 1] == 0) || (comment[k + 1] < 0 && i != -comment[k + 1]) || (comment[k + 1] > 0 && i == comment[k + 1]))) {
                place[k] = i;
                d[i][dtop[i]] = ddian[k + 1];
                dtop[i]++;
                //z消除
                for (int j = 0; j < ztop[i]; j++) {
                    if (zeliminate[i][j] == 0 && z[i][j] == ddian[k + 1]) zeliminate[i][j] = 1;
                }
                dfs(k + 1, 1 - q);
                if (flag == 1) return;
                //回溯
                for (int j = 0; j < ztop[i]; j++) {
                    if (zeliminate[i][j] == 1) {
                        z[i][j] = ddian[k + 1];
                        zeliminate[i][j] = 0;
                    }
                }
                place[k] = 0;
                dtop[i]--;
                d[i][dtop[i]] = 0;
            }
        }
        for (int i = 0; i < dtop[zput[k + 1]]; i++) {
            if (deliminate[zput[k + 1]][i] == 1) {
                d[zput[k + 1]][i] = zdian[k + 1];
                deliminate[zput[k + 1]][i] = 0;
            }
        }
        ztop[zput[k + 1]]--;
        z[zput[k + 1]][ztop[zput[k + 1]]] = 0;
    }
    //dxy先出手
    else if (q == 0)
    {
        //d放置
        for (int i = 1; i <= 3; i++) {
            if (dtop[i] < 3 && ((comment[k + 1] == 0) || (comment[k + 1] < 0 && i != -comment[k + 1]) || (comment[k + 1] > 0 && i == comment[k + 1]))) {
                place[k] = i;
                d[i][dtop[i]] = ddian[k + 1];
                dtop[i]++;
                //z消除
                for (int j = 0; j < ztop[i]; j++) {
                    if (zeliminate[i][j] == 0 && z[i][j] == ddian[k + 1]) zeliminate[i][j] = 1;
                }
                //z放置
                z[zput[k + 1]][ztop[zput[k + 1]]] = zdian[k + 1];
                ztop[zput[k + 1]]++;
                //d消除
                for (int s = 0; s < dtop[zput[k + 1]]; s++) {
                    if (deliminate[zput[k + 1]][s] == 0 && d[zput[k + 1]][s] == zdian[k + 1]) deliminate[zput[k + 1]][s] = 1;
                }
                dfs(k + 1, 1 - q);
                if (flag == 1) return;
                //回溯
                for (int s = 0; s < dtop[zput[k + 1]]; s++) {
                    if (deliminate[zput[k + 1]][s] == 1) {
                        d[zput[k + 1]][s] = zdian[k + 1];
                        deliminate[zput[k + 1]][s] = 0;
                    }
                }
                ztop[zput[k + 1]]--;
                z[zput[k + 1]][ztop[zput[k + 1]]] = 0;
                for (int j = 0; j < ztop[i]; j++) {
                    if (zeliminate[i][j] == 1) {
                        z[i][j] = ddian[k + 1];
                        zeliminate[i][j] = 0;
                    }
                }
                place[k] = 0;
                dtop[i]--;
                d[i][dtop[i]] = 0;
            }
        }
    }
}

int main() {
    for (int i = 1; i < 10; i++) cin >> ddian[i];
    for (int i = 1; i < 10; i++) cin >> zdian[i];
    for (int i = 1; i < 10; i++) cin >> zput[i];
    for (int i = 1; i < 10; i++) cin >> comment[i];
    dfs(0, 1);
    if (flag == 0) cout << "No" << endl;
    else {
        cout << "Yes" << endl;
        for (int i = 0; i < 9; i++) cout << place[i] << " \n"[i == 8];
    }
    return 0;
}