#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<unordered_map>
#include<cstring>
using namespace std;

int n, x, root;
vector<int>preorder;
vector<int>postorder;
vector<vector<int>>tree;
unordered_map<int, int>mp;
stack<int>st;

void build(int poststart, int postend, int rootid)
//������Ӧ�ĸ��ڵ���ǰ������е�λ�ã������нڵ��ں�������е���ʼλ��,�������ڵ���ǰ������е�λ��
{
    if (poststart == postend) return;//��Ҷ�ڵ���
    int nxt_rootid_bound = rootid + postend - poststart;//�������ڵ�ĵĽ���
    int nxt_rootid = rootid + 1;
    int nxt_poststart = poststart, nxt_postend = postend, size = 0;
    if (nxt_rootid <= nxt_rootid_bound) nxt_postend = mp[preorder[nxt_rootid]];
    while (nxt_rootid <= nxt_rootid_bound) {
        tree[preorder[rootid]].push_back(preorder[nxt_rootid]);//�������ڵ��ǵ�ǰ�������ӽ��
        build(nxt_poststart, nxt_postend, nxt_rootid);
        nxt_rootid += (nxt_postend - nxt_poststart + 1);
        nxt_poststart = nxt_postend + 1;
        if (nxt_rootid <= nxt_rootid_bound) nxt_postend = mp[preorder[nxt_rootid]];
    }

}
void bfsprint(int root)
{
    queue<int>que;
    que.push(root);
    //cout << root << ' ';
    while (!que.empty()) {//bfs
        int size = que.size();
        for (int i = 0; i < size; ++i) {
            int u = que.front();
            que.pop();
            for (int v : tree[u]) que.push(v);
            if (i == size - 1) cout << u << ' ';
        }
    }
}
int main()
{
    cin >> n;
    preorder.resize(n);
    postorder.resize(n);
    tree.resize(n + 1);
    for (int i = 0; i < n; ++i) cin >> preorder[i];
    for (int i = 0; i < n; ++i) cin >> postorder[i];
    root = preorder[0];//ǰ������׽ڵ��������β�ڵ㼴���ڵ�
    for (int i = 0; i < n; ++i) {
        mp[postorder[i]] = i;//��¼ÿ�����ں�������ж�Ӧ���±�
    }
    int root = preorder[0];//�������ĸ�
    build(0, n - 1, 0);
    bfsprint(root);
    return 0;
}

/*
input:
6
1 2 3 4 5 6
3 4 5 2 6 1
output:
1 6 5
*/