#include <iostream>
#include <vector>
using namespace std;


int buildTree(int tree[][2], int pre_order[], int in_order[], int pre_l, int pre_r, int in_l, int in_r) {
    if (pre_l > pre_r)
        return -1;
    int root = pre_order[pre_l];
    int root_index_in = -1;
    for (int i = in_l; i <= in_r; i++) {
        if (in_order[i] == root) {
            root_index_in = i;
            break;
        }
    }
    int left_subtree_len = root_index_in - in_l;
    int right_subtree_len = in_r - root_index_in;
    tree[root-1][0] = buildTree(tree, pre_order, in_order, pre_l+1, pre_l+left_subtree_len, in_l, root_index_in-1);
    tree[root-1][1] = buildTree(tree, pre_order, in_order, pre_l+left_subtree_len+1 , pre_r, root_index_in+1, in_r);
    return root;
}


int main() {
    int n;
    cin >> n;
    int tree[n][2];
    for (int i = 0; i < n; i++) {
        tree[i][0] = -1;
        tree[i][1] = -1;
    }
    int pre_order[n], in_order[n];
    for (int i = 0; i < n; i++) {
        cin >> in_order[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> pre_order[i];
    }
    buildTree(tree, pre_order, in_order, 0, n-1, 0, n-1);
    for (int i = 0; i < n; i++) {
        cout << tree[i][0] << ' ' << tree[i][1] << endl;
    }
}