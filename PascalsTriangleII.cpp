#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class Solution {
	public:
		void showData(vector<int> &vecData)
		{
			for (size_t i = 0; i < vecData.size(); ++i)
			{
				printf("%d\t", vecData[i]);
			}
			printf("\n");
		}

		void calLayer(vector<int> &vecData, int min, int max, int start, int step=1)
		{
			//printf("%d %d %d %d\n", min, max, start, step);
			int cur = start;
			int next = 0;
			while (cur <= max && cur >= min)
			{
				vecData[cur] = vecData[cur];
				next  = cur + step;
				if (next <= max && next >= min) vecData[cur] += vecData[next];

				cur  = next;
			}
		}

		vector<int> getRow(int rowIndex) {
			if (0 == rowIndex) return vector<int>(1, 1);

			int elemCnt = rowIndex + 1;
			vector<int> vecData(elemCnt);
			
			int left = 0;
			int right = 0;
			int leftOrRight = 0; // 0-left, 1-right

			//init
			int mid = elemCnt / 2;
			vecData[mid] = 1;
			left = mid;
			right = mid;
			if (elemCnt % 2 == 0) leftOrRight = 1; //right first	
		
			for (int i = 1; i <= rowIndex; ++i) //row0 has been inited first
			{
				if (leftOrRight == 1)
				{
					left = left-1;
					calLayer(vecData, left, right, left, 1); 
				}
				else
				{
					right = right+1;
					calLayer(vecData, left, right, right, -1);
				}

				leftOrRight = 1 - leftOrRight;

				//showData(vecData);		
			}	
			
			return vecData;
		}
};

int main(int argc, char *argv[])
{
	Solution poSolution;
	int rowIndex = atoi(argv[1]);
	vector<int> vecData = poSolution.getRow(rowIndex);
	poSolution.showData(vecData);

	return 0;
}
