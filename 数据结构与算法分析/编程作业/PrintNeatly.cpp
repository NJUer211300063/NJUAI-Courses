#include <iostream>
#include <stdint.h>
#include <assert.h>
using namespace std;

#define MIN(x, y) ((x) > (y) ? (y) : (x))

int64_t minimize_slot(uint64_t n, uint64_t L, uint64_t len[]) {
    int64_t dp[n+1];   // dp[i]表示第1个单词到第i个单词的最小slot
    int64_t sup[n+1][n+1]; // sup[i][j]表示第i个到第j个单词在同一行的slot
    // compute sup
    for (int i = 1; i <= n; i++) {
        sup[i][i] = -1;
        if (len[i] - len[i-1] > L)  // 某个单词长度超过一行
            { cout << len[i] - len[i-1] << endl; assert(0); }
        else sup[i][i] = ((L - len[i] + len[i-1]) * (L - len[i] + len[i-1]) * (L - len[i] + len[i-1]));
        for (int j = i + 1; j <= n; j++) {
            if (len[j] - len[i-1] + (j - i) <= L)
                sup[i][j] = (L - (len[j] - len[i-1] + (j - i))) * (L - (len[j] - len[i-1] + (j - i))) * (L - (len[j] - len[i-1] + (j - i)));
            else sup[i][j] = -1;
        }
    }
    // dp
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i-1] + sup[i][i];  // 第i个单词单独一行
        for(int j = i - 1; j >= 1; j--) {  // 第j个单词和第i个单词一行
            if (sup[j][i] == -1)    break;
            dp[i] = MIN(dp[i], dp[j-1] + sup[j][i]);
        }
    }
    // 因为最后一行的slot不算，所以要进一步处理
    int64_t ret = dp[n];   
    for (int i = n; i > 0 && sup[i][n] > 0; i--) { 
        ret = MIN(ret, dp[i-1]);
    }
    return ret;
}

int main() {
    int t; cin >> t;
    while (t--) {
        uint64_t n, L;
        cin >> n >> L;
        uint64_t len[n+1];
        uint64_t sum = 0, tmp = 0;
        for (int i = 0; i < n; i++) {
            cin >> tmp;
            sum += tmp;
            len[i+1] = sum;
        }
        len[0] = 0;
        cout << minimize_slot(n, L, len) << endl;
    }
}


