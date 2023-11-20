# include <iostream>
# include <vector>
# include <unordered_set>
# include <string.h>
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };


class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode*> myset;
        while (head != nullptr) {
            if (myset.count(head))
                return true;
            myset.insert(head);
            head = head->next;
        }
        return false;
    }
};

int main() {



    return 0;
}