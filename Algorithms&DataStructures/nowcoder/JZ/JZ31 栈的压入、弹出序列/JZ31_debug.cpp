class Solution {
public:
    stack<int> mystack;
    
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        int i = 0, j = 0;
        
        if (pushV.empty()) {
            return true;
        }
        
        // 每次遍历，pushV入栈一个元素
        // 当前入栈出栈元素相等，先入后出，实际直接移动指针
        // 当前栈顶等于出栈元素，先出后入
        // 都不相等，直接入栈
        while (i < pushV.size()) {
            if (pushV[i] != popV[j]) {
                if (!mystack.empty() &&
                    mystack.top() == popV[j]) {
                        mystack.pop();
						cout << "pop: " << popV[j] << endl; ////debug
                        ++j;
                }
				else {
					mystack.push(pushV[i]);
					cout << "push: " << pushV[i] << endl; ////debug
					++i;
				}
            } else {
				cout << "push: " << pushV[i] << endl; ////debug
				cout << "pop: " << popV[j] << endl; ////debug
                ++i, ++j;
            }
        }
        
        
        cout << "debug1" << endl; ////debug
        while (j < popV.size()) {
            if (mystack.top() == popV[j]) {
                cout << "debug2" << endl; ////debug
                    mystack.pop();
					cout << "pop: " << popV[j] << endl; ////debug
                    ++j;
            }
            else {
                cout << "debug3" << endl; ////debug
                return false;
            }
        }
        
        return true;
    }
};