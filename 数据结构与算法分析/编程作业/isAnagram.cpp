# include <iostream>
# include <vector>
# include <unordered_map>
# include <string.h>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        int n1 = s.size(), n2 = t.size();
        if (n1 != n2)   return false;
        unordered_map<char, int> map1, map2;

        for (auto ch : s)
            map1[ch]++;
        for (auto ch : t)
            map2[ch]++;

        if (map1.size() != map2.size()) return false;
        for (auto ch : s) {
            if (map1[ch] != map2[ch])
                return false;
        }
        
        return true;

    }
};

int main(){
    Solution sl;
    string a = "rat", b = "car";
    cout << sl.isAnagram(a, b);

    return 0;
}