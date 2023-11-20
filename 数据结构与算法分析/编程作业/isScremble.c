#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

#define MAXLEN 30
int dp[MAXLEN][MAXLEN][MAXLEN+1];
typedef struct HashTable{
    char c;
    int times;
    struct HashTable *next;
} HashTable;

HashTable *isIn(HashTable *head, char c) {
    HashTable *tmp = head;
    while (tmp != NULL) {
        assert(tmp != NULL);
        if (tmp->c == c)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

HashTable * insert(HashTable *head, char c) {
    HashTable *new = malloc(sizeof(HashTable *));
    new->c = c;
    new->times = 1;
    new->next = head;
    return new;
}

void print_HashTable(HashTable *head) {
    for (HashTable *tmp = head; tmp; tmp = tmp->next) {
        printf("%c: %d\n", tmp->c, tmp->times);
    }
    printf("-----------------\n");
}

bool isSimilar(const char *s1, const char *s2, int f1, int f2, int len) {
    HashTable *head = (HashTable *)malloc(sizeof(HashTable));
    head->c = s1[f1];
    head->times = 1;
    head->next = NULL;
    for (int i=1, idx=f1+1; i<len; i++, idx++) {
        HashTable *a = isIn(head, s1[idx]);
        if (a) a->times += 1;
        else head = insert(head, s1[idx]);
    }
    print_HashTable(head);
    for (int i=0, idx=f2; i<len; i++, idx++) {
        HashTable *a = isIn(head, s2[idx]);
        if (a) a->times -= 1;
        else return false;
    }
    while (head) {
        if (head->times != 0)
            return false;
        head = head->next;
    }
    return true;
    
}


bool isEqual(const char *s1, const char *s2, int f1, int f2, int len) {
    while (len--)
    {
        if (s1[f1++] != s2[f2++])
            return false;
    }
    return true;
}

bool dfs(char *s1, char *s2, int f1, int f2, int len) {
    // 记忆化，看是否搜索过
    if (dp[f1][f2][len] == 1)
        return true;
    else if (dp[f1][f2][len] == -1)
        return false;

    // 判断两个字符串是否相等
    if (isEqual(s1, s2, f1, f2, len)) {
        dp[f1][f2][len] = 1;
        return true;
    }

    // 判断字母出现次数
    if (isSimilar(s1, s2, f1, f2, len) == false) {
        dp[f1][f2][len] = -1;
        return false;
    }

    // dp
        // 枚举分割位置
    for (int i = 1; i < len; ++i) {
        // 不交换的情况
        if (dfs(s1, s2, f1, f2, i) && dfs(s1, s2, f1 + i, f2 + i, len - i)) {
            dp[f1][f2][len] = 1;
            return true;
        }
        // 交换的情况
        if (dfs(s1, s2, f1, f2+ len - i, i) && dfs(s1, s2, f1 + i, f2, len - i)) {
            dp[f1][f2][len] = 1;
            return true;
        }
    }

    dp[f1][f2][len] = -1;
    return false;

}

bool isScramble(char * s1, char * s2){
    int l = strlen(s1);
    // int dp[l][l][l+1];
    memset(dp, 0, sizeof(dp));
    return dfs(s1, s2, 0, 0, l);
}

int main() {
    char *s1 = "abc";
    char *s2 = "acb";
    printf("%d\n", isScramble(s1, s2));
}