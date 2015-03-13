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
