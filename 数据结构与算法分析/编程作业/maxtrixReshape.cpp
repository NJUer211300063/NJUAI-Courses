# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        int m = mat.size();
        int n = mat[0].size();
        if(m * n != r * c)  return mat;
        vector<vector<int>> ans(r, vector<int>(c));
        for(int i = 0; i < m * n; i++)
            ans[i / c][i % c] = mat[i / n][i % n];

        return ans;
    }
};

int main(){
    Solution a;
    vector<vector<int>> b{{1,2},{3,4}};
    vector<vector<int>> ans = a.matrixReshape(b, 1, 4);
    for(int i = 0; i < ans.size(); i++)
        for(int j = 0; j < ans[0].size(); j++)
            cout << ans[i][j] <<" ";
}