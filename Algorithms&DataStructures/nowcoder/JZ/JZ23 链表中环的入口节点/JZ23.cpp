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
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        ListNode* fast = pHead, *slow = pHead, *ptr = pHead;
        
        while (NULL != fast) {
            if (NULL == fast->next) {
                break;
            }
            
            slow = slow->next;
            fast = fast->next->next;
            
            if(slow == fast) {
                while (ptr != slow) {
                    ptr = ptr->next;
                    slow = slow->next;
                }
                return slow;
            }
        }
        
        return NULL;
    }
};