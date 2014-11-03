#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

class Solution {
	public:
		void genSolution(vector<vector<string> > &rec, vector<int> &bt_state, int n)
		{
			vector<string> one;
			string line;
			for (int i = 0; i < n; ++i)
			{
				line = "";
				for (int j = 0; j < n; ++j)
				{
					line += bt_state[i] == j ? "Q" : ".";
				}
				one.push_back(line);

				printf("%s\n", line.c_str());
			}
			printf("\n");

			rec.push_back(one);
		}

		vector<vector<string> > solveNQueens(int n) {
			vector<vector<string> > res;

			int *occupy_y = new int[n];
			memset(occupy_y, 0, sizeof(int) * n);

			int m = 2 * n - 1;
			int *occupy_lc = new int[m]; //left cross \
			//memset(occupy_lc, 0, sizeof(int) * n);
			memset(occupy_lc, 0, sizeof(int) * m);
			int *occupy_rc = new int[m]; //right cross /
			memset(occupy_rc, 0, sizeof(int) * m);

			//lc_idx = n-1-(x-y);
			//rc_idx = x+y;

			vector<int> bt_state;

			//do backtrack to looking for solution
			bt_state.push_back(0); //push (0, 0)
			occupy_y[0] = 1;
			occupy_lc[n-1-(0-0)] = 1;
			occupy_rc[0+0] = 1;

			int y = 0;
			int x = 0;
			bool line_ok = false;

			do
			{
				if (n == (int)bt_state.size()) //find one
				{
					genSolution(res, bt_state, n);
				}

				x = (int)bt_state.size();
				line_ok = false;
				for ( ; y < n; ++y)
				{
					if (occupy_y[y] == 0 && occupy_lc[n-1-(x-y)] == 0 && occupy_rc[x+y] == 0) //valid
					{
						//set state
						occupy_y[y] = 1;
						occupy_lc[n-1-(x-y)] = 1;
						occupy_rc[x+y] = 1;

						bt_state.push_back(y);
						line_ok = true;
						break;
					}
				}

				if (line_ok)
				{
					//move to next line
					y = 0;
				}
				else
				{
					//should backtrack
					y = bt_state.back();
					bt_state.pop_back();
					x = (int)bt_state.size();

					//reset state
					occupy_y[y] = 0;
					occupy_lc[n-1-(x-y)] = 0;
					occupy_rc[x+y] = 0;

					//move to next pos of the same line
					y++;
				}

				//printf("%d %d\n", x, y);

			} while (!bt_state.empty() || y < n);

			delete[] occupy_y;
			delete[] occupy_lc;
			delete[] occupy_rc;

			//printf("#solution: %d\n", res.size());
			
			return res;
		}
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution  poSolution;
	
	poSolution.solveNQueens(atoi(argv[1]));

	return 0;
}
