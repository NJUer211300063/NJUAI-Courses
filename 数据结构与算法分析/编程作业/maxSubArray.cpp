# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> list;
        list.assign(nums.begin(), nums.end());
        for(int i=1; i<n; i++)
            list[i] = max(list[i], list[i]+list[i-1]);
        return *max_element(list.begin(), list.end());
    }
};

int main(){
    Solution a;
    vector<int> b{-2,1,-3,4,-1,2,1,-5,4};
    cout<<a.maxSubArray(b);
}