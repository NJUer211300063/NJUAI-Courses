#include <stdio.h>
#include <string.h>
int mymin(int a, int b, int c) {
    a = (a < b ? a : b);
    return a < c ? a : c;
}

int minDistance(char * word1, char * word2) {
    int len1 = strlen(word1), len2 = strlen(word2);
    int dp[len1+1][len2+1];
    dp[0][0] = 0;
    for (int i=1; i<=len1; i++)
        dp[i][0] = i;
    for (int j=1; j<=len2; j++)
        dp[0][j] = j;
    for (int i=1; i<=len1; i++)
        for (int j=1; j<=len2; j++) {
            int sublen = dp[i-1][j] + 1;
            int inslen = dp[i][j-1] + 1;
            int difflen = dp[i-1][j-1];
            if (word1[i-1] != word2[j-1])
                difflen += 1;
            dp[i][j] = mymin(sublen, inslen, difflen);
        }
    return dp[len1][len2];
}

int main() {
    char *word1 = "horse";
    char *word2 = "ros";
    printf("%d\n", minDistance(word1, word2));
}