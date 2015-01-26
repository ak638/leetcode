#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
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
		ListNode *insertionSortList(ListNode *head) {
			/*
				每次选择一个元素插入前面已经排好序的list里面
				维护最后一个已排序的节点指针
				sorted | unsorted
			*/
			if (! head) return head;
			
			ListNode *lastSordNode = head;
				
			while (lastSordNode->next)
			{
				ListNode *firstUnsortNode = lastSordNode->next;
				//printf("DEBUG: lastsorted[%d] firstunsorted[%d]\n", lastSordNode->val, firstUnsortNode->val);

				ListNode **targetPos = &head;

				while (*targetPos != firstUnsortNode && (*targetPos)->val < firstUnsortNode->val)
				{
					targetPos = &(*targetPos)->next;
				}
				//printf("target pos[%d]\n", (*targetPos)->val);

				if (*targetPos != firstUnsortNode) //the target position found
				{
					ListNode *one = firstUnsortNode;
					
					//get one out
					lastSordNode->next = one->next;

					//link next
					one->next = *targetPos;

					//adjust head(no need, because targetPos is pointer to pointer)
					//if (head == *targetPos) head = one;

					//put it in
					*targetPos = one; //not targetPos = &one;
				}
				else //need not to move
				{
					lastSordNode = firstUnsortNode;
				}
			}

			return head;
		}

		void printList(ListNode *head)
		{
			ListNode *cur = head;
			while (cur)
			{
				printf("%d => ", cur->val);
				cur = cur->next;
			}
			printf(" nil\n");
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
		ListNode *head = NULL;
		ListNode **cur = &head;

		ListNode *newNode = NULL;
		int nodenum = 0;
		scanf("%d", &nodenum);
		
		while (nodenum--)
		{
			newNode = new ListNode(0);
			scanf("%d", &newNode->val);

			*cur = newNode;
			cur = &(*cur)->next;
		}

		poSolution.printList(head);

		ListNode *sortedHead = poSolution.insertionSortList(head);
		
		poSolution.printList(sortedHead);
	}

	return 0;
}

/*
1
8
3 6 2 5 7 1 2 4
*/
