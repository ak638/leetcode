#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

class LRUCache{
	public:
		struct ListNode;

		LRUCache(int capacity) {
			bk_num = 7;
			head = NULL;
			tail = NULL;
			cap = capacity;
			num = 0;

			bucket = new ListNode*[bk_num];
			memset(bucket, 0, sizeof(ListNode *) * bk_num); //!!!!!!!
		}

		ListNode *checkKeyExisted(ListNode **head, int key)
		{
			ListNode **cur = head;
			while (*cur)
			{
				if ((*cur)->key == key) break;
				
				cur = &(*cur)->bk_next;
			}
			
			return *cur;
		}

		int get(int key) {
			int bk_idx = getBucketIdx(key);
			ListNode **cur= &bucket[bk_idx];
			ListNode *node = checkKeyExisted(cur, key);
			
			if (node) //found
			{
				//adjust double linked list
				if (node != head) //not head
				{
					//break this node
					removeNodeFromDoubleLinkedList(node);

					//add head
					addHeadToDoubleLinkedList(node);
				}

				return node->val;
			}

			return -1;
		}

		void set(int key, int value) {
			ListNode *toAdd = NULL;

			int bk_idx = getBucketIdx(key); 
			ListNode **cur= &bucket[bk_idx];
			ListNode *node = checkKeyExisted(cur, key);
			
			if (node || num >= cap) //existed or full
			{
				if (! node) toAdd = tail;
				else toAdd = node;

				//remove double linked-list 
				removeNodeFromDoubleLinkedList(toAdd);

				//remove bucket linked-list
				bk_idx = getBucketIdx(toAdd->key); 
				ListNode **head = &bucket[bk_idx];
				removeNodeFromBucketLinkedList(head, toAdd);
				
				//num of nodes remains the same as before
				toAdd->key = key;
				toAdd->val = value;
			}
			else
			{
				toAdd = new ListNode(key, value);
				num++;
			}

			//set the right place
			addHeadToDoubleLinkedList(toAdd); //set all-list

			bk_idx = getBucketIdx(key); 
			cur= &bucket[bk_idx];
			addHeadToBucketLinkedList(cur, toAdd); //set bk-list
		}

		~LRUCache() {
			ListNode *tmp = NULL;
			for (int i = 0; i < bk_num; ++i)
			{
				ListNode *cur = bucket[i];
				while (cur)
				{
					tmp = cur;
					cur = cur->bk_next;
					delete tmp, tmp = NULL;
				}
			}
			
			delete[] bucket, bucket = NULL;
		}

		//-----------------
		struct ListNode {
			int key;
			int val;
			ListNode *pre;
			ListNode *next;
			ListNode *bk_pre;
			ListNode *bk_next;
			ListNode(int _key, int _value) : key(_key), val(_value), pre(NULL), next(NULL), bk_pre(NULL), bk_next(NULL) {}
		};

		int getBucketIdx(int key)
		{
			return key % bk_num;
		}

		void showDoubleLinkedList()
		{
			ListNode *cur = head;
			while (cur)
			{
				printf("[%d:%d]<->", cur->key, cur->val);
				cur = cur->next;
			}
			printf("nil\n");
		}

		void showBucketLinkedList()
		{
			for (int i = 0; i < bk_num; ++i)
			{
				printf("IDX[%d] ", i);
				ListNode *cur = bucket[i];
				while (cur)
				{
					printf("[%d:%d]<->", cur->key, cur->val);
					cur = cur->bk_next;
				}
				printf("nil\n");
			}
		}

		void showCap()
		{
			printf("Using %d of %d\n", num, cap);
		}

		void removeNodeFromBucketLinkedList(ListNode **head, ListNode *cur)
		{
			if (cur->bk_pre) cur->bk_pre->bk_next = cur->bk_next;
			else *head = cur->bk_next; //!!!!! not "= NULL"

			if (cur->bk_next) cur->bk_next->bk_pre = cur->bk_pre;
		}

		void addHeadToBucketLinkedList(ListNode **cur, ListNode *toAdd)
		{
			toAdd->bk_next = *cur;
			toAdd->bk_pre = NULL;

			if (*cur) (*cur)->bk_pre = toAdd;
			*cur = toAdd;
		}

		void removeNodeFromDoubleLinkedList(ListNode *cur)
		{
			if (cur == tail) tail = cur->pre;
			if (cur == head) head = cur->next;

			if (cur->pre) cur->pre->next = cur->next;
			if (cur->next) cur->next->pre = cur->pre;
		}

		void addHeadToDoubleLinkedList(ListNode *cur)
		{
			if (! head) 
			{
				cur->next = NULL;
				cur->pre = NULL;

				tail = cur;
			}
			else
			{
				cur->next = head;
				cur->pre = NULL;
				head->pre = cur;
			}

			head = cur;
		}
	
	private:
		int bk_num;
		ListNode **bucket;
		ListNode *head;
		ListNode *tail;

		int cap;
		int num;
};

int main(int argc, char *argv[])
{
	freopen("./input.txt", "r", stdin);
	LRUCache cache(10);

	int key;
	int val;
	
	cache.set(1, 3);
	cache.showDoubleLinkedList();
	cache.showBucketLinkedList();
	printf("\n");

	cache.set(2, 4);
	cache.showDoubleLinkedList();
	cache.showBucketLinkedList();
	printf("\n");

	cache.set(6, 2);
	cache.showDoubleLinkedList();
	cache.showBucketLinkedList();
	printf("\n");


	key = 1;
	val = cache.get(key);
	printf("get %d -> %d\n", key, val);
	cache.showDoubleLinkedList();
	cache.showBucketLinkedList();
	printf("\n");

	cache.set(8, 2);
	cache.showDoubleLinkedList();
	cache.showBucketLinkedList();
	printf("\n");

	key = 100;
	val = cache.get(key);
	printf("get %d -> %d\n", key, val);
	cache.showDoubleLinkedList();
	cache.showBucketLinkedList();
	printf("\n");

	key = 8;
	val = cache.get(key);
	printf("get %d -> %d\n", key, val);
	cache.showDoubleLinkedList();
	cache.showBucketLinkedList();

	printf("\n===========\n");
	cache.showDoubleLinkedList();
	cache.showBucketLinkedList();

	cache.showCap();

	return 0;
}
//qspace@GYDEV ~/mattwu/leetcode $ cat tmp.txt| awk -F'),' '{for (i = 1; i <= NF; ++i) printf("cache.%s);\n", $i)}'
