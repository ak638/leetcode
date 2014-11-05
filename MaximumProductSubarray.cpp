#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

/*
动态规划
https://oj.leetcode.com/problems/maximum-product-subarray/solution/
f(k) = max( f(k-1) * A[k], A[k], g(k-1) * A[k] )
g(k) = min( g(k-1) * A[k], A[k], f(k-1) * A[k] )
*/

class Solution {
	public:
		int calMaxSubA(int A[], int beg, int end)
		{
			if (beg == end)
			{
				return A[beg];
			}

			int res = 1;
			vector<int> data;
			//find <0 index [beg, end)
			for (int i = beg; i <= end; ++i)
			{
				if (A[i] < 0) data.push_back(i);
			}

			int odd_cnt = (int)data.size();
			if (odd_cnt % 2 == 0) //just product all
			{
				for (int i = beg; i <= end; ++i)
				{
					res *= A[i];
				}
			}
			else
			{
				//cmp two seg products
				int tmp1 = 1;
				int tmp2 = 1;

				for (int i = beg; i < data[odd_cnt-1]; ++i) tmp1 *= A[i];
				for (int i = data[0]+1; i <= end; ++i) tmp2 *= A[i];

				res = tmp1 > tmp2 ? tmp1 : tmp2;
			}

			return res;
		}

		int maxProduct(int A[], int n) {
			int beg = 0;
			int end = 0;
			int res = 0;
			bool first = true;

			for (int i = 0; i < n; ++i)
			{
				if (A[i] == 0 || i == n-1) //cal subA
				{
					if (A[i] == 0) end = i-1;
					else end = i;

					int tmp;
					if (beg > end) tmp = 0;
					else tmp = calMaxSubA(A, beg, end);

					if (first)
					{
						first = false;
						res = tmp;
					}
					else if (tmp > res) 
					{
						res = tmp;
					}

					if (A[i] == 0 && res < 0) res = 0;

					//reset
					beg = i + 1;
				}
			}
			
			return res;
		}

		//Memory Limit Exceeded
		int maxProduct_1(int A[], int n) {
			vector<vector<int> > data(n);
			for (int i = 0; i < n; ++i) data[i] = vector<int>(n, 1);

			int res = 0;

			for (int i = 0; i < n; ++i)
			{
				for (int j = i; j < n; ++j)
				{
					if (i == j) data[i][j] = A[j];
					else
					{
						data[i][j] = data[i][j-1] * A[j];
					}
				}
			}

			res = data[0][0];
			for (int i = 0; i < n; ++i)
			{
				for (int j = i; j < n; ++j)
				{
					if (res < data[i][j]) res = data[i][j];
				}
			}

			return res;
		}
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution  poSolution;

	int testcase;
	scanf("%d", &testcase);

	int arr[64];
	int n;

	while (testcase--)
	{
		scanf("%d", &n);	
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &arr[i]);
		}

		int res;
		if (argc >= 2)
		{
			printf("old...");
			res = poSolution.maxProduct_1(arr, n);
		}
		else
			res = poSolution.maxProduct(arr, n);
		printf("RES: %d\n", res);
	}

	return 0;
}

/*
9
4
2 3 -2 4
5
2 3 -2 4 -1
6
2 3 -2 4 -1 2
1
2
7
-1 2 3 0 -2 4 -1
8
1 -5 2 -1 2 3 -2 5
1
-2
3
-2 0 -1
1
0
 */
