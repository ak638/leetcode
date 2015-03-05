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

//https://oj.leetcode.com/problems/candy/

using namespace std;

class Solution {
	public:
		int candy(vector<int> &ratings) {
			int max_cnt = (int)ratings.size();
			if (max_cnt == 0) return 0;
			
			//greedy algo.
			int res = 0;
			int cur = 0; //上一个小孩首次分配的candy数
			res += ++cur;
			int last_high_idx = 0; //记录最近最大rating的下标
			int last_high_val = cur; //记录最近最大rating下标首次分配的candy数

			for (int i = 1; i <= max_cnt; ++i)
			{
				if (i == max_cnt || ratings[i] >= ratings[i-1])
				{
					//summary last desc range
					int len = i - last_high_idx - 1;
					if (len > 0) //下降区间为[last_high_idx, i-1]
					{
						res += (1 + len) * len / 2; //为[last_high_idx+1, i-1]分配糖果
						if (len >= last_high_val) res += len - last_high_val + 1; //为last_high_idx补充糖果
						cur = 1; //区间末端最小为1
					}
					
					if (i < max_cnt) //如果非越界
					{
						if (ratings[i] > ratings[i-1]) res += ++cur;
						else res += cur = 1; //跟上一个小孩的rating一样，没有要求跟上一个一样的糖果，分配最小的数量1

						//刷新最大rating下标和其糖果数
						last_high_idx = i;
						last_high_val = cur;
					}
				}
				//积累rating下降区间
			}

			return res;
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
		int n;
		scanf("%d", &n);
		int a;
		vector<int> ratings;
		while (n--)
		{
			scanf("%d", &a);	
			ratings.push_back(a);
		}

		int res = poSolution.candy(ratings);
		printf("%d\n", res);
	}

	return 0;
}

/*
4
8
1 5 9 4 3 2 1 7
3
1 2 2 
5
4 2 3 4 1
5
4 2 1 1 2 
 */
