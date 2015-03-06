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
//https://oj.leetcode.com/problems/gas-station/

class Solution {
	public:
		int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
			int res = -1;

			int n = (int)gas.size();
			vector<int> left(n, 0);

			for (int i = 0; i < n; ++i)
			{
				left[i] = gas[i] - cost[i];
			}

			int i = 0;
			int j = 0;
			int sum = 0;

			bool bFinished = false;

			//i往后走，j往前走，当j走不动，i才走，如果最终的sum非负数，则i为起点
			while (1)
			{
				//move j forwards
				do
				{
					sum += left[j];
					j = (j + 1) % n; //j move after sum add
					if (j == i)
					{
						bFinished = true;
						break;
					}
				}while (sum >= 0);

				//move i backwards
				do
				{
					if (bFinished) break;

					i = (i - 1 + n) % n; //i move before sum add
					sum += left[i];
					if (j == i)
					{
						bFinished = true;
						break;
					}
				} while (sum < 0);

				//check finished
				if (bFinished) 
				{
					if (sum >= 0) res = i;
					break;
				}
			}
			
			return res;
		}

		int canCompleteCircuit_v2(vector<int> &gas, vector<int> &cost) {
			//accepted!
			int res = -1;
			int n = (int)gas.size();

			int cur = 0;
			int start = 0;
			int sum = 0;
			int prestart = 0;

			//单向迭代，基于走过的不行的路径，都不可能为起点
			while (1)
			{
				sum = 0;
				for (int i = 0; i < n; ++i)
				{
					cur = (start + i) % n;
					sum += gas[cur] - cost[cur];
					if (sum < 0) break;
				}
				
				if (sum >= 0) {res = start; break;}
				prestart = start;
				start = (cur + 1) % n; //接着从当前的下个station开始作为起点
				if (start <= prestart) break; //如果start又跨过了0起点，意味着所有的节点都试过了
			}

			return res;
		}
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution poSolution;
	
	vector<int> gas;
	gas.push_back(1);
	gas.push_back(2);
	vector<int> cost;
	cost.push_back(2);
	cost.push_back(1);

	int res = poSolution.canCompleteCircuit(gas, cost);
	printf("RES: %d\n", res);

	return 0;

	int testcase = 0;
	scanf("%d", &testcase);

	while (testcase--)
	{

	}

	return 0;
}
