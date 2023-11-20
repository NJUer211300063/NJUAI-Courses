#include <iostream>
using namespace std;

int main() {
    int length; cin >> length;
    if (length == 1) { cout << "! 1" << endl; return 0;}
    if (length == 2)  {
        int f, s;
        cout << "? 1" << endl; cin >> f;
        cout << "? 2" << endl; cin >> s;
        int ans = (f < s) ? 1 : 2; 
        cout << "! " << ans << endl; 
        return 0;
    }
    if (length == 3) {
        int f, m, e;
        int ans;
        cout << "? 1" << endl; cin >> f;
        cout << "? 2" << endl; cin >> m;
        cout << "? 3" << endl; cin >> e;
        if (f < m && f < e) ans = 1;
        if (m < f && m < e) ans = 2;
        if (e < f && e < m) ans = 3;
        cout << "! " << ans << endl; 
        return 0;
    }
    int start, end;
    int start_n, end_f;
    int l = 1, r = length;
    int ans;
    cout << "? 1" << endl; cin >> start;
    cout << "? 2" << endl; cin >> start_n;
    cout << "? " << length  << endl; cin >> end;
    cout << "? " << length - 1 << endl; cin >> end_f;
    int state1, state2;
    while (l < r) {
        if (r - l == 1) { 
            ans = start < end ? l : r;
            break; 
        }
        int m = l + (r - l) / 2;
        state1 = (start_n > start) ? 1 : 0;
        state2 = (end > end_f) ? 1 : 0;
        if (state1 == 1 && state2 == 0) {
            ans = start < end ? l : r;
            break; 
        }
        int tmpm, tmpl, tmpr;
        cout << "? " << m << endl;
        cin >> tmpm;
        cout << "? " << m-1 << endl;
        cin >> tmpl;
        cout << "? " << m+1 << endl;
        cin >> tmpr;
        if (state1 == 0 && state2 == 1) {
            if (tmpm < tmpl && tmpm < tmpr) { 
                ans = m;
                break;
            }
            if (tmpm < tmpl) {
                l = m;
                start = tmpm;
                start_n = tmpr; 
                continue;;
            }
            else {
                r = m;
                end = tmpm;
                end_f = tmpl;
                continue;;
            }
        }
        if (state1 == 1 && state2 == 1) {
            if (start < end) {
                ans = l;
                break;
            }
            if (tmpm < tmpr) {
                if (tmpm < start) {
                    r = m; 
                    end = tmpm; 
                    end_f = tmpl; 
                    continue;
                }
                else {
                    l = m;
                    start = tmpm; 
                    start_n = tmpr; 
                    continue;
                }
            }
            else {
                l = m;
                start = tmpm; 
                start_n = tmpr; 
                continue;
            }
        }
        if (state1 == 0 && state2 == 0) {
            if (start > end) {
                ans = r;
                break;
            }
            if (tmpm < tmpl) {
                if (tmpm > start) {
                    r = m;
                    end = tmpm; 
                    end_f = tmpl; 
                    continue;
                }
                else {
                    l = m;
                    start = tmpm; 
                    start_n = tmpr; 
                    continue;
                }
            }
            else {
                r = m;
                end = tmpm; 
                end_f = tmpl; 
                continue;
            }
        }
        
    }
    cout << "! " << ans << endl;
    return 0;

}