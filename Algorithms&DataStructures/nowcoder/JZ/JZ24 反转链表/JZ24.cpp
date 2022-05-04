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
    ListNode* ReverseList(ListNode* pHead) {
        ListNode* cur_node = pHead;
        ListNode* pre_node = nullptr;
        ListNode* temp = nullptr;
        
        /* 每一次操作将旧链表第一个节点移动到新链表头部 */
        while(nullptr != cur_node)
        {
            temp = cur_node->next;
            cur_node->next = pre_node;
            pre_node = cur_node;
            cur_node = temp;
        }
        
        return pre_node;
    }
};