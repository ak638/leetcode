#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <unordered_map>
#include <string.h>
#include <cmath>

using namespace std;

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

class Solution {
	public:
		int maxPoints(vector<Point> &points) {
			/**
			 * 以每一个点为基点，计算斜率，hash存储好次数，不用考虑截距.
			 * 譬如以(a, b)为基点，考虑(a1, b1)和(a2, b2)，若(a2, b2)在(a, b)和(a1, b1)决定的直线上，那么(a, b)和(a2, b2)决定的直线的斜率和截距必然和前者一致，也就是只需要考虑斜率便可。
			 * 为了减少精度的损失，可以不考虑计算截距，而是直接计算a1-a和b1-b，但是这需要一致化这两个数值，否则判断不了一致
			 */
			if (points.size() <= 2u) return points.size();

			int iMaxPointCnt = 0;

			int iOverlapCnt = 0; //与基点重合的点个数
			int iBaseMaxPointCnt = 0; //以基点同一条直线的点个数
			unordered_map<long long, int> umap; //将a1-a和b1-b求GCD之后保存到map里面，统计出现次数，只需要统计同一个基点的结果就行

			for (size_t i = 0; i < points.size(); ++i)
			{
				Point &basePoint = points[i];
				
				//initialize
				umap.clear();
				iOverlapCnt = 0;
				iBaseMaxPointCnt = 0;

				for (size_t j = i+1; j < points.size(); ++j)
				{
					Point &endPoint = points[j];
					int xd = basePoint.x - endPoint.x;
					int yd = basePoint.y - endPoint.y;

					if (xd == 0 && yd == 0)
					{
						iOverlapCnt ++;
						continue;
					}

					int gcd = calGCD(xd, yd);
					printf("DEBUG: gcd(%d, %d) = %d\n", xd, yd, gcd);
					long long hashKey = xd / gcd;
					hashKey <<= 32;
					hashKey += yd / gcd;

					int cnt = ++umap[hashKey];
					//if (cnt > iBaseMaxPointCnt) iBaseMaxPointCnt = cnt;
					iBaseMaxPointCnt = max(iBaseMaxPointCnt, cnt);
				}

				iMaxPointCnt = max(iMaxPointCnt, iBaseMaxPointCnt+iOverlapCnt+1);
			}

			return iMaxPointCnt;
		}

		int calGCD(int x, int y)
		{
			int r = 0;

			while (0 != y)
			{
				r = x % y;
				x = y;
				y = r;
			}

			return x;
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
		int cnt = 0;
		scanf("%d", &cnt);

		vector<Point> points;
		Point tmp;
		while (cnt--)
		{
			scanf("%d %d", &tmp.x, &tmp.y);
			points.push_back(tmp);
		}

		int res = poSolution.maxPoints(points);
		printf("RES: %d\n", res);	
	}

	return 0;
}

/*
1
8
1 2
2 4
3 6
2 2
3 3
3 3
3 3
3 3
*/
