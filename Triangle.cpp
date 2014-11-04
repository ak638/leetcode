#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

//https://oj.leetcode.com/problems/triangle/

class Solution {
	public:
		void showData(vector<vector<int> > &triangle)
		{
			int n = (int)triangle.size();
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j <= i; ++j)
				{
					printf("%d\t", triangle[i][j]);
				}
				printf("\n");
			}
		}

		int minimumTotal(vector<vector<int> > &triangle) {
			int n = (int)triangle.size();

			int *arr = new int[n];
			memset(arr, 0, sizeof(int) * n);

			int tmp = 0;
			//arr[i, j] = min{arr[i-1, j-1], arr[i-1, j]} + T[i, j]
			for (int i = 0; i < n; ++i)
			{
				for (int j = i; j >=0; --j)
				{
					if (j != i) 
					{
						tmp = arr[j]; 
						if (j - 1 >= 0 && arr[j-1] < tmp) tmp = arr[j-1];
					}
					else
					{//当前行最后一个的上面位置的值是无意义的
						if (j - 1 >= 0) tmp = arr[j-1];
					}

					arr[j] = tmp + triangle[i][j];

					//printf("%d\t", arr[j]);
				}
				//printf("\n");
			}

			int res = arr[0];
			for (int i = 1; i < n; ++i)
			{
				if (arr[i] < res) res = arr[i];
			}

			delete[] arr;

			return res;
		}
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution  poSolution;

	int testcase = 0;
	scanf("%d", &testcase);

	while (testcase--)
	{
		int layer = 0;
		scanf("%d", &layer);

		vector<vector<int> > data;
		
		//while (layer--)
		for (int j = 0; j < layer; ++j)
		{
			vector<int> vec;
			for (int i = 0; i <= j; ++i)
			{
				int tmp;
				scanf("%d", &tmp);
				vec.push_back(tmp);
			}
			data.push_back(vec);
		}

		int res = poSolution.minimumTotal(data);
		printf("RES: %d\n\n", res);
	}

	return 0;
}
