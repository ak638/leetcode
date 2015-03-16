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

//https://leetcode.com/problems/palindrome-partitioning/

using namespace std;

class Solution {
	public:
		int minCut(string s) {
			/*
			 * https://leetcode.com/problems/palindrome-partitioning-ii/
			 * 判断是否回文，两种思路：1.枚举每个字串，再判断字串是否为回文；2.迭代判断，字串a是回文，前后再包装同一个字符，那么新的字串xax也是回文，记录下来后面使用
			 */
			int n = (int)s.size();
			if (n <= 1) return 0;

			bool bPalin[n+1][n+1]; //bPalin[i][j]表示s[i, j-1]为回文
			memset(bPalin, 0, sizeof(bool) * (n+1) * (n+1));

			int dp[n+1]; //res[i]表示s[0...i-1]子串最小cut
			for (int i = 0; i <= n; ++i) dp[i] = i - 1; //初始化为每个子串最大可能的cut数
			//dp[0] = -1! 解决dp[1] = dp[0] + 1的问题

			for (int i = 2; i <= n; ++i)
			{
				for (int j = i-1; j >= 0; --j)
				{
					//s[j, i]
					if (s[i-1] == s[j] && (i - j <= 2 || bPalin[j+1][i-1]))
					{
						bPalin[j][i] = true;
						dp[i] = min(dp[i], dp[j]+1); //s[0,j-1]最小割次数+s[j,i-1]回文次数1
					}
				}
			}

			return dp[n];
		}
		
		vector<vector<string> > partition(string s) {
			vector<vector<string> > res;
			vector<string> single;

			dfs(s, 0, res, single);

			return res;
		}

		void dfs(string &s, size_t start, vector<vector<string> > &res, vector<string> &single)
		{
			if (start >= s.size())
			{
				res.push_back(single);
				return;
			}

			//get next ch, which is the same as s[start]
			size_t end = start;
			for ( ; end < s.size(); end++)
			{
				if (s[start] == s[end] && isPalindrome(s, start, end)) 
				{
					string sPal = string(s, start, end-start+1);
					single.push_back(sPal);

					dfs(s, end+1, res, single);
					
					//restore
					single.pop_back();
				}
			}
		}

		bool isPalindrome(string &s, int i, int j)
		{
			//[start, end]
			while (i < j)
			{
				if (s[i] == s[j])
				{
					i++; j--;
				}
				else return false;
			}

			return true;
		}
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution poSolution;

	int testcase = 0;
	scanf("%d", &testcase);
	char str[128];
	getchar();

	while (testcase--)
	{
		gets(str);

		vector<vector<string> > res = poSolution.partition(str);
		printf("======RES for [%s]\n", str);
		for (size_t i = 0; i < res.size(); ++i)
		{
			for (size_t j = 0; j < res[i].size(); ++j)
			{
				printf("%s ", res[i][j].c_str());
			}
			printf("\n");
		}
	}

	return 0;
}
