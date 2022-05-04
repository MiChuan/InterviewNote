#include <iostream>
#include <string>
#include <queue>
#include <sstream>
#include <stack>
using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Traverse {
public:
	Traverse(){}
	~Traverse(){}

	void preorderTraverse(TreeNode* root) {//先序遍历
		std::cout<<"preorderTraverse:"<<endl;
		if (root == NULL) return;
        stack<TreeNode*> nodeStack;
        TreeNode* curNode = root;
        while (curNode != NULL || !nodeStack.empty()){
            while (curNode != NULL){
            	std::cout << curNode->val << " ";
                nodeStack.push(curNode);
                curNode = curNode->left;
            }
            if(!nodeStack.empty()){
            	curNode = nodeStack.top();
            	nodeStack.pop();
            	curNode = curNode->right;
            }
        }
        printf("\n");
	}

	void inorderTraverse(TreeNode* root) {//中序遍历
		std::cout<<"inorderTraverse:"<<endl;
		if (root == NULL) return;
        stack<TreeNode*> nodeStack;
        TreeNode* curNode = root;
        while (curNode != NULL || !nodeStack.empty()){
            while (curNode != NULL){
                nodeStack.push(curNode);
                curNode = curNode->left;
            }
            TreeNode* top = nodeStack.top();
            nodeStack.pop();
            std::cout << top->val << " ";
            curNode = top->right;
        }
        printf("\n");
    }

    void backorderTraverse(TreeNode* root) {//后序遍历
		std::cout<<"backorderTraverse:"<<endl;
		if (root == NULL) return;
        stack<TreeNode*> nodeStack;
        TreeNode* curNode = root;
        TreeNode* refer = NULL;
        while (curNode != NULL || !nodeStack.empty()){
            if(curNode != NULL){//从根节点到最左下角的左子树都入栈
            	nodeStack.push(curNode);//中序现将结点进栈保存
            	curNode = curNode->left;
        	} else{
        		curNode = nodeStack.top();//取栈顶
            	if(curNode->right && curNode->right!=refer){//1.右子树还没有访问并且右子树不空，第一次栈顶
                	curNode=curNode->right;///进入右子树
            	}
            	else{//右子树已经访问或为空，接下来出栈访问结点，第二次栈顶
            		curNode = nodeStack.top();//取栈顶
               		nodeStack.pop();
               		std::cout << curNode->val << " ";
                	refer = curNode;///指向访问过的右子树结点
                	curNode=NULL;///使p为空继续访问栈顶
            	}
        	}
        }
        printf("\n");
	}

	void levelTraverse(TreeNode* root) {//层序遍历
		std::cout<<"levelTraverse:"<<endl;
		if (root == NULL) return;
		queue<TreeNode*> treeQueue;
		TreeNode* curNode = root;
		treeQueue.push(root);//根节点入队
		std::cout << root->val << " ";//访问根节点
		while (!treeQueue.empty()) {
			curNode = treeQueue.front();//队首元素
			if (curNode->left != NULL) {
				std::cout << curNode->left->val << " ";
				treeQueue.push(curNode->left);
			}
			if (curNode->right != NULL) {
				std::cout << curNode->right->val << " ";
				treeQueue.push(curNode->right);
			}
			treeQueue.pop();//队首元素出队
		}
		printf("\n");
	}
};

int main() {
	TreeNode* treeRoot = new TreeNode(1);
	treeRoot->left = new TreeNode(2);
	treeRoot->right = new TreeNode(3);
	treeRoot->right->left = new TreeNode(4);
	treeRoot->right->right = new TreeNode(5);
	Traverse T;
	T.preorderTraverse(treeRoot);
	T.inorderTraverse(treeRoot);
	T.backorderTraverse(treeRoot);
	T.levelTraverse(treeRoot);
	return 0;
}