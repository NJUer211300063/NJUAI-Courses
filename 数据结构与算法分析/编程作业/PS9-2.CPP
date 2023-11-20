#include <iostream>
using namespace std;

int cnt = 0;

void boom(){
    ++cnt;
    if (cnt <= 9990) return;
    int k = 0;
    cout << 100 / k <<endl;
    return;
}

int main() {
    int n; cin >> n;
    int query;
    int candidate = 0;
    // 选一个候选
    for (int i = 1; i < n; i++) {
        cout << "? " << candidate << " " << i << endl;
        cout.flush();
        cin >> query;
        if (query == 1) candidate = i; 
    }

    // 验证这个候选
    int i ;
    for (i = 0; i < n; i++) {
        cout << "? " << candidate << " " << i << endl;
        cout.flush();
        cin >> query;
        if (query == 1) break;
    }
    int j;
    for (j = 0; j < n; j++) {
        cout << "? " << j << " " << candidate << endl;
        cout.flush();
        cin >> query;
        if (query == 0 && (j != candidate)) break;
    }
    
    if (i == n && j == n)
        cout << "! " << candidate << endl;
    else cout << "! -1" << endl;
}