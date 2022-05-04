/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead) {
        ListNode* pre = nullptr;
        ListNode* new_head = new ListNode(0);
        int value = 0;
        
        if (nullptr == pHead || nullptr == pHead->next) {
            return pHead;
        }
        
        new_head->next = pHead;
        pre = new_head;
        while (nullptr != pre->next && nullptr != pre->next->next) {
            if (pre->next->val == pre->next->next->val) {
                value = pre->next->val;
                while (nullptr != pre->next && value == pre->next->val) {
                    pre->next = pre->next->next;
                }
            }
            else {
                pre = pre->next;
            }
        }
        
        return new_head->next;
    }
};