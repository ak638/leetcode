#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string.h>
#include <cmath>

using namespace std;

class Solution {
	public:
		vector<string> wordBreakII(string s, unordered_set<string> &dict) {
			vector<string> res;
			vector<vector<unordered_set<string>::iterator> > record;
			
			/*
			printf("%s\n", s.c_str());
			for (unordered_set<string>::iterator usit = dict.begin(); usit != dict.end(); ++usit)
			{
				printf("%s\n", usit->c_str());
			}
			*/

			int len = (int)s.size();
			int *st = new int[len+1];
			memset(st, 0, sizeof(int) * (len+1));
			st[0] = 1;
			for (int i = 0; i <= len; ++i) record.push_back(vector<unordered_set<string>::iterator>());
			unordered_set<string>::iterator usit = dict.begin();

			for (int i = 1; i <= len; ++i)
			{
				for (usit = dict.begin(); usit != dict.end(); ++usit)
				{
					int cur_len = (int)usit->size();
					int dis = i - cur_len;
					if (dis < 0) continue; //too short, impossible
					const char *start = s.c_str() + dis;

					if (st[dis] == 1 && strncmp(start, usit->c_str(), cur_len) == 0)
					{
						st[i] = 1;
						record[i].push_back(usit);
					}
				}
			}

			//debug
			/*
			for (size_t i = 1; i < record.size(); ++i)
			{
				printf("%lu ==> ", i);
				for (size_t j = 0; j < record[i].size(); j++) printf("%s ", record[i][j]->c_str());
				printf("\n");
			}
			printf("\n");
			*/

			//construct paths
			if (st[len] == 1) constructSolutions(record, res, (int)record.size()-1, "");
			//if (st[len] == 1) printf("YES!\n");

			return res;
		}

		void constructSolutions(vector<vector<unordered_set<string>::iterator> > &record, vector<string> &res, int idx, string str)
		{
			//printf("DEBUG: %d [%s]\n", idx, str.c_str());

			if (idx <= 0)
			{
				res.push_back(str);
				//printf("#####got[%s]\n", str.c_str());
				return;
			}

			string strbak = str;
			if (strbak.size() != 0u) strbak = " " + strbak;

			for (size_t i = 0; i < record[idx].size(); ++i)
			{
				str = strbak;
				str = record[idx][i]->c_str() + str;
				constructSolutions(record, res, idx-(int)record[idx][i]->size(), str);
			}
		}

		bool wordBreak(string s, unordered_set<string> &dict) {
			int len = (int)s.size();
			int *st = new int[len+1];

			/*
			printf("%s\n", s.c_str());
			for (unordered_set<string>::iterator usit = dict.begin(); usit != dict.end(); ++usit)
			{
				printf("%s\n", usit->c_str());
			}
			*/	

			memset(st, 0, sizeof(int) * (len+1));
			st[0] = 1;
			unordered_set<string>::iterator usit = dict.begin();

			for (int i = 1; i <= len; ++i)
			{
				for (usit = dict.begin(); usit != dict.end(); ++usit)
				{
					int cur_len = (int)usit->size();
					int dis = i - cur_len;
					if (dis < 0) continue; //too short, impossible
					const char *start = s.c_str() + dis;

					if (st[dis] == 1 && strncmp(start, usit->c_str(), cur_len) == 0)
					{
						st[i] = 1;
						break;
					}
				}
			}

			bool res = st[len] == 1;
			delete[] st;
			return res;
		}

		void showState(int *arr, int len)
		{
			for (int i = 0; i < len; ++i)
			{
				printf("%d ", arr[i]);
			}
			printf("\n");
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
		char src[128];
		char tmp[128];
		int n;
		string s;
		unordered_set<string> dict;

		scanf("%d", &n);
		getchar();
		gets(src);
		s = src;
		while (n--)
		{
			gets(tmp);
			dict.insert(tmp);
		}
		
		//bool res = poSolution.wordBreak(s, dict);
		//printf("==RES: %d\n", res);
		vector<string> res = poSolution.wordBreakII(s, dict);
		for (size_t i = 0; i < res.size(); ++i)
		{
			printf("RES: %s\n", res[i].c_str());
		}
		printf("==================\n");
	}

	return 0;
}

/*
5
2
leetcode
leet
code
4
leetcode
le
ee
et
e
3
leetcode
leet
etcod
e
1
a
a
5
catsanddog
cat
cats
and
sand
dog
*/
