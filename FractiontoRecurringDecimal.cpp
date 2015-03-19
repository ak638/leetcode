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

//https://leetcode.com/problems/fraction-to-recurring-decimal/

class Solution {
	public:
		string fractionToDecimal(int numerator, int denominator) {
			int minus = 1;
			long long lnum = numerator;
			long long ldenom = denominator;
			if (numerator < 0)
			{
				minus *= -1;
				lnum= -lnum;
			}
			if (denominator < 0)
			{
				minus *= -1;
				ldenom = -ldenom;
			}

			long long int_part = lnum / ldenom;
			long long remainer = lnum % ldenom;

			string res;
			addIntToString(res, int_part);

			do
			{
				//别漏了负号！
				if (remainer == 0) break;

				res += ".";

				map<long long, size_t> mapReminder2Idx;
				string fra_part;
				long long fake_int_part;

				long long int nr = remainer;
				do
				{
					fake_int_part = (nr * 10) / ldenom;
					nr = (nr * 10) % ldenom;

					if (mapReminder2Idx.find(nr) != mapReminder2Idx.end()) //loop now
					{
						char tmp[8];
						snprintf(tmp, sizeof(tmp), "%lld", fake_int_part);
						//处理1/6和2/3的不同，1/6需要特殊处理下
						//余数虽然开始重复，但是对应的商不一致，这种情况下商的循环应该从第一次出现余数的商下一个位置开始
						if (tmp[0] != fra_part[mapReminder2Idx[nr]])
						{
							addIntToString(fra_part, fake_int_part);
							mapReminder2Idx[nr]++;
						}

						break;
					}

					addIntToString(fra_part, fake_int_part);
					mapReminder2Idx[nr] = fra_part.size()-1;

				} while (nr != 0);

				if (nr == 0) res += fra_part;
				else 
				{
					res += string(fra_part, 0, mapReminder2Idx[nr]-0);
					res += "(" + string(fra_part, mapReminder2Idx[nr]) + ")";
				}
			} while (0);

			if (minus == -1 && res != "0") res = "-" + res;

			return res;
		}

		void addIntToString(string &res, long long i)
		{
			char tmp[32] = {0};
			snprintf(tmp, sizeof(tmp), "%lld", i);
			res += tmp;
		}
};

int main(int argc, char *argv[])
{
	//freopen("./input.txt", "r", stdin);
	Solution poSolution;

	int testcase = 0;
	//scanf("%d", &testcase);

	//while (testcase--)
	while (true)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		string res = poSolution.fractionToDecimal(a, b);
		printf("RES: %s\n", res.c_str());
	}

	return 0;
}
