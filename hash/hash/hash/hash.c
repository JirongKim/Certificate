#include <stdio.h>
#include <stdlib.h>

#define MAX 10;

struct node
{
	int block_num;
	int block_max;
	struct node* next;
};

struct bucket
{
	int count;
	struct node* head;
};

struct bucket* hashTable[MAX];

int hash_function(int key)
{
	return key;
}

void hash_insert(int key, int block_num, int block_max)
{
	struct node* newNode = hashTable[key];

	return;
}

int main(void)
{
	return 0;
}