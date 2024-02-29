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
//子树对应的父节点在前序遍历中的位置，子树中节点在后序遍历中的起始位置,子树根节点在前序遍历中的位置
{
    if (poststart == postend) return;//到叶节点了
    int nxt_rootid_bound = rootid + postend - poststart;//子树根节点的的界限
    int nxt_rootid = rootid + 1;
    int nxt_poststart = poststart, nxt_postend = postend, size = 0;
    if (nxt_rootid <= nxt_rootid_bound) nxt_postend = mp[preorder[nxt_rootid]];
    while (nxt_rootid <= nxt_rootid_bound) {
        tree[preorder[rootid]].push_back(preorder[nxt_rootid]);//子树根节点是当前树根的子结点
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
    root = preorder[0];//前序遍历首节点或后序遍历尾节点即根节点
    for (int i = 0; i < n; ++i) {
        mp[postorder[i]] = i;//记录每个数在后序遍历中对应的下标
    }
    int root = preorder[0];//整棵树的根
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