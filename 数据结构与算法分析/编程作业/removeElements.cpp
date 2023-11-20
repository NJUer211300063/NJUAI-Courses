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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* ans = new ListNode(-1);
        ListNode* ans1 = ans;

        while (head != nullptr) {
            if (head->val != val) {
                ans1->next = head;
                ans1 = ans1->next;
            }

            head = head->next;
        }
        
        ans1->next = nullptr;
        return ans->next;
    }
};