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
			if (! head || ! head->next) return;

			ListNode **front = &head;
			bool bFinished = false;

			order(front, head, &bFinished);	
		}

		void order(ListNode **front, ListNode *cur, bool *bFinished)
		{
			if (! cur) return;

			order(front, cur->next, bFinished);

			//printf("back %d front %d finished %d\n", cur->val, (*front)->val, *bFinished);
			if (*bFinished) return;

			ListNode *tmp = *front;
			cur->next = (*front)->next;
			*front = (*front)->next;
			tmp->next = cur;

			//check finished
			if (*front == cur || (*front)->next == cur)  //偶数个元素 || 奇数个元素
			{
				//printf("cur %d front %d cur->next %d\n", cur->val, (*front)->val, cur->next->val);
				(*front)->next = NULL;
				*bFinished = true;
			}
		}

		void reorderList_v1(ListNode *head) {
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

		ListNode *buildList(vector<int> &vec)
		{
			ListNode *head = NULL;
			ListNode **cur = &head;

			for (size_t i = 0; i < vec.size(); ++i)
			{
				*cur = new ListNode(vec[i]);
				cur = &(*cur)->next;
			}

			return head;
		}

		void showList(ListNode *head)
		{
			ListNode *cur = head;
			while (cur)
			{
				printf("%d -> ", cur->val);
				cur = cur->next;
			}
			printf("NIL\n");
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
		int n;
		scanf("%d", &n);		
		vector<int> vec;
		int a;

		while (n--)
		{
			scanf("%d", &a);		
			vec.push_back(a);
		}

		ListNode *head = poSolution.buildList(vec);
		poSolution.showList(head);
		poSolution.reorderList(head);
		poSolution.showList(head);
	}

	return 0;
}
/*
1
2
1 2 3 4 5 6
 */
