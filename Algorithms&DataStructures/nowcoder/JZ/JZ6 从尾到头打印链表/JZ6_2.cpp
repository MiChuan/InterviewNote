/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        /* 先统计链表节点数，再构造对应长度数组 */
        int len = 0;
        ListNode* p = nullptr;
        
        for (p = head; nullptr != p; p = p->next)
        {
            ++len;
        }
        
        vector<int> result_vec(len);
        p = head;
        
        while (len > 0)
        {
            result_vec[len - 1] = p->val;
            p = p->next;
            --len;
        }
        
        return result_vec;
    }
};