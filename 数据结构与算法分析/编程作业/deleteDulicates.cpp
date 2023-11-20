# include <iostream>
# include <vector>
# include <unordered_set>
# include <string.h>
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
      ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next)   return head;
        ListNode* cur = head;
        
        while(cur->next) {
            if(cur->next->val != cur->val) {
                cur = cur->next;
            } else {
                cur->next=cur->next->next;
            }
            
        }

        return head;
    }
};