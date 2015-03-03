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
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */

struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
	public:
		RandomListNode *copyRandomList(RandomListNode *head) {
			if (! head) return NULL;

			RandomListNode *newHead = NULL;
			RandomListNode **newCur = &newHead;
			
			//use unordered_map as hash_map better!
			map<RandomListNode *, int> mapAddr2Idx;
			vector<RandomListNode *> vecNewIdx2Addr;

			int cnt = 0;
			RandomListNode *oldCur = head;
			while (oldCur)
			{
				*newCur = new RandomListNode(oldCur->label);

				mapAddr2Idx[oldCur] = cnt;
				vecNewIdx2Addr.push_back(*newCur);

				cnt += 1;
				newCur = &(*newCur)->next;
				oldCur = oldCur->next;
			}

			int idx = 0;
			oldCur = head;
			newCur = &newHead;
			while (oldCur)
			{
				if (oldCur->random)
				{
					idx = mapAddr2Idx[oldCur->random];
					(*newCur)->random = vecNewIdx2Addr[idx];	
				}
				
				newCur = &(*newCur)->next;
				oldCur = oldCur->next;
			}

			return newHead;
		}
};

using namespace std;

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution poSolution;
	poSolution.copyRandomList(NULL);

	int testcase = 0;
	scanf("%d", &testcase);

	while (testcase--)
	{

	}

	return 0;
}
