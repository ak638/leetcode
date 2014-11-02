#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <string.h>

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
		ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
			ListNode newList = ListNode(0);
			ListNode *newCurNode = &newList;

			while (l1 && l2)
			{
				if (l1->val == l2->val)
				{
					newCurNode->next = l1;
					newCurNode = l1;
					l1 = l1->next;

					newCurNode->next = l2;
					newCurNode = l2;
					l2 = l2->next;
				}
				else if (l1->val < l2->val)
				{
					newCurNode->next = l1;
					newCurNode = l1;
					l1 = l1->next;
				}
				else
				{
					newCurNode->next = l2;
					newCurNode = l2;
					l2 = l2->next;
				}
			}
			
			if (l1) newCurNode->next = l1;
			else if (l2) newCurNode->next = l2;
			else newCurNode->next = NULL;

			return newList.next;
		}
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution  poSolution;

	ListNode *newList = poSolution.mergeTwoLists(NULL, NULL);

	return 0;
}
