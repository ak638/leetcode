#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <string.h>

using namespace std;

class Solution {
	public:
		int calValue(int lt, int rt, string &opt)
		{
			if (opt == "+") return lt + rt;
			else if (opt == "-") return lt - rt;
			else if (opt == "*") return lt * rt;
			else return lt / rt;
		}

		//从左往右进行计算，如果遇到操作符，把操作数栈的两个数取出来运算再放回去ȥ
		int evalRPN(vector<string> &tokens) {
			stack<int> st_int;
			int lt, rt;

			for (int i = 0; i < tokens.size(); ++i)
			{
				if (tokens[i] == "+" ||
						tokens[i] == "-" ||
						tokens[i] == "*" ||
						tokens[i] == "/" ||
						0)
				{
					rt = st_int.top();
					st_int.pop();
					
					lt = st_int.top();
					st_int.pop();

					st_int.push(calValue(lt, rt, tokens[i]));
				}
				else
				{
					st_int.push(atoi(tokens[i].c_str()));
				}
			}

			return st_int.top();
		}

		void calTilEmpty(stack<string> &st, stack<int> &st_int)
		{
			string opt;
			int lt, rt;

			while (! st.empty() && st_int.size() >= 2u)
			{
				opt = st.top();
				st.pop();

				lt = st_int.top();
				st_int.pop();

				rt = st_int.top();
				st_int.pop();

				//printf("CAL: %d %s %d\n", lt, opt.c_str(), rt);
				st_int.push(calValue(lt, rt, opt));
			}
		}

		//从右到左进行计算，操作符和操作数都要入栈！á
		//runtime error
		int evalRPN_1(vector<string> &tokens) {
			stack<string> st;
			stack<int> st_int;

			int last_is_int = false;

			for (int i = tokens.size()-1; i >= 0; --i)
			{
				if (tokens[i] == "+" ||
						tokens[i] == "-" ||
						tokens[i] == "*" ||
						tokens[i] == "/" ||
						0)
				{
					st.push(tokens[i]);
					last_is_int = false;
				}
				else
				{
					st_int.push(atoi(tokens[i].c_str()));

					if (last_is_int) calTilEmpty(st, st_int);
					last_is_int = true;
				}
			}

			//cal the rest
			calTilEmpty(st, st_int);
		
			return st_int.top();
		}
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution  poSolution;

	int testcase = 0;
	scanf("%d", &testcase);

	int num;
	char arr[10];

	while (testcase--)
	{
		scanf("%d", &num);
		getchar();

		vector<string> vec;
		while (num--)
		{
			gets(arr);
			vec.push_back(arr);
		}

		int res = poSolution.evalRPN(vec);
		printf("RES: %d\n", res);
		
	}

	return 0;
}
