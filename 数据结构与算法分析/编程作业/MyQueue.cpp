# include <iostream>
# include <stack>
# include <string.h>
using namespace std;

class MyQueue {
private:
    stack<int> st1;
    stack<int> st2;
    int fr;

public:
    
    void push(int x) {
        if (st1.empty())
            fr = x;
        st1.push(x);
    }
    
    int pop() {
        if (st2.empty()) {
            while (!st1.empty()) {
                st2.push(st1.top());
                st1.pop();
            }
        }
        int tmp = st2.top();
        st2.pop();
        return tmp;
    }
    
    int peek() {
        if (!st2.empty())
            return st2.top();
        return fr;
    }
    
    bool empty() {
        return st1.empty() && st2.empty();
    }
};