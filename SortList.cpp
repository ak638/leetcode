#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
	public:
		ListNode *sortList(ListNode *head) {
			if (! head) return head;

			QuickSort(&head, NULL);

			return head;
		}

		void AppendNode(ListNode **last, ListNode **head, ListNode *node)
		{
			if (*last) (*last)->next = node;
			else 
			{
				*last = node;
				*head = node;
			}
		}

		void QuickSort(ListNode **head, ListNode **end)
		{
			if (! *head || ! (*head)->next) return;

			ListNode *pivot = *head;
			ListNode *lt = NULL, *rt = NULL;
			ListNode *lhead = NULL, *rhead = NULL;
			ListNode **cur = head;
			ListNode *tmp = NULL;
			
			while (*cur)
			{
				if ((*cur)->val < pivot->val)
				{
					AppendNode(&lt, &lhead, *cur);
					lt = *cur;
				}
				else
				{
					AppendNode(&rt, &rhead, *cur);
					rt = *cur;
				}

				tmp = *cur;
				*cur = (*cur)->next;
				tmp->next = NULL;
			}

			//divides into sorting two sides
			QuickSort(&lhead, &lt);
			//optimize this part
			ListNode **ckp = &rhead->next;
			while (*ckp && (*ckp)->val == rhead->val) ckp = &(*ckp)->next;
			QuickSort(ckp, &rt); //skip pivot 
			//QuickSort(&rhead->next, &rt);

			//merge two lists
			if (lhead) 
			{
				*head = lhead;
				lt->next = rhead;
			}
			else *head = rhead;
			//now pivot in middle

			//set last node (in case of changes)
			if (end) *end = rt;
		}

		void showArrayCont(ListNode *marr[], int num)
		{
			for (int i = 0; i < num; ++i)
			{
				printf("%d ", marr[i]->val);
			}
			printf("\n");
		}

		void showArray(ListNode *head)
		{
			while (head)
			{
				printf("%d -> ", head->val);
				head = head->next;
			}
			printf("nil\n");
		}

		ListNode *initList(int arr[], int num)
		{
			ListNode *head = new ListNode(0);
			ListNode *cur = head;

			for (int i = 0; i < num; ++i)
			{
				ListNode *tmp = new ListNode(arr[i]);

				cur->next = tmp;
				cur = tmp;
			}

			return head;
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
		int num = 0;
		scanf("%d", &num);
		printf("==>%d\n", num);

		int arr[28238];
		for (int i = 0; i < num; ++i) scanf("%d", &arr[i]);

		ListNode *fake_head = poSolution.initList(arr, num);
		ListNode *head = fake_head->next;

		poSolution.showArray(head);

		ListNode * res = poSolution.sortList(head);

		//poSolution.showArray(head);

		printf("result...\n");
		poSolution.showArray(res);

		printf("\n");
	}

	return 0;
}

/**
3
9
5 3 7 1 6 2 9 0 4
11
4 4 5 5 4 4 -1 2 5 3 6
70
-1 2 -2 1 -1 -2 1 -2 1 0 -1 2 -2 1 -1 -2 1 -2 1 0 -1 2 -2 1 -1 -2 1 -2 1 0 -1 2 -2 1 -1 -2 1 -2 1 0 -1 2 -2 1 -1 -2 1 -2 1 0 -1 2 -2 1 -1 -2 1 -2 1 0 -1 2 -2 1 -1 -2 1 -2 1 0
*/
