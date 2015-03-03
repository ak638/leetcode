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
    
            vector<RandomListNode *> vecNewIdx2Addr;

            int cnt = 0;
            RandomListNode *oldCur = head;
            while (oldCur)
            {   
                *newCur = new RandomListNode(oldCur->label);

                (*newCur)->random = oldCur->random;
                oldCur->label = cnt;
                vecNewIdx2Addr.push_back(*newCur);

                cnt += 1;
                newCur = &(*newCur)->next;
                oldCur = oldCur->next;
            }   

            for (newCur = &newHead; *newCur; newCur = &(*newCur)->next)
            {   
                if ((*newCur)->random) (*newCur)->random = vecNewIdx2Addr[(*newCur)->random->label];
            }   

            //recover label
            cnt = 0;
            for (oldCur = head; oldCur; oldCur = oldCur->next, cnt++)
            {   
                oldCur->label = vecNewIdx2Addr[cnt]->label;
            }   

            return newHead;
        }   
};

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
