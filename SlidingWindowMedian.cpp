#include <stdio.h>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

// https://leetcode.com/problems/sliding-window-median/
class Solution
{
public:
	vector<double> medianSlidingWindow(vector<int>& nums, int k) {
		// 用map/set维护排序状态，取代线性的有序状态
		multiset<int> min_half;
		multiset<int> max_half;
		const int min_size = k / 2;
		const int max_size = k % 2 == 0 ? k/2 : k/2+1;
		const int all_size = nums.size();

		multiset<int>::iterator msit;

		// 初始化
		for (int i = 0; i < k; ++i)
		{
			min_half.insert(nums[i]);
		}
		for (int i = 0; i < max_size; ++i)
		{
			max_half.insert(*(min_half.rbegin()));
			// min_half.erase(min_half.rbegin());
			msit = min_half.end();
			--msit;
			min_half.erase(msit);
		}

		printf("min_size %zd max_size %zd\n", min_half.size(), max_half.size());

		vector<double> res;

		for (int i = 0; i <= all_size-k; ++i)
		{
			double tmp = *max_half.begin();
			if (min_size == max_size)
			{
				tmp += *(min_half.rbegin());
				tmp /= 2;
			}
			res.push_back(tmp);

			// adjust heap
			int to_remove = nums[i];
			int to_add = 0;
			if (i+k < all_size)
			{
				to_add = nums[i+k];
			}
			else
			{
				break;
			}

			// remove 
			if (min_half.size() == 0 || to_remove > *min_half.rbegin())
			{
				// multiset erase多个！
				// max_half.erase(to_remove);
				msit = max_half.find(to_remove);
				max_half.erase(msit);
			}
			else
			{
				// min_half.erase(to_remove);
				msit = min_half.find(to_remove);
				min_half.erase(msit);
			}

			// add
			if (min_half.size() == 0 || to_add > *min_half.rbegin())
			{
				max_half.insert(to_add);
			}
			else
			{
				min_half.insert(to_add);
			}


			// adjust two halves
			while (int(min_half.size()) > min_size)
			{
				max_half.insert(*min_half.rbegin());
				// min_half.erase(min_half.rbegin());
				msit = min_half.end();
				--msit;
				min_half.erase(msit);
			}
			while (int(max_half.size()) > max_size)
			{
				min_half.insert(*max_half.begin());
				max_half.erase(max_half.begin());
			}
			printf("round %d min_size %zd max_size %zd\n", i, min_half.size(), max_half.size());
		}

		return res;
	}

	vector<double> medianSlidingWindow_v1(vector<int>& nums, int k) {

		vector<double> res;
		int len = nums.size();

		std::list<int> slice(nums.begin(), nums.begin() + k);
		slice.sort();

		// for (std::list<int>::iterator it = slice.begin(); it != slice.end(); ++it)
		// {
		// 	printf("%d \n", *it);
		// }
		// printf("\n");

		int m1 = -1;
		int m2 = -1;
		if (k % 2 == 1)
		{
			m1 = k / 2;
		}
		else
		{
			// even
			m2 = k / 2;
			m1 = m2-1;
		}

		int left = 0;
		int next = 0;

		for (int s = 0; s <= len-k; ++s)
		{
			left = nums[s];
			next = 0;
			if (s+k < len) next = nums[s+k];

			// printf("round %d left %d next %d\n", s, left, next);

			std::list<int>::iterator lit = slice.begin();
			std::list<int>::iterator remove_pos = slice.end();
			std::list<int>::iterator insert_pos = slice.begin();

			double mean = 0.0;

			int pos = 0;
			while (lit != slice.end())
			{
				// printf("==> %d\n", *lit);
				if (*lit == left)
				{
					remove_pos = lit;
				}

				if (*lit < next)
				{
					insert_pos = lit;
					++insert_pos;
				}

				if (pos == m1)
				{
					mean += *lit;
				}
				else if (pos == m2)
				{
					mean += *lit;
					mean /= 2;
				}

				++lit;
				++pos;
			}

			// real slide
			// if (insert_pos != slice.end())
			{
				// printf("insert right \n");
				slice.insert(insert_pos, next);
			}
			if (remove_pos != slice.end())
			{
				// printf("erase left\n");
				slice.erase(remove_pos);
			}
			res.push_back(mean);

			// printf("slide size %zd\n", slice.size());
			// assert(slice.size() == k);
		}

		return res;
	}
};

int main(int argc, char* argv[])
{
	freopen("./input.txt", "r", stdin);

	int k = 0;
	vector<int> nums;

	scanf("%d", &k);
	int tmp;
	while (EOF != scanf("%d", &tmp) && tmp != -1111)
	{
		nums.push_back(tmp);
	}
	printf("size %zd\n", nums.size());

	Solution so;
	vector<double> res = so.medianSlidingWindow(nums, k);

	for (std::vector<double>::iterator it = res.begin(); it != res.end(); ++it)
	{
		printf("%lf \n", *it);
	}
	printf("\n");
	printf("res size %zd\n", res.size());

	return 0;
}

// 1
// 1 2
// -1111
// 3
// 1 3 -1 -3 5 3 6 7
// -1111
// 4
// 6 5 9 5 4 9 1 7 5 5
