#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

class Solution {
	public:
		void reverseWords(string &s)
		{
			//以单词为中心，不管空格，只需要在单词之间加上一个空格就行
			string newstr;
			int len = (int)s.size();
			int end =  len;
			
			for (int i = len-1; i >= 0; --i)
			{
				if (s[i] == ' ')
				{
					end = i;
				}
				else if (i == 0 || s[i-1] == ' ') //侦测到当前应该开始计算word
				{
					if (newstr.size() != 0) newstr += ' ';
					for (int j = i; j < end; ++j) newstr += s[j];
				}
			}

			s = newstr;
		}

		//complicated one solution
		void reverseWords_1(string &s) {
			string newstr = "";

			int len = (int)s.size();

			int beg = len - 1;
			int end = 0;

			bool last_is_space = false;
			bool leading_space = true;

			for (int i = len-1; i >= 0; --i)
			{
				//filter leading spaces
				if (leading_space && s[i] == ' ')
				{
					beg = i - 1;
					continue;
				}	
				leading_space = false;

				if (s[i] == ' ')
				{
					if (last_is_space) 
					{
						//reset beg if current is still space
						beg = i - 1;
						continue;
					}
					last_is_space = true;
					
					end = i;

					//[beg, end) should add reversed
					for (int j = end+1; j <= beg; ++j) newstr += s[j];

					//reset
					beg = i - 1;
				}
				else
				{
					if (last_is_space) //should add one space
					{
						newstr += ' ';
						beg = i;
						last_is_space = false;
					}
				}
			}

			//patch the tailing word
			for (int j = 0; j <= beg; ++j) newstr += s[j];
			
			s = newstr;
		}
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution  poSolution;

	int testcase = 0;
	scanf("%d", &testcase);
	getchar();

	string s;
	char arr[512];

	while (testcase--)
	{
		gets(arr);
		s = arr;
		poSolution.reverseWords(s);
		printf("[%s]->[%s]\n", arr, s.c_str());
	}

	return 0;
}

/*
4
the sky is blue
   the sky is a kind of what
 
    hello    world  yes
*/
