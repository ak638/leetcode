#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

//https://oj.leetcode.com/problems/spiral-matrix-ii/

class Solution {
	public:
		enum {DIR_RIGHT = 0, DIR_DOWN, DIR_LEFT, DIR_UP, DIR_COUNT};

		void getPosByThisDirection(int x, int y, int &new_x, int &new_y, int dir)
		{
			switch (dir)
			{
				case DIR_RIGHT:
					new_x = x;
					new_y = y + 1;
					break;
				case DIR_DOWN:
					new_x = x + 1;
					new_y = y;
					break;
				case DIR_LEFT:
					new_x = x;
					new_y = y - 1;
					break;
				case DIR_UP:
					new_x = x - 1;
					new_y = y;
					break;
			}
		}

		bool isPosValid(int x, int y, int n)
		{
			return (x >= 0 && x < n && y >= 0 && y < n);
		}

		int getNextPos(vector<vector<int> > &vecData, int n, int &x, int &y, int &dir)
		{
			int new_x = 0;
			int new_y = 0;
			
			for (int i = 0; i < 2; ++i)
			{
				dir = (dir + i) % DIR_COUNT;

				//try get next pos with current direction
				getPosByThisDirection(x, y, new_x, new_y, dir);
				//printf("%d->%d %d->%d %d\n", x, new_x, y, new_y, dir);
				//if (isPosValid(new_x, new_y, n)) printf("data[%d][%d] = %d\n", new_x, new_y, vecData[new_x][new_y]);

				if (isPosValid(new_x, new_y, n) && vecData[new_x][new_y] == 0)
				{
					//this pos is OK
					x = new_x;
					y = new_y;
					return 0;
				}
			}
			
			return 1;
		}

		vector<vector<int> > generateMatrix(int n) {
			vector<vector<int> > vecData(n);
			for (size_t i = 0; i < n; ++i)
			{
				vecData[i] = vector<int>(n, 0);
				//for (size_t j = 0; j < n; ++j) vecData[i].push_back(0);
			}

			int x = 0;
			int y = -1;
			int dir = DIR_RIGHT;
			for (int num = 1; num <= n * n; ++num)
			{
				getNextPos(vecData, n, x, y, dir);	
				vecData[x][y] = num;
			}

			return vecData;
		}

		void showData(vector<vector<int> > &vecData)
		{
			for (size_t i = 0; i < vecData.size(); ++i)
			{
				for (size_t j = 0; j < vecData.size(); ++j)
				{
					printf("%d\t", vecData[i][j]);
				}
				printf("\n");
			}
		}
};

int main(int argc, char *argv[])
{
	//freopen("./input.txt", "r", stdin);
	Solution  poSolution;

	int n = 0;
	scanf("%d", &n);
	vector<vector<int> > vecData = poSolution.generateMatrix(n);
	poSolution.showData(vecData);

	return 0;
}
