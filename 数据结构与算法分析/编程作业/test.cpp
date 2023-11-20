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

void print_debug() {
    map <int64_t, NONE>::iterator it = multiset.begin();
    for (; it != multiset.end(); it++) {
        cout << "index: " << it->first << " nums: " << it->second.nums << " sum of former: " << it->second.sun_of_former << endl;
    }
}

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
                print_debug();
            }
            else if (it == multiset.end()) {
                // 原先不存在，先插入
                print_debug()
                multiset.emplace(arg1, NONE {.nums = 1, .sun_of_former = arg1});
                // 由后继获取前驱
                if (it1 == multiset.end()) {
                    // 没有后继，只有前驱
                    if (multiset.size() != 0) {
                        it1--;
                        multiset[arg1].sun_of_former += it1->second.sun_of_former;
                    }  
                    // 没有后继，没有前驱
                    print_debug();
                }
                else { // 存在后继
                    if (multiset.size() > 1) { // 也存在前驱
                        it1--;
                        int64_t tmp = it1->second.sun_of_former + arg1;
                        it1++;
                        multiset[arg1].sun_of_former = tmp;
                        for (; it1 != multiset.end(); it1++) {
                            it1->second.sun_of_former = (tmp + it1->first * it1->second.nums);
                            tmp = it1->second.sun_of_former;
                        }
                    } 
                    else { // 但不存在前驱
                        it1->second.sun_of_former += arg1;
                    }
                    print_debug();
                }
            }
            else { /*原先存在*/
                if (it1 == multiset.end()) { // 没有后继
                    multiset[arg1].nums++;
                    multiset[arg1].sun_of_former += arg1;
                    print_debug();
                }
                else {
                    multiset[arg1].nums++;
                    multiset[arg1].sun_of_former += arg1;
                    int64_t tmp = multiset[arg1].sun_of_former;
                    for (; it1 != multiset.end(); it1++) {
                        it1->second.sun_of_former = (tmp + it1->first * it1->second.nums);
                        tmp = it1->second.sun_of_former;
                    }
                    print_debug();
                }
            }
            break;
        case 1: // 删除元素
            cin >> arg1;
            arg1 = (arg1 + lans) % P;
            it = multiset.find(arg1);
            it1 = multiset.upper_bound(arg1);
            
            if (it == multiset.end()) { // 没有这个元素
                cout << 0 << endl;
                print_debug();
            }
            else { // 存在这个元素
                cout << multiset[arg1].nums << endl;
                multiset[arg1].nums--;
                multiset[arg1].sun_of_former -= arg1;
                int64_t tmp = multiset[arg1].sun_of_former;
                if (multiset[arg1].nums == 0 ) {
                    cout << "erase: " << arg1 << endl;
                    multiset.erase(arg1);
                    cout << "size: " << multiset.size() << endl;
                    print_debug();
                }
                if (it1 != multiset.end()) { // 这个元素存在后继
                    for (; it1 != multiset.end(); it1++) {
                        it1->second.sun_of_former = tmp + it1->first * it1->second.nums;
                        tmp = it1->second.sun_of_former;
                    }
                    print_debug();
                }
                print_debug();
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
            it1 = multiset.upper_bound(arg2);
            
            // cout << it->first << endl;
            // cout << it1->first << endl;
            
            it1--;
            // cout << it->first << endl;
            cout << it1->first << endl;
            cout << it1->second.sun_of_former << endl;
            if (it == multiset.begin()) {
                lans = it1->second.sun_of_former;
                cout << it1->second.sun_of_former<< endl;
                break;
            }
            it--;
            cout << "arg1 - arg2: " << arg1  << " "  << arg2 << " ";
            cout << "real: " << it1->first << " " << it->first << " " << endl;
            
            lans = it1->second.sun_of_former - it->second.sun_of_former;
            cout << it1->second.sun_of_former - it->second.sun_of_former << endl;
            break;
        default:
            break;
        }
    }

    it = multiset.begin();
    for (; it != multiset.end(); it++) {
        cout << "index: " << it->first << " nums: " << it->second.nums << " sum of former: " << it->second.sun_of_former << endl;
    }
}