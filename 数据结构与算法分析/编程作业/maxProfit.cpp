# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minbuy = 1e9,max_pro = 0;
        for(int i=0; i<prices.size(); i++){
            max_pro = max(prices[i]-minbuy>0?prices[i]-minbuy:0, max_pro);
            minbuy = prices[i]>minbuy?minbuy:prices[i];
        }
        return max_pro;
    }
};

int main(){
    Solution a;
    vector<int> b{7,1,5,3,6,4};
    cout << a.maxProfit(b);
    
}