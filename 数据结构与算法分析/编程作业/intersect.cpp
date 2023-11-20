# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size() > nums2.size())
            return intersect(nums2, nums1);
        
        
    }
};

int main(){
    Solution a;
    vector<int> b1{4,9,5}, b2{9,4,9,8,4};
    vector<int> b3 = a.intersect(b1, b2);
    for(int i=0; i<b3.size(); i++)
        cout << b3[i];
    return 0;
}