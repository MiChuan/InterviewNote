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
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        ListNode* p1 = pHead1;
        ListNode* p2 = pHead2;
        int len1 = 0;
        int len2 = 0;
        
        if (NULL == p1 || NULL == p2) {
            return NULL;
        }
        
        while (NULL != p1) {
            p1 = p1->next;
            ++len1;
        }
        
        while (NULL != p2) {
            p2 = p2->next;
            ++len2;
        }
        
        p1 = pHead1;
        p2 = pHead2;
        
        while (len1 > len2) {
            p1 = p1->next;
            --len1;
        }
        
        while (len1 < len2) {
            p2 = p2->next;
            --len2;
        }
        
        while (NULL != p1) {
            if (p1 == p2) {
                return p1;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        
        return NULL;
    }
};