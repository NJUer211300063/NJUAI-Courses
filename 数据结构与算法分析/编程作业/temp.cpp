#include <stdio.h>
int main() {
    int len;
    scanf("%d", &len);
    int lo = 1, hi = len;
    int ret = 1;
    int loVal, hiVal, loRight, hiLeft;
    printf("? %d\n", lo); scanf("%d", &loVal);
    printf("? %d\n", lo + 1); scanf("%d", &loRight);
    printf("? %d\n", hi); scanf("%d", &hiVal);
    printf("? %d\n", hi - 1); scanf("%d", &hiLeft);
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (lo + 1 == hi) {ret = loVal < hiVal ? lo : hi; break;}
        if (lo == 1 && hi == len && loVal < loRight && hiVal < hiLeft) {
            ret = loVal < hiVal? lo:hi;
            break;
        }
        if (loVal > loRight && hiVal > hiLeft) {
            int mVal, mRight, mLeft;
            printf("? %d\n", mid); scanf("%d", &mVal);
            printf("? %d\n", mid + 1); scanf("%d", &mRight);
            printf("? %d\n", mid - 1); scanf("%d", &mLeft);
            if (mVal < mRight) { hi = mid; hiVal = mVal; hiLeft = mLeft; continue;}
            else { lo = mid; loVal = mVal; loRight = mRight; continue; }
        }
        if (loVal < loRight && hiVal > hiLeft) {
            if (lo == 1 && hi == len) {if (loVal < hiVal) {ret = lo; break;}}
            int mVal, mRight, mLeft;
            printf("? %d\n", mid); scanf("%d", &mVal);
            printf("? %d\n", mid + 1); scanf("%d", &mRight);
            printf("? %d\n", mid - 1); scanf("%d", &mLeft);
            if (mVal < mRight) {
                if (mVal < loVal) {hi = mid; hiVal = mVal; hiLeft = mLeft; continue;}
                else {lo = mid;loVal = mVal; loRight = mRight; continue;}
            }
            else {lo = mid;loVal = mVal; loRight = mRight; continue;}
        }
        if (loVal > loRight && hiVal < hiLeft) {
            if (lo == 1 && hi == len) {if (loVal > hiVal) {ret = hi; break;}}
            int mVal, mRight, mLeft;
            printf("? %d\n", mid); scanf("%d", &mVal);
            printf("? %d\n", mid + 1); scanf("%d", &mRight);
            printf("? %d\n", mid - 1); scanf("%d", &mLeft);
            if (mVal > mRight) {
                if (mVal > loVal) {hi = mid; hiVal = mVal; hiLeft = mLeft; continue;}
                else {lo = mid;loVal = mVal; loRight = mRight; continue;}
            }
            else {hi = mid;hiVal = mVal; hiLeft = mLeft; continue;}
        }
    }
    printf("! %d\n", ret);
    return 0;
}