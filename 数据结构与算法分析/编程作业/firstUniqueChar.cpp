# include <iostream>
# include <vector>
# include <unordered_map>
# include <string.h>
using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> dic;
        int lens = s.size();

        for(int i = 0; i < lens; i++) {
            dic[s[i]]++;
        }

        for(int i = 0; i < lens; i++) {
            if (dic[s[i]] == 1)
                return i;
        }

        return -1;
    }
};

int main(){
    Solution sl;
    string s = "aabb";
    cout << sl.firstUniqChar(s);

    return 0;
}