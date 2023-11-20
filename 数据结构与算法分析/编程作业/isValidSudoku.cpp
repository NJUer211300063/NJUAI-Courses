# include <iostream>
# include <vector>
# include <algorithm>
# include <string.h>
using namespace std;

class Solution {
public:

    bool isValidSudoku(vector<vector<char>>& board) {
        int rows[9][9], cols[9][9], subs[3][3][9];
        memset(rows, 0, sizeof(rows));
        memset(cols, 0, sizeof(cols));
        memset(subs, 0, sizeof(subs));
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++){
                if(board[i][j] != '.'){
                    int value = board[i][j] - '1';
                    rows[i][value]++;
                    cols[j][value]++;
                    subs[i / 3][j / 3][value]++;
                    if(rows[i][value] > 1 ||  cols[j][value] > 1 || subs[i / 3][j / 3][value] > 1)
                        return false;
                }

            }
        return true;

    }
};