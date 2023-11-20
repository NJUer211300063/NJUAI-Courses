#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    void flatten(TreeNode* root) {
        stack<TreeNode*> stk;
        if(root!=nullptr) stk.push(root);
        while(!stk.empty()){
            TreeNode* tmp=stk.top();
            stk.pop();
            if(tmp->right!=nullptr) stk.push(tmp->right);
            if(tmp->left!=nullptr) stk.push(tmp->left);
            tmp->left=nullptr;
            tmp->right=stk.top();
        }

        
    }
};

int main(){

}