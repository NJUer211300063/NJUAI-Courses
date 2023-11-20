#include <iostream>
#include <cstdint>
#include <map>
using namespace std;

struct NONE
{
    int64_t nums;
    int64_t sun_of_former;
};

map <int64_t, NONE>multiset;

int main() {
    int64_t Q;
    int64_t P, lans, output3;
    cin >> Q >> P;
    int i;
    lans = 0;
    map <int64_t, NONE>::iterator it, it1;
    for (i = 0; i < Q; i++) {
        int opt;
        int64_t arg1, arg2;
        cin >> opt;
        switch (opt)
        {
        case 0:
            // 获取参数
            cin >> arg1;
            arg1 = (arg1 + lans) % P;
            it = multiset.find(arg1);
            it1 = multiset.upper_bound(arg1);
            if (multiset.size() == 0) { // 空，直接插入
                multiset.emplace(arg1, NONE {.nums = 1, .sun_of_former = arg1});
            } else {
                
            }  
            break;
        case 1:
            cin >> arg1;
            arg1 = (arg1 + lans) % P;
            it= multiset.find(arg1);
            if (it == multiset.end()) {
                cout << 0 << endl;
            }
            else {
                cout << multiset[arg1] << endl;
                multiset[arg1]--;
                if (multiset[arg1] == 0)
                    multiset.erase(arg1);
            }
            break;
        case 2:
            cin >> arg1 >> arg2;
            arg1 = (arg1 + lans) % P;
            arg2 = (arg2 + lans) % P;
            if (arg1 > arg2) {
                int64_t tmp = arg1;
                arg1 = arg2;
                arg2 = tmp;
            }
            it = multiset.upper_bound(arg1);
            output3 = 0;
            for (; it != multiset.end(); it++) {
                if (it->first > arg2)   break;
                output3 += it->first * it->second;
            }
            lans = output3;
            cout << output3 << endl;
            break;
        default:
            break;
        }
    }
    it = multiset.begin();
    for (; it != multiset.end(); it++) {
        cout << "index: " << it->first << " nums: " << it->second << endl;
    }
}