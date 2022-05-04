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
    	/* 使用栈保存数据 */
        vector<int> result_vec;
        stack<int> my_stack;
        ListNode* p = nullptr;
        
        for (p = head; nullptr != p; p = p->next)
        {
            my_stack.push(p->val);
        }
        
        while (false == my_stack.empty())
        {
            result_vec.push_back(my_stack.top());
            my_stack.pop();
        }
        
        return result_vec;
    }
};