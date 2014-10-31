#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

class Solution
{
	public:
		int distinctNumWithOneArray(string src, string tar)
		{
			int src_len = (int)src.size();
			int tar_len = (int)tar.size();

			//alloc & init
			int *num = new int[src_len+1];
			memset(num, 0, src_len+1);
			//for (int i = 0; i <= src_len; ++i)
			//{
			//	num[i] = 0;
			//}

			//DP
			int record = 1; //保存左上角的值
			int tmp = 0; //新的值
			for (int i = 1; i <= tar_len; ++i)
			{
				for (int j = 1; j <= src_len; ++j)
				{
					if (tar[i-1] == src[j-1])
					{
						tmp = num[j-1] + record;
					}
					else
					{
						tmp = num[j-1];
					}

					record = num[j];
					num[j] = tmp;
				}
			}

			int result = num[src_len];

			//free
			delete[] num;

			return result;
		}

		int distinctNum(string src, string tar)
		{
			int src_len = (int)src.size();
			int tar_len = (int)tar.size();

			//alloc
			int **num = new int*[tar_len+1];
			for (int i = 0; i <= tar_len; ++i)
			{
				num[i] = new int[src_len+1];
				memset(num[i], 0, src_len+1);
			}	

			//DP
			//init
			for (int i = 0; i <= src_len; ++i)
			{
				num[0][i] = 1;
			}
			
			/*
			  S for source string(the longer one most of the time), T for target string
			  let A[i, j] is the number of distinct subsequences for T[0...i], S[0...j]
			  A[i, j] =	A[i, j-1], if T[i] != S[j]
						A[i, j-1] + A[i-1, j-1], if T[i] == S[j]
			  
			  如果T[i] != S[j]，很明显当前的S[j]用不上，结果跟A[i, j-1]一样；
			  如果T[i] == S[j]，那么分两种情况，如果使用S[j]去跟当前T[i]去匹配，那么，跟大家都少当前字符的结果是一样的；如果不使用，那么跟T[i]!=S[j]情况是一样的。所以是两者的结合
			  */
			int result = 0;

			for (int i = 1; i <= tar_len; ++i)
			{
				for (int j = 1; j <= src_len; ++j)
				{
					if (tar[i-1] == src[j-1])
					{
						num[i][j] = num[i][j-1] + num[i-1][j-1];
					}
					else
					{
						num[i][j] = num[i][j-1];
					}
				}
			}

			result = num[tar_len][src_len];

			//free
			for (int i = 0; i <= tar_len; ++i)
			{
				delete[] num[i], num[i] = NULL;
			}

			delete[] *num;

			return result;
		}
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution  poSolution;

	char src[128];
	char tar[128];

	int testcase = 0;
	scanf("%d", &testcase);
	getchar();

	while (testcase--)
	{
		gets(src);
		gets(tar);

		//int ret = poSolution.distinctNum(src, tar);
		int ret = poSolution.distinctNumWithOneArray(src, tar);
		printf("%d\n", ret);
	}

	return 0;
}

/*
 * test cases
2
rabbbit
rabbit
raabbbiat
rabbit
 */
