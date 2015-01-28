#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string.h>
#include <cmath>

using namespace std;

/**
   * Definition for binary tree
   * struct TreeNode {
   *     int val;
   *     TreeNode *left;
   *     TreeNode *right;
   *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
   * };
 */
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct BuildNode {
	TreeNode *node;
	int state; //0 - init; 1 -left now; 2- right now 
	BuildNode(TreeNode *_node, int _state=0) : node(_node), state(_state) {}
};

struct ShowNode {
	TreeNode *node;
	int indent; //show indent of tabs
	int level; //BFS level
	ShowNode(TreeNode *_node, int _indent=0, int _level=0) : node(_node), indent(_indent), level(_level) {}
};

class Solution {
	public:
		vector<int> preorderTraversal(TreeNode *root) {
			vector<int> res;
			if (! root) return res;

			stack<TreeNode *> stVisitNode;
			stVisitNode.push(root);

			while (! stVisitNode.empty())
			{
				TreeNode *cur = stVisitNode.top();
				stVisitNode.pop();
				
				//visit
				res.push_back(cur->val);

				//pop left first for next iteration
				if (cur->right) stVisitNode.push(cur->right);
				if (cur->left) stVisitNode.push(cur->left);
			}

			return res;
		}

		vector<int> postorderTraversal(TreeNode *root) {
			/*
			   更为简洁的方式：利用每次插入结果数组第一个位置来制造后序遍历
			 */
			vector<int> res;
			if (! root) return res;

			stack<TreeNode *> stVisitNode;
			stVisitNode.push(root);

			while (! stVisitNode.empty())
			{
				TreeNode *cur = stVisitNode.top();
				stVisitNode.pop();
				
				//visit, but in front, then as back in final result
				res.insert(res.begin(), cur->val);

				if (cur->left) stVisitNode.push(cur->left);
				if (cur->right) stVisitNode.push(cur->right);
			}

			return res;
		}

		vector<int> postorderTraversal_v1(TreeNode *root) {
			/*
			   退栈的时候才访问节点
			 */
			vector<int> res;
			if (! root) return res;

			stack<TreeNode *> stVisitNode;
			stVisitNode.push(root);
			TreeNode *cur = stVisitNode.top(); //当前处理的节点，用来辅助判断是否需要退栈或者往右继续下去
			bool bShouldBt = false;

			while (! stVisitNode.empty())
			{
				//keep going left direction
				while (NULL != (cur = stVisitNode.top()->left)) stVisitNode.push(cur);

				//if need backtrack
				bShouldBt = false;

				//decide next step: backtrack or go right side
				if (stVisitNode.top()->right) //has right
					stVisitNode.push(stVisitNode.top()->right);
				else //no right side, should backtrack
					bShouldBt = true;

				//need backtrack
				if (bShouldBt)
				{
					//keep pop util stack empty or (right child of top is not null and not processed)
					do
					{
						cur = stVisitNode.top();
						//visit it
						res.push_back(cur->val);

						stVisitNode.pop();
					} while (! stVisitNode.empty() && (cur == stVisitNode.top()->right || NULL == stVisitNode.top()->right));

					if (! stVisitNode.empty()) //right should be processed and not yet, then push right
					{
						stVisitNode.push(stVisitNode.top()->right);
					}
				}
			}
			
			return res;
		}

		TreeNode *buildBinaryTree(vector<string> &vecStr)
		{
			TreeNode *root = NULL;

			stack<BuildNode> skBuild;

			for (size_t i = 0; i < vecStr.size(); ++i)
			{
				//backtrack when meets #
				if (vecStr[i] == "#")
				{
					if (skBuild.empty()) break; //build done

					while (skBuild.top().state == 2) //already right & meet end
					{
						skBuild.pop();
						if (skBuild.empty()) break;
					}

					skBuild.top().state++; //move to right

					continue;
				}

				int val = atoi(vecStr[i].c_str());	
				TreeNode *newNode = new TreeNode(val);
				
				//link newNode to root tree
				if (! skBuild.empty())
				{
					if (skBuild.top().state == 1) skBuild.top().node->left = newNode;
					else skBuild.top().node->right = newNode;
				}
				else root = newNode;
				
				//prepare for next iteration
				skBuild.push(BuildNode(newNode, 1));
			}

			return root;
		}

		void showSimpleTree(TreeNode *root)
		{
			if (! root) return;

			queue<TreeNode *> queueNode;
			queueNode.push(root);

			while (queueNode.empty() == false)
			{
				if (queueNode.front()->left) 
				{
					printf("%d -> %d\n", queueNode.front()->val, queueNode.front()->left->val);
					queueNode.push(queueNode.front()->left);
				}
				else
				{
					printf("%d -> #\n", queueNode.front()->val);
				}

				if (queueNode.front()->right) 
				{
					printf("%d -> %d\n", queueNode.front()->val, queueNode.front()->right->val);
					queueNode.push(queueNode.front()->right);
				}
				else
				{
					printf("%d -> #\n", queueNode.front()->val);
				}

				queueNode.pop();
			}
		}
		
		int getMaxLeftIndent(TreeNode *root, int indent=1)
		{
			int ret = indent;
			if (! root) return ret;

			if (root->left) ret = max(getMaxLeftIndent(root->left, indent+1), ret);
			if (root->right) ret = max(getMaxLeftIndent(root->right, indent-1), ret);

			return ret;
		}

		void showTree(TreeNode *root)
		{
			if (! root) return;

			int indent = getMaxLeftIndent(root);
			printf("indent: %d\n", indent);
			queue<ShowNode> queNodeBFS;
			queNodeBFS.push(ShowNode(root, indent, 0));
			int pre_level = -1;

			while (! queNodeBFS.empty())
			{
				//print indent of current level once
				if (pre_level != queNodeBFS.front().level) 
				{
					printf("\n");
					for (int i = 0; i < queNodeBFS.front().indent; ++i) printf("\t");
					pre_level = queNodeBFS.front().level;
				}

				if (queNodeBFS.front().node) printf("%d\t\t", queNodeBFS.front().node->val);
				else printf("#\t\t");

				//push left and right
				if (queNodeBFS.front().node)
				{
					queNodeBFS.push(ShowNode(queNodeBFS.front().node->left, queNodeBFS.front().indent-1, queNodeBFS.front().level+1));
					queNodeBFS.push(ShowNode(queNodeBFS.front().node->right, queNodeBFS.front().indent+1, queNodeBFS.front().level+1));
				}

				//pop parent
				queNodeBFS.pop();
			}
			printf("\n");
		}
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution poSolution;

	int testcase = 0;
	scanf("%d", &testcase);

	while (testcase--)
	{
		int nodenum = 0;
		scanf("%d", &nodenum);
		char tmp[8];
		vector<string> vecStr;

		while (nodenum--)
		{
			scanf("%s", tmp);
			vecStr.push_back(tmp);
		}

		TreeNode *root = poSolution.buildBinaryTree(vecStr);
		poSolution.showSimpleTree(root);

		poSolution.showTree(root);

		//vector<int> res = poSolution.postorderTraversal(root);
		vector<int> res = poSolution.preorderTraversal(root);
		printf("\nRES: ");
		for (size_t i = 0; i < res.size(); ++i)
		{
			printf("%d ", res[i]);
		}
		printf("\n");
	}

	return 0;
}

/*
1
15
1 # 2 3 4 5 # 6 # # 12 # 15 16 # #
*/
