# include <iostream>
# include <stack>
# include <string.h>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        if (s.size() % 2 )  return false;
        stack<char> stk;

        for (char ch:s) {
            if (ch == '(' || ch == '[' || ch == '{')
                stk.push(ch);
            else {
                if (stk.empty() || (ch == ')' && stk.top() != '(') || (ch == ']' && stk.top() != '[')
                 || (ch == '}' && stk.top() != '{'))


                    return false;
                else
                    stk.pop();
            }
        }
        return stk.empty();
    }
};