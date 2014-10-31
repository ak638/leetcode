#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <string.h>

using namespace std;


class Solution {
	public:
		int findMin(vector<int> &num) {
			int min = 0;
			int max = (int)num.size() - 1;
			int mid = 0;

			while (min < max)
			{
				mid = min + (max-min)/2;

				//if (num[max] < num[mid] && num[min] < num[mid]) //top in the middle
				if (num[max] < num[mid]) //top in the middle
				{
					min = mid + 1;
				}
				else if (num[max] > num[mid])
				{
					max = mid;
				}
			}

			return num[min];
		}
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution  poSolution;

	vector<int> num;
	int tcnum = 0;
	scanf("%d", &tcnum);

	int testnum = 0;
	int singlenum = 0;
	int res = 0;

	while (tcnum--)
	{
		num.clear();

		scanf("%d", &testnum);
		while (testnum--)
		{
			scanf("%d", &singlenum);
			num.push_back(singlenum);	
		}

		res = poSolution.findMin(num);
		printf("RES: %d\n", res);
	}

	return 0;
}
