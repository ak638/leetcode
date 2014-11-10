#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
	public:
		ListNode *sortList(ListNode *head) {
			if (! head) return head;

			int len = 0;
			ListNode *cur = head;

			//get length
			while (cur)
			{
				len++;
				cur = cur->next;
			}

			if (len <= 1) return head;

			//init hash_map
			ListNode **marr = new ListNode * [len];
			cur = head;
			int i = 0;
			while (cur)
			{
				marr[i++] = cur;
				cur = cur->next;
			}

			//do quick sort
			quickSort(marr, 0, len-1);

			delete[] marr;

			return NULL;
		}

		void quickSort(ListNode *marr[], int beg, int end)
		{
			if (beg < end)
			{
				int mid = Partition(marr, beg, end);
				quickSort(marr, beg, mid-1);
				quickSort(marr, mid+1, end);
			}
		}

		void _swap(ListNode *marr[], int i, int j)
		{
			marr[i]->val ^= marr[j]->val ^= marr[i]->val ^= marr[j]->val;
		}

		int Partition(ListNode *marr[], int beg, int end)
		{
			int i = beg, j = end;
			int pivot = marr[i]->val;

			while (i < j)
			{
				while (marr[j]->val >= pivot && i < j) j--;
				marr[i]->val = marr[j]->val;

				while (marr[i]->val <= pivot && i < j) i++;
				marr[j]->val = marr[i]->val;
			}

			marr[i]->val = pivot;
			
			return i;
		}

		void showArrayCont(ListNode *marr[], int num)
		{
			for (int i = 0; i < num; ++i)
			{
				printf("%d ", marr[i]->val);
			}
			printf("\n");
		}

		void showArray(ListNode *head)
		{
			while (head)
			{
				printf("%d ", head->val);
				head = head->next;
			}
			printf("\n");
		}

		ListNode *initList(int arr[], int num)
		{
			ListNode *head = new ListNode(0);
			ListNode *cur = head;

			for (int i = 0; i < num; ++i)
			{
				ListNode *tmp = new ListNode(arr[i]);

				cur->next = tmp;
				cur = tmp;
			}

			return head;
		}
};

void showArray(int arr[], int num)
{
	for (int i = 0; i < num; ++i) printf("%d ", arr[i]);
	printf("\n");
}

void _swap(int arr[], int i, int j)
{
	arr[i] ^= arr[j] ^= arr[i] ^= arr[j];
}

void Partition(int arr[], int beg, int end)
{
	if (beg >= end) return;

	int mid = (beg + end) / 2;
	int pivot = arr[mid];
	int i = beg, j = end;

	//keep pivot in i first
	if (i != mid) _swap(arr, i, mid);

	while (i < j)
	{
		while (arr[j] > pivot && i < j) j--;
		if (i < j) _swap(arr, i, j); //now pivot in j

		while (arr[i] <= pivot && i < j) i++;
		if (i < j) _swap(arr, i, j); //now pivot in i
	}

	Partition(arr, 0, i-1);
	Partition(arr, i+1, end);
}

void quickSort(int arr[], int len)
{
	if (1 < len)
	{
		Partition(arr, 0, len-1);
	}
}

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	Solution poSolution;

	int testcase = 0;
	scanf("%d", &testcase);

	while (testcase--)
	{
		int num = 0;
		scanf("%d", &num);

		int arr[20];
		for (int i = 0; i < num; ++i) scanf("%d", &arr[i]);

		ListNode *fake_head = poSolution.initList(arr, num);
		ListNode *head = fake_head->next;

		poSolution.showArray(head);

		poSolution.sortList(head);

		poSolution.showArray(head);
	}

	return 0;
}
