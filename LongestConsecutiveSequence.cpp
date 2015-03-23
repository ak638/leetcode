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


using namespace std;

class Solution {
	public:
		int longestConsecutive_v2(vector<int> &num)
		{
			//跟longestConsecutive想法类似，但是段不是靠段头和段尾去维持，而是段的每一个位置都用整个段长度表示，
			//其实就也是利用到段头和段尾而已，中间不用维护
			int size = (int)num.size();
			if (size <=1 ) return size;

			int res = 1;
			//unordered_map<int, int> mapOcc;
			//unordered_map<int, int>::iterator mit, mpreit, mpostit;
			map<int, int> mapOcc; //记录所在连续段的长度
			//map<int, int>::iterator mit, mpreit, mpostit;

			for (int i = 0; i < size; ++i)
			{
				int cur = num[i];
				if (mapOcc.find(cur) != mapOcc.end()) continue;

				int left = cur == INT_MIN ? 0 : mapOcc.find(cur-1) == mapOcc.end() ? 0 : mapOcc[cur-1];
				int right = cur == INT_MAX ? 0 : mapOcc.find(cur+1) == mapOcc.end() ? 0 : mapOcc[cur+1];

				//合并连续段，0相当于没有连续段，一致对待
				int sum = left + 1 + right;
				mapOcc[cur] = sum;
				res = max(res, sum);

				//只需要更新连续段的头和尾就行
				if (left != 0) mapOcc[cur-left] = sum;
				if (right != 0) mapOcc[cur+right] = sum;
			}

			return res;
		}
		int longestConsecutive(vector<int> &num)
		{
			//注意边上只有一个节点，那么节点上原来的值需要先保存到临时变量！
			int size = (int)num.size();
			if (size <=1 ) return size;

			int res = 1;

			//unordered_map<int, int> mapOcc;
			//unordered_map<int, int>::iterator mit, mpreit, mpostit;
			map<int, int> mapOcc;
			map<int, int>::iterator mit, mpreit, mpostit;

			for (int i = 0; i < size; ++i)
			{
				int cur = num[i];	

				mit = mapOcc.find(cur);
				if (mit != mapOcc.end()) continue;

				mpreit = cur == INT_MIN ? mapOcc.end() : mapOcc.find(cur-1); //看cur是否为当前连续段的起点
				mpostit = cur == INT_MAX ? mapOcc.end() : mapOcc.find(cur+1); //看后面是否还有连续段需要合并

				if (mpreit == mapOcc.end() && mpostit != mapOcc.end()) // [empty(n), cur, (consecutive seg...)]
				{
					//[cur, 3, 4, 5, 6]
					//cur要作为当前连续段的起点
					//只需要更新新的起点以及当前段的最后一个节点就ok了
					int tmp = mpostit->second;
					mapOcc[cur] = mpostit->second + 1; 
					mapOcc[cur+mpostit->second]++; 

					if (res < mapOcc[cur+tmp]) res = mapOcc[cur+tmp];
				}
				else if (mpreit != mapOcc.end() && mpostit == mapOcc.end())
				{
					//[1, 2, 3, cur]
					//cur最为当前连续段的末尾
					mapOcc[cur] = mpreit->second + 1; //先更新末端
					mapOcc[cur-mpreit->second]++;

					if (res < mapOcc[cur]) res = mapOcc[cur];
				}
				else if (mpreit != mapOcc.end() && mpostit != mapOcc.end())
				{
					//[1, 2, 3, cur, 5, 6, 7]
					//cur处在两个连续段中间，需要将两个段合并起来
					int tmp = mpostit->second;
					int tmp2 = mpreit->second;
					mapOcc[cur+tmp] += 1 + tmp2; //先更新末端
					mapOcc[cur-tmp2] += 1 + tmp;
					mapOcc[cur] = 1 + tmp2; //当前节点可以随便填

					if (res < mapOcc[cur+tmp]) res = mapOcc[cur+tmp];
				}
				else
				{
					//[cur]
					mapOcc[cur] = 1;
				}
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

		int res = poSolution.longestConsecutive(num);
		printf("RES: %d\n", res);
	}

	return 0;
}

/*
 * 
5
6
1 199 189 3 4 2
6 
100 4 200 1 3 2
7
-2147483648 2147483647 2147483646 1 3  5 6
7
1 3 2 7 6 5 4
2
0 -1
 *
 */
