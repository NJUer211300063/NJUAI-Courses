#include<bits/stdc++.h>
using namespace std;


// 定义两种结构体
struct pos
{
    int x;
    int y;
};

struct pos1
{
    int x;
    char c;
};


int cmpfunc (const void * a, const void * b)
{
   	return (*(pos*)a).x - (*(pos*)b).x;
}

int cmpfunc1 (const void * a, const void * b)
{
   	return (*(pos1*)a).x - (*(pos1*)b).x;
}

long merge_count(int a[], int l, int mid, int r) {
    int len = r - l + 1;
    if (len <= 0)   return 0;
    pos1 tmp[len];
    int i;
    for(i = 0; i + l <= mid; i++) {
        tmp[i].x = a[l+i];
        // cout << "len:" << len << endl;
        // cout << "i:" << i << endl;
        tmp[i].c = 'l';
    }
    for(; i+l <= r; i++) {
        tmp[i].x = a[l+i];
        tmp[i].c = 'r';
    }
    qsort(tmp, len, sizeof(tmp[0]), cmpfunc1);
    i = 0;
    long total = 0, count = 0;
    for (; i < len; i++) {
        if (tmp[i].c == 'r'){
            // cout << "tmp[i].c = " << tmp[i].c << endl;
            count ++;
        }
        else {
            // cout << "tmp[i].c = " << tmp[i].c << endl;
            
            total += count;
            // cout << "total: " << total << endl;
        }
    }
    // cout << "len: " << len << endl;
    // cout << "count: " << count << endl;
    // cout << "total: " << total << endl;
    return total;

}

long count(int a[], int l, int r) {
    if (l - r == 0) return 0;
    if (l - r == 1) {
        if (a[l] > a[r])
            return 1;
        else    
            return 0;
    }
    long c1 = count(a, l, l + (r - l) / 2);
    long c2 = count(a, l + (r - l) / 2 + 1, r);
    long c3 = merge_count(a, l, l + (r - l) / 2, r);
    return c1 + c2 + c3;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n; cin >> n;
    pos a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i].x;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].y;
    }
    qsort(a, n, sizeof(a[0]), cmpfunc);
    int tmp[n];
    for (int i = 0; i < n; i++) tmp[i] = a[i].y;
    long ans = 0;
    ans = count(tmp, 0, n-1);
    cout << ans << endl;
    
}