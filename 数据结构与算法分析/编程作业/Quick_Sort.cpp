#include<bits/stdc++.h>
using namespace std;

void print_arr(int a[], int len) {
    for (int i = 0; i < len; i++) 
        cout << a[i] << " ";
    cout << endl;
}

// swap(a[i], a[j])
void swap(int a[], int i, int j) {
    if (i == j) return;
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;    
}

int partionate(int a[], int l, int r) {
    int pviot = a[r];
    int i = l - 1;
    for (int j = l; j < r; j++) {

        // assert(0);
        if (a[j] <= pviot) swap(a, ++i, j);
    }
    swap(a, ++i, r);
    return i+1;
}

void Quick_Sort(int a[], int l, int r) {
    if (l == r) return;
    // 划分partionate
    int mid = partionate(a, l, r);
    Quick_Sort(a, l, mid-1);
    Quick_Sort(a, mid+1, r);
}

int main() {
    int a[5] = {1, 2, 5, 3, 4};
    Quick_Sort(a, 0, 4);
    // swap(a, 0, 1);
    print_arr(a, 5);
}