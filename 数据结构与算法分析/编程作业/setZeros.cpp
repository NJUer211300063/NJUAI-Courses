# include <iostream>
# include <vector>
# include <algorithm>
# include <string.h>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {

        int n = matrix.size(), m = matrix[0].size();
        bool rows[n], cols[m];
        memset(rows, false, sizeof(rows));
        memset(cols, false, sizeof(cols));

        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++){
                if (matrix[i][j] == 0)
                    {
                        rows[i] = true;
                        cols[j] = true;
                    }
            }
        
        for(int i = 0; i < n; i++){
            if (rows[i]){
                for(int j = 0; j < m; j++)
                    matrix[i][j] = 0;
            }
        }
        for(int i = 0; i < m; i++){
            if (cols[i]){
                for(int j = 0; j < n; j++)
                    matrix[j][i] = 0;
            }
        }
    }
};

int main(){

    Solution sl;
    vector<vector<int>> mat = {{1,1,1},{1,0,1},{1,1,1}};
    sl.setZeroes(mat);
    

    return 0;
}