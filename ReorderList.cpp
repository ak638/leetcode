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
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
	public:
		void reorderList(ListNode *head) {
			vector<ListNode *> vec;

			ListNode *cur = head;
			while (cur)
			{
				vec.push_back(cur);
				cur = cur->next;
			}

			if (vec.size() <= 2) return;

			int i = 0;
			int j = (int)vec.size() - 1;

			for ( ; i < j; i++, j--)
			{
				vec[j]->next = vec[i]->next;
				vec[i]->next = vec[j];
			}

			vec[i]->next = NULL;
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

	}

	return 0;
}
