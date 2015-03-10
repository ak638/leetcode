#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <set>
//#include <unordered_set>
#include <map>
//#include <unordered_map>
//#include "unordered_set"
//#include "unordered_map"
#include <string.h>
#include <cmath>

using namespace std;

//https://leetcode.com/problems/binary-tree-maximum-path-sum/

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
	public:
		int maxPathSum(TreeNode *root) {
			if (! root) return 0;

			int iMaxSideSum = 0;
			int iMaxSum = INT_MIN;

			countTree(root, iMaxSideSum, iMaxSum);

			return iMaxSum;
		}

		void countTree(TreeNode *cur, int &iMaxSideSum, int &iMaxSum)
		{
			if (! cur) return;	

			int iLeftSideSum = INT_MIN;
			int iRightSideSum = INT_MIN;

			if (cur->left) countTree(cur->left, iLeftSideSum, iMaxSum);
			if (cur->right) countTree(cur->right, iRightSideSum, iMaxSum);

			//如果子树且子树根节点为路径的一端的结果小于0，则不取
			if (iLeftSideSum < 0) iLeftSideSum = 0;
			if (iRightSideSum < 0) iRightSideSum = 0;

			//汇总左右子树的值，计算新的最大值
			int sum = cur->val + iLeftSideSum + iRightSideSum;
			if (sum > iMaxSum) iMaxSum = sum;

			//更新当前节点子树且以根节点为路径的一端的结果
			iMaxSideSum = cur->val;
			if (iLeftSideSum >= iRightSideSum) iMaxSideSum += iLeftSideSum;
			else iMaxSideSum += iRightSideSum;
		}
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution poSolution;

	int testcase = 0;
	scanf("%d", &testcase);

	printf("%d\n", INT_MIN);

	while (testcase--)
	{

	}

	return 0;
}
