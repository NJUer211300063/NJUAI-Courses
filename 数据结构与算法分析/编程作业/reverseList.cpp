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
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) 
            return head;
        ListNode* former = head;
        ListNode* net = head->next;
        while (net != nullptr) {
            ListNode* temp = net->next;
            net->next = former;
            former = net;
            net = temp;
        }
        head->next = nullptr;

        return former;
    }
};