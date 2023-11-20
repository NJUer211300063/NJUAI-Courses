#include<bits/stdc++.h>
using namespace std;

void print_arr(int a[], int len) {
    for (int i = 0; i < len; i++) 
        cout << a[i] << " ";
    cout << endl;
}

void Merge(int a[], int l, int mid, int r) {
    int len = r - l + 1;
    int tmp[len];
    int index = 0;
    int po1 = l, po2 = mid+1;
    
    while (po1 <= mid && po2 <= r) {
        if (a[po1] < a[po2])
            tmp[index++] = a[po1++];
        else 
            tmp[index++] = a[po2++];
    }

    if (po1 <= mid) {
        while (po1 <= mid)
            tmp[index++] = a[po1++];
    }
    else {
        while (po2 <= r)
            tmp[index++] = a[po2++];
    }

    index = 0;
    for (int i = l; i <= r; i++) {
        a[i] = tmp[index++];
    }
    
}

void Merge_Sort(int a[], int l, int r) {
    if (l == r) return;
    int mid = l + (r-l)/2 ;
    // divide
    Merge_Sort(a, l, mid);
    Merge_Sort(a, mid+1, r);
    // merge
    Merge(a, l, mid, r);
}

int main() {
    int a[5] = {1, 2, 5, 3, 4};
    Merge_Sort(a, 0, 4);
    print_arr(a, 5);
}