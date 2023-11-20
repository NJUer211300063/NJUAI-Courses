# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans(numRows);
        for(int i = 0; i < numRows; i++){
            vector<int> tmp(i+1);
            tmp[0] = 1;
            tmp[i] = 1;
            for(int j = 1; j < i; j++){
                tmp[j] = ans[i-1][j-1] + ans[i-1][j];
            }
            ans[i] = tmp;
        }
        return ans;
    }
    
};

int main(){
    Solution a;
    vector<vector<int>> ans = a.generate(5);
    for(int i = 0; i < ans.size(); i++){
        for(int j = 0; j < ans[0].size(); j++)
             cout << ans[i][j] <<" ";
        cout << endl;
    }
}