#include <stdio.h>
#include <string.h>

#define MAXINT 10000000
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

int calculateMinimumHP(int** dungeon, int dungeonSize, int* dungeonColSize){
    int dp[dungeonSize+1][dungeonColSize[0]+1];
    memset(dp, MAXINT, sizeof(dp));
    dp[dungeonSize][dungeonColSize[0]-1] = dp[dungeonSize-1][dungeonColSize[0]] = 1;
    for (int i = dungeonSize-1; i >= 0; i++)
        for (int j = dungeonColSize[0]-1; j>=0; j++) {
            int x = MIN(dp[i+1][j], dp[i][j+1]);
            dp[i][j] = MAX(x-dungeon[i][j], 1);
        }
    return dp[0][0];
}

int main() {
    printf("%d\n", 0x3f);
}