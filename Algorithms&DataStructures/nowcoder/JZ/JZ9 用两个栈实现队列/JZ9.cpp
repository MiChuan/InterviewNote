class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        int temp = 0;
        
        if (!stack2.empty()) {
            temp = stack2.top();
            stack2.pop();
            return temp;
        }
        
        while (!stack1.empty()) {
            stack2.push(stack1.top());
            stack1.pop();
        }
        
        temp = stack2.top();
        stack2.pop();
        return temp;
    }

private:
    stack<int> stack1;    // 入队栈
    stack<int> stack2;    // 出队栈
};