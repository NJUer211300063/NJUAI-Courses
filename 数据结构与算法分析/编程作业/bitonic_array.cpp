#include <iostream>
using namespace std;

int main(){
    int length; cin >> length;
    if (length == 1) cout << "! 1" << endl;
    int l = 1, r = length;
    int mid; int index1;
    bool success = true;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (mid == 1 || mid == length)   {success = false; break;}
        int tmpl, tmpm, tmpr;
        cout << "? " << mid << endl;
        cin >> tmpm;
        cout << "? " << mid-1 << endl;
        cin >> tmpl;
        cout << "? " << mid+1 << endl;
        cin >> tmpr;
        if (tmpm <= tmpl && tmpm <= tmpr) break; 
        if (mid > l && tmpm > tmpl) r = mid - 1 ; 
        else if (mid < r && tmpm > tmpr) l = mid + 1;
        else break;
    }
    // cout << "! " << mid << endl; return 0;
    // if (mid == 1) {
    //     int tmp;
    //     cout << "? " << length << endl;
    //     cin >> tmp;
    //     if (tmp > )
    // }
    // cout << "! " << mid << endl; return 0;
    if(success)
        { cout << "! " << mid << endl; return 0;}
    else {
        index1 = mid;
        if(mid == 1) { l = length / 2; r = length; }
        else {l = 1; r = length / 2; }
        while (l <= r)
        {
        mid = (l + r) / 2;
        if (mid == 1 || mid == length)   {success = false; break;}
        int tmpl, tmpm, tmpr;
        cout << "? " << mid << endl;
        cin >> tmpm;
        cout << "? " << mid-1 << endl;
        cin >> tmpl;
        cout << "? " << mid+1 << endl;
        cin >> tmpr;
        if (tmpm <= tmpl && tmpm <= tmpr) break; 
        if (mid > l && tmpm > tmpl) r = mid - 1 ; 
        else if (mid < r && tmpm > tmpr) l = mid + 1;
        else break;
        }
    }
    int x, y;
    cout << "? " << index1 << endl;
    cin >> x;
    cout << "? " << mid << endl;
    cin >> y;
    if (x > y)  cout << "! " << mid << endl;
    else cout << "! " << index1 << endl;
    return 0;
}

