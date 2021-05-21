#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

#define MAX_TABLE 100000

int arr_idx = 0;

unsigned long myhash(const char* str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

struct NODE {
	char data[7];

	NODE* prev;
} a[20000];

NODE* myalloc(void){
	return &a[arr_idx++];
}

NODE* hTable[MAX_TABLE];

int main(void)
{
	NODE* p;

	int key;
	char in[7] = "aaaaaa";

	key = (int)myhash(in);

	p = myalloc();
	strncpy(p->data, in, 7);
	p->prev = hTable[key];
	hTable[key] = p;



	char search[7] = "vrvipy";

	int k = (int)myhash(search);

	for (NODE* pp = hTable[k]; pp != NULL; pp = pp->prev)
	{
		if (!strncmp(search, pp->data, 6))
			cout << "FOUND : " << pp->data << endl << endl;
	}

	return 0;
}