#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <set>
//#include <unordered_set>
#include <map>
#include <bitset>
//#include <unordered_map>
//#include "unordered_set"
//#include "unordered_map"
#include <string.h>
#include <cmath>

//https://leetcode.com/problems/maximum-gap/

using namespace std;

class Solution {
	public:
		int maximumGap(vector<int> &num)
		{
			//bucket sort
			int n = (int)num.size();
			if (n < 2) return 0;

			int iMax = num[0];
			int iMin = num[0];
			for (int i = 0; i < n; ++i)
			{
				iMax = max(iMax, num[i]);
				iMin = min(iMin, num[i]);
			}

			//利用一个特性，免除在bucket里面进行sort
			//这样就可以不用存同一个bucket里面的元素，只需要记录bucket的最大和最小值就可以
			//准确来说应该是(只有n-1个间隔)：
			//max_gap的low bound应该为low_bound = (iMax - iMin) / (n - 1) + ((iMax - iMin) % (n - 1) ? 1 : 0);
			//low_bound >= old_iInterval，所以用old_iInterval作为max_gap的最小值是没问题的！
			//int old_iInterval = 1 + (iMax - iMin) / n; //桶中元素的max_gap，必定小于等于全部元素的max_gap的最小值, safe!
			int iInterval = (iMax - iMin) / (n - 1) + ((iMax - iMin) % (n - 1) ? 1 : 0);
			vector<int> vecMin(n, INT_MAX);
			vector<int> vecMax(n, -1);

			int max_gap = iInterval;

			for (int i = 0; i < n; ++i)
			{
				int idx = (num[i] - iMin) / iInterval;
				vecMin[idx] = min(num[i], vecMin[idx]);
				vecMax[idx] = max(num[i], vecMax[idx]);
			}

			int last_max = -1;
			for (int i = 0; i < n; ++i)
			{
				//cmp last max with this min
				//可能中间有些bucket是空的，需要跳过
				if (vecMin[i] == INT_MAX) continue;
				if (last_max == -1) last_max = vecMax[i];
				
				max_gap = max(max_gap, vecMin[i] - last_max);
				last_max = vecMax[i];
			}
			
			return max_gap;
		}
		
		int maximumGap_v1(vector<int> &num)
		{
			//bucket sort
			int n = (int)num.size();
			if (n < 2) return 0;

			int iMax = num[0];
			int iMin = num[0];
			for (int i = 0; i < n; ++i)
			{
				iMax = max(iMax, num[i]);
				iMin = min(iMin, num[i]);
			}

			int iBkSize = n;
			int iInterval = (iMax - iMin) / iBkSize + 1; //each bucket range size

			vector<vector<int> > vecBucket(iBkSize, vector<int>());

			for (int i = 0; i < n; ++i)
			{
				vecBucket[(num[i]-iMin)	/ iInterval].push_back(num[i]);
			}

			int last_num = -1;
			int max_gap = 0;
			//sort each bucket
			for (int i = 0; i < iBkSize; ++i)
			{
				sort(vecBucket[i].begin(), vecBucket[i].end());
				
				for (int j = 0; j < vecBucket[i].size(); ++j)
				{
					if (last_num == -1) last_num = vecBucket[i][j];

					max_gap = max(max_gap, vecBucket[i][j] - last_num);
					last_num = vecBucket[i][j];
				}

			}
			
			return max_gap;
		}

};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	//freopen("./tmp2.txt", "r", stdin);
	Solution poSolution;

	int testcase = 0;
	scanf("%d", &testcase);

	while (testcase--)
	{
		int n;
		scanf("%d", &n);
		//printf("nnnn %d\n", n);
		vector<int> num;
		while (n--)
		{
			int a;
			scanf("%d", &a);
			num.push_back(a);
			//printf("asdf%d %d\n", a, num[num.size()-1]);
		}
		//printf("len %u\n", num.size());

		int res = poSolution.maximumGap(num);
		printf("RES: %d\n", res);
	}

	return 0;
}

/*
5
6
1 199 189 3 4 2
6 
100 4 200 1 3 2
3
1000 1 100000
10
1 2 3 5 2 1 5 6 2 4
2
1 10000000
*/
