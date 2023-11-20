# include <iostream>
# include <vector>
# include <unordered_map>
# include <string.h>
using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        
        int n1 = ransomNote.size(), n2 = magazine.size();
        if (n1 > n2)    return false;
        unordered_map<char, int> map2;

        
        for (char ch : magazine){
            map2[ch] ++;
        } 

        for (char ch : ransomNote){
            map2[ch] --;
            if (map2[ch] < 0)
                return false;
        } 

        return true;

    }
};

int main() {
    Solution sl;
    string s1 = "a", s2 = "b";
    cout << sl.canConstruct(s1, s2);

    return 0;
}