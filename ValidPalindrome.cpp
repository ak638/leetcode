#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

class Solution {
	public:
		int moveNext(const char *str, int min, int max, int iCur, int iStep=1)
		{
			while (iCur >= min && iCur <= max)
			{
				if ((str[iCur] >= 'a' && str[iCur] <= 'z') ||
						(str[iCur] >= 'A' && str[iCur] <= 'Z') ||
						(str[iCur] >= '0' && str[iCur] <= '9') ||
						0)
				{
					return iCur;
				}
				
				iCur += iStep;
			}
			
			return -1;
		}

		bool isPalindrome(string s) {
			if ("" == s) return true;
			
			int iLen = (int)s.size();
			int front = 0;
			int last = iLen-1;

			for ( ; front <= last; front++, last--)
			{
				front = moveNext(s.c_str(), front, last, front, 1);
				last = moveNext(s.c_str(), front, last, last, -1);

				if (-1 == front || last == -1) return true;

				//char c1 = s[front] >= 'a' && s[front] <='z' ? s[front] & (~0X20) : s[front];
				//char c2 = s[last] >= 'a' && s[last] <='z' ? s[last] & (~0X20) : s[last];
				char c1 = tolower(s[front]);
				char c2 = tolower(s[last]);

				if (c1 != c2) return false;
			}

			return true;
		}
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	//freopen("./output.txt", "w", stdout);

	Solution  poSolution;
	char str[512] = {'\0'};
	//while (EOF != scanf("%s", str))
	while (gets(str))
	{
		printf("[%s] ==> %d\n", str, poSolution.isPalindrome(str));
	}

	return 0;
}

/* Test Cases:
 man, a plan, a canal: Panama
 asbagrgrg



 a%&*b%$a
 */
