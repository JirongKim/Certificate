#include <stdio.h>

#define NULL 0
#define nullptr 0
#define MAX_N 50001
#define MAX_LENGTH 11
#define MAX_WORD 10001
#define MAX_TABLE 100007

long long hashKey(const char* str)
{
	long long hash = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		hash = (hash << 5) + str[i];
	}
	return hash;
}

unsigned long hash(long long temp)
{
	return temp % MAX_TABLE;
}

struct SCHKEY
{
	long long key;
	int id;
	SCHKEY* prev;
} a[MAX_N * 4];
int arr_idx = 0;
SCHKEY* myalloc(void) { return &a[arr_idx++]; }

SCHKEY* hashTable[MAX_TABLE];

long long id[MAX_N][4];


struct BLOCK
{
	long long key;
	bool* isBlock;
	int id;
	BLOCK* prev;
} b[MAX_N * 4 * 4];
int arr_ibx = 0;
BLOCK* myalloc_block(void) { return &b[arr_ibx++]; }

BLOCK* blockTable[MAX_TABLE];

bool blockEnable[MAX_TABLE];

void init(int n) {
	arr_idx = 0;
	arr_ibx = 0;
	for (int i = 0; i < MAX_TABLE; i++)
	{
		hashTable[i] = nullptr;
		blockTable[i] = nullptr;
		blockEnable[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		id[i][0] = id[i][1] = id[i][2] = id[i][3] = 0;
	}
}

void addPage(int mId, int m, char word[][11]) {
	for (int i = 0; i < m; i++)
	{
		int key = (int)hash(hashKey(word[i]));

		id[mId][i] = hashKey(word[i]);
		SCHKEY* newSCH = myalloc();
		newSCH->key = hashKey(word[i]);
		newSCH->id = mId;
		newSCH->prev = hashTable[key];
		hashTable[key] = newSCH;

		for (int j = 0; j < m; j++)
		{
			if (j == i) { continue; }
			BLOCK* newBLK = myalloc_block();
			newBLK->id = mId;
			newBLK->isBlock = &blockEnable[key];
			newBLK->prev = blockTable[key];
			blockTable[key] = newBLK;
		}
	}
}

void removePage(int mId) {
	for (int i = 0; id[mId][i] != 0; i++)
	{
		int key = (int)hash(id[mId][i]);
		SCHKEY* del = NULL;
		for (SCHKEY* pp = hashTable[key]; pp != NULL; del = pp, pp = pp->prev)
		{
			if (pp->key == id[mId][i])
			{
				if (del) // del이 NULL이 아니면?
				{
					del = pp->prev; // del과 다음거를 이어줌.
				}
				else // del이 NULL이면?
				{
					hashTable[key] = pp->prev; // 다음거랑 맨 앞을 이어줌.
				}
			}
		}
		id[mId][i] = 0;
	}
}

void blockWord(char word[]) {
	int key = (int)hash(hashKey(word));
	for (SCHKEY* pp = hashTable[key]; pp != NULL; pp = pp->prev)
	{
		if (pp->key == hashKey(word))
		{
			int temp = hash(hashKey(word));
			blockEnable[temp] = 1;
		}
	}
}

void recoverWord(char word[]) {
	int key = (int)hash(hashKey(word));
	for (SCHKEY* pp = hashTable[key]; pp != NULL; pp = pp->prev)
	{
		if (pp->key == hashKey(word))
		{
			int temp = hash(hashKey(word));
			blockEnable[temp] = 0;
		}
	}
}

int search(char word[2][11], int mode) {
	int cnt = 0;
	if (mode == 0)
	{
		//printf("%s\n", word[0]);
		int key = (int)hash(hashKey(word[0]));
		for (SCHKEY* pp = hashTable[key]; pp != NULL; pp = pp->prev)
		{
			if (pp->key == hashKey(word[0]))
			{
				int temp = hash(hashKey(word[0]));
				int flag = 0;
				for (BLOCK* ppp = blockTable[temp]; ppp != NULL; ppp = ppp->prev)
				{
					if (ppp->id == pp->id) { flag = 1; break; }
				}
				if (flag == 1) { continue; }
				cnt++;
			}
		}
	}
	else
	{
		//printf("%s\n", word[0]);
		//printf("%s\n", word[1]);
		long long temp1[100];
		long long temp2[100];
		int cnt1 = 0;
		int cnt2 = 0;

		int key = (int)hash(hashKey(word[0]));
		for (SCHKEY* pp = hashTable[key]; pp != NULL; pp = pp->prev)
		{
			if (pp->key == hashKey(word[0]))
			{
				int temp = hash(hashKey(word[0]));
				int flag = 0;
				for (BLOCK* ppp = blockTable[temp]; ppp != NULL; ppp = ppp->prev)
				{
					if (ppp->id == pp->id) { flag = 1; break; }
				}
				if (flag == 1) { continue; }
				temp1[cnt1++] = pp->id;
			}
		}

		key = (int)hash(hashKey(word[1]));
		for (SCHKEY* pp = hashTable[key]; pp != NULL; pp = pp->prev)
		{
			if (pp->key == hashKey(word[1]))
			{
				int temp = hash(hashKey(word[0]));
				int flag = 0;
				for (BLOCK* ppp = blockTable[temp]; ppp != NULL; ppp = ppp->prev)
				{
					if (ppp->id == pp->id) { flag = 1; break; }
				}
				if (flag == 1) { continue; }
				temp2[cnt2++] = pp->id;
			}
		}

		if (mode == 1) // and 연산
		{
			for (int i = 0; i < cnt1; i++)
			{
				for (int j = 0; j < cnt2; j++)
				{
					if (temp1[i] == temp2[j]) {
						cnt++;
					}
				}
			}
		}
		else // or연산
		{
			cnt = cnt1 + cnt2;
			for (int i = 0; i < cnt1; i++)
			{
				for (int j = 0; j < cnt2; j++)
				{
					if (temp1[i] == temp2[j]) {
						cnt--;
					}
				}
			}
		}
	}
	//printf("cnt : %d\n", cnt);
	return cnt;
}