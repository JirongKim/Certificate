#define _CRT_SECURE_NO_WARNINGS

#include <Stdio.h>
#include <string.h>

#define MAX_TABLE 10000

struct NODE
{
	char data[7];
	NODE *prev;
}a[10000];

unsigned int idx = 0;

NODE* myalloc()
{
	return &a[idx++];
}

unsigned long myhash(const char* str) {
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) & MAX_TABLE;
	}

	return hash & MAX_TABLE;
}

int main(void)
{
	NODE* hTable[MAX_TABLE];
	for (int i = 0; i < MAX_TABLE; i++) hTable[i] = nullptr;
	NODE* p;

	int key;
	char in[7];

	// 입력부
	for (int i = 0; i < 3; i++)
	{
		scanf("%s", in);
		key = (int)myhash(in);

		p = myalloc();
		strncpy(p->data, in, 7);
		p->prev = hTable[key];
		hTable[key] = p;
	}

	// 검색
	char search[7];

	scanf("%s", search);
	int k = (int)myhash(search);

	for (NODE* pp = hTable[k]; pp != NULL; pp = pp->prev)
	{
		if (!strncmp(search, pp->data, 6))
			printf("FOUND %s \n", pp->data);
	}

	// 마지막 추가한 값을 출력
	printf("FOUND %s \n", hTable[k]->data);

	// Hash Table 초기화 방법.
	idx = 0;
	for (int i = 0; i < MAX_TABLE; i++) hTable[i] = nullptr;

	return 0;
}