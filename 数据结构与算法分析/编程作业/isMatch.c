#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isMatch(char * s, char * p){
    int len1 = strlen(s), len2 = strlen(p);
    bool dp[len1 + 1][len2 + 1];
    // for (int i = 1; i <= len1; i++)
    //     dp[i][0] = false;
    for (int i = 0; i <= len1; i++)
        for (int j = 0; j <= len2; j++)
            dp[i][j] = false;
    dp[0][0] = true;
    for (int j = 1; j <= len2; j++)
        if (p[j-1] == '*') 
            dp[0][j] = dp[0][j-2];
    for (int i = 1; i <= len1; i++)
        for (int j = 1; j <= len2; j++) {
            if (p[j-1] == '*') {
                if (s[i-1] == p[j-2] || p[j-2] == '?')
                    dp[i][j] = (dp[i][j-2] || dp[i-1][j]);
                else dp[i][j] = dp[i][j-2];
            } else {
                if (s[i-1] == p[j-1] || p[j-1] == '?') 
                    dp[i][j] = dp[i-1][j-1];
                else dp[i][j] = false;
            }
        }
    return dp[len1][len2];
}

int main() {
    char *s = "aa";
    char *p = "a*";
    bool ret = isMatch(s, p);
    if (ret == true)
        printf("true\n");
    else
        printf("false\n");
}