/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
        ListNode* newHead = new ListNode(0);
        ListNode* tail = newHead;
        ListNode* p1 = pHead1;
        ListNode* p2 = pHead2;
        
        while (NULL != p1 && NULL != p2)
        {
            if (p1->val < p2->val)
            {
                tail->next = p1;
                p1 = p1->next;
            }
            else
            {
                tail->next = p2;
                p2 = p2->next;
            }
            tail = tail->next;
        }
        
        tail->next = p1 ? p1 : p2;
        
        return newHead->next;
    }
};