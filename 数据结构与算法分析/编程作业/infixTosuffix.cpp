#include<bits/stdc++.h>
using namespace std;

int priority(char c) {
    if (c == '(')
        return 0;
    else if (c == '-' || c == '+')
        return 1;
    else if (c == '/' || c == '*')
        return 2;
    else    
        return -1;
    
}
void Turn(string exp){
    stack<char> sta;
    for(auto s:exp){
        if('0'<=s && s<='9'){
            cout<<s;
        }
        else if(s=='('){
            sta.push(s);
        }
        else if(s==')'){
            while(sta.top()!='('){
                cout<<sta.top();
                sta.pop();
            }
            sta.pop();
        }
        else{
            if(sta.empty()){
                sta.push(s);
            }
            else if(priority(s) > priority(sta.top()))
                sta.push(s);
            else{
                while(priority(s) <= priority(sta.top())){

                    cout<<sta.top();
                    sta.pop();
                    if(sta.empty())
                        break;
                }
                sta.push(s);
            }
        }
    }
    while(!sta.empty()){
        cout<<sta.top();
        sta.pop();
    }
    
}

int main(){
    string exp = "";
    cin>>exp;
    Turn(exp);

    
}