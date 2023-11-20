#include <iostream>
#include <vector>
#include <queue>
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
    void getchild(TreeNode* now, queue<TreeNode*> &ls){
        if(now->left!=nullptr)
            ls.push(now->left);
        if(now->right!=nullptr)
            ls.push(now->right);
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> sentry;
        vector<vector<int>> ans;
        if(root!=nullptr)
            sentry.push(root);
    
        while(!sentry.empty()){
            int i=sentry.size();
            vector<int> bss;
            for(int j=0; j<i; j++){
                TreeNode* temp= sentry.front();
                bss.push_back(sentry.front()->val);
                sentry.pop();
                getchild(temp, sentry);
            }
            ans.push_back(bss);
            
        }
        return ans;
    }
};

int main(){

}