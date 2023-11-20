#include <iostream>
#include <stdint.h>
using namespace std;

#define UINF -10000000000

uint64_t rod_cutting(int n, uint64_t c, int64_t p[], uint64_t l[]) {
    int64_t dp[n+1];
    for (int i = 0; i <= n; i++)
        dp[i] = UINF;
    dp[0] = 0;
    for (int i = 0; i <= n; i++)  // 遍历长度为i的片段
        for (int j = n; i <= j; j--)  // 遍历剩余长度
                for (int k = 1; k <= l[i] && (j - i * k) >= 0; k++) { // 遍历长度为i的片段切几次
                    dp[j] = max(dp[j], dp[j - k * i] + p[i] * k);
                }
    return dp[n] + c; // 加c是因为最后一段不需要切割
}

int main() {
    // int n = 3, c = 0;
    // int64_t p[n+1] = {UINF, 1, 1, 1};
    // uint64_t l[n+1] = {0, 1, 1, 1};
    // cout << rod_cutting(n, c, p, l);
    int t; cin >> t;
    while(t--) {
        int n;
        uint64_t c;
        cin >> n >> c;
        int64_t p[n+1];
        uint64_t l[n+1];
        p[0] = UINF;
        l[0] = 0;
        for (int i = 1; i <= n; i++)  { cin >> p[i]; p[i] -= c; }
        for (int i = 1; i <= n; i++)  cin >> l[i];
        cout << rod_cutting(n, c, p, l) << endl;
    }
}