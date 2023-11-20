# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        for(int i=0; i<n; i++)
            for (int j=i+1; j<n; j++){
                if(nums[i] + nums[j] == target){
                    vector<int> tmp{i,j};
                    return tmp;
                }
                    
            }
    vector<int> tm{0,0};
    return tm;
    }
    
};

int main(){
    Solution a;
    vector<int> b = {3,2,4};
    vector<int> x = a.twoSum(b, 6);
    cout<<x[0]<<" "<<x[1]<<endl;
}