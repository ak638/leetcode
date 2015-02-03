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
#include <string.h>
#include <cmath>

using namespace std;

/**
 *   Definition for singly-linked list.
 *    struct ListNode {
 *         int val;
 *         ListNode *next;
 *         ListNode(int x) : val(x), next(NULL) {}
 *        };
 */

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
	public:
		//return the node where the cycle begins. If there is no cycle, return null.
		ListNode *detectCycle(ListNode *head) {
			/*
			 * 检测到有cycle的条件为slow == fast，此时各自移动的step为m，那么slow走了m个节点，而fast走了2m+1个节点
			 * 也就是说cycle有m+1个节点，等价于 head-->slow step为m，slow->slow step为m+1
			 * 意味着，如果还有一个指针从slow->next开始出发，也有个指针从head重新出发，当它们相遇的时候，也就是cycle开始的节点
			 */
			ListNode *res = NULL;
			if (! head || ! head->next) return res;
			
			ListNode *slow = head;
			ListNode *fast = head->next;
			bool hasCycle = false;

			while (fast)
			{
				if (fast == slow) 
				{
					hasCycle = true;
					break;
				}
				
				if (fast->next) fast = fast->next->next;
				else break;

				slow = slow->next;
			}

			if (hasCycle)
			{
				ListNode *head1 = head;
				ListNode *head2 = slow->next;

				while (1)
				{
					if (head1 == head2)
					{
						res = head1;
						break;
					}

					head1 = head1->next;
					head2 = head2->next;
				}
			}

			return res;
		}

		bool hasCycle(ListNode *head) {
			if (! head || ! head->next) return false;
			
			ListNode *slow = head;
			ListNode *fast = head->next;

			while (fast)
			{
				if (fast == slow) return true;
				
				if (fast->next) fast = fast->next->next;
				else break;

				slow = slow->next;
			}

			return false;
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
