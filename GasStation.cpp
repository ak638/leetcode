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

		int canCompleteCircuit_v1(vector<int> &gas, vector<int> &cost) {
			//TLE!
			int res = -1;

			int n = (int)gas.size();
			vector<int> left(n, 0);

			for (int i = 0; i < n; ++i)
			{
				left[i] = gas[i] - cost[i];
			}

			bool bFound = false;
			int sum = 0;
			for (int i = 0; i < n; ++i)
			{
				bFound = true;
				sum = 0;
				for (int j = i, cnt = n; cnt > 0; j = (j+1) % n, cnt--)
				{
					sum += left[j];
					if (sum < 0) 
					{
						bFound = false;
						break;
					}
				}

				if (bFound)
				{
					res = i;
					break;
				}
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
