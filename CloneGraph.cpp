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

//https://leetcode.com/problems/clone-graph/

struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {};
};


class Solution {
	public:
		UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
			if (! node) return NULL;
			//bfs
			queue<UndirectedGraphNode *> q;
			vector<UndirectedGraphNode *> vecNewNode;
			map<int, int> mapOldNode2Idx;
			int iNodeCnt = 0;

			//init
			UndirectedGraphNode *newGraph = new UndirectedGraphNode(node->label);
			vecNewNode.push_back(newGraph);
			mapOldNode2Idx[node->label] = iNodeCnt;
			iNodeCnt += 1;

			q.push(node);

			//注意当前node的neighbors可以相同，不重复加到queue
			while (! q.empty())
			{
				UndirectedGraphNode *cur = q.front();
				q.pop();

				UndirectedGraphNode *newCur = vecNewNode[mapOldNode2Idx[cur->label]];
				for (int i = 0 ; i < cur->neighbors.size(); ++i)
				{
					UndirectedGraphNode *tarNode = cur->neighbors[i];

					UndirectedGraphNode *tmp = NULL;

					//in case of double-visit or double-add to queue
					bool bVisited = mapOldNode2Idx.end() != mapOldNode2Idx.find(tarNode->label);

					//has added some cur's ibling[4, 5, 5] or been visited
					if (bVisited) tmp = vecNewNode[mapOldNode2Idx[tarNode->label]];
					else tmp = new UndirectedGraphNode(tarNode->label);

					//set neighbors
					newCur->neighbors.push_back(tmp);

					if (bVisited) continue;

					vecNewNode.push_back(tmp);
					mapOldNode2Idx[tarNode->label] = iNodeCnt;
					iNodeCnt += 1;

					q.push(tarNode);
				}
			}

			return newGraph;
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
