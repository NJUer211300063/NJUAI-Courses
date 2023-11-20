#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;
    if (n == 1) { cout << "! 1" << endl; return 0;}
    int major = 1, count = 1;
    int judge;
    for(int i = 2; i < n + 1; i++) {
        cout << "? " << major << " " << i << endl;
        cin >> judge;
        switch (judge)
        {
        case 0: count--; break;
        case 1: count++; break;
        default:    return 0;
        }
        if (count <= 0) { major = i; count = 1;}
    }

    if(count <= 0)  { cout << "! -1" << endl; return 0;}
    else {
        count = 0;
        for (int i = 1; i < n + 1; i++) {
            cout << "? " << major << " " << i << endl;
            cin >> judge;
            if (judge == 1) count++;
        }
    }
    
    if(count > (n / 2)) cout << "! " << major << endl;
    else cout << "! -1" << endl;
    return 0;
}