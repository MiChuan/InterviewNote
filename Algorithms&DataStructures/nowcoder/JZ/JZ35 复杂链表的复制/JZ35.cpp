/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead) {
        unordered_map<RandomListNode*, RandomListNode*> mp;
        RandomListNode* p = pHead;
        RandomListNode* temp = nullptr;
        
        if (nullptr == pHead) {
            return pHead;
        }
        /* 遍历链表，拷贝标签 */
        while (nullptr != p) {
            temp = new RandomListNode(p->label);
            mp[p] = temp;
            p = p->next;
        }
        p = pHead;
        while (nullptr != p) {
            mp[p]->next = mp[p->next];
            if (nullptr != p->random) {
                mp[p]->random = mp[p->random];
            }
            p = p->next;
        }
        
        return mp[pHead];
    }
};