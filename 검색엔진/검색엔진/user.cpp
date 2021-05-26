#include <stdio.h>

#define MAX_PAGE 50000
#define MAX_TABLE 20001
#define rint register int

#define NULL 0
#define nullptr 0

struct WORD;

struct PAGE
{
	int id;
	int m;
	bool removed;
	WORD* word[4];
} page[MAX_PAGE];

struct NODE
{
	int id;
	NODE* prev;
} a[MAX_PAGE * 4];

int arr_idx = 0;
NODE* myalloc(void)
{
	a[arr_idx].id = 0;
	a[arr_idx].prev = nullptr;
	return &a[arr_idx++];
}

struct WORD
{
	long long w;
	bool blocked;
	NODE* head;
} wd[MAX_PAGE];

WORD wt[MAX_TABLE];

WORD* addWord(long long k)
{
	int key = (int)(k % MAX_TABLE);
	while (wt[key].w != k)
	{
		if (wt[key].w == 0)
		{
			wt[key].w = k;
			break;
		}
		key = (key + 1) % MAX_TABLE;
	}
	return &wt[key];
}

WORD* findWord(long long k)
{
	int key = (int)(k % MAX_TABLE);
	//int cnt = MAX_TABLE;

	//while (wt[key].w != k && cnt--)
	while (wt[key].w != k)
	{
		if (wt[key].w == 0)
		{
			return NULL;
		}
		key = (key + 1) % MAX_TABLE;
	}
	return &wt[key];
}

long long strToLL(char* str)
{
	long long ret = 0;
	for (rint i = 0; str[i] != '\0'; i++)
	{
		ret = (ret << 5) + str[i] - 'a' + 1;
	}
	return ret;
}

int searchCount[MAX_PAGE] = { 0, };
int searchCountNum = 0;

void init(int n) {
	arr_idx = 0;
	for (rint i = 0; i < MAX_PAGE; i++)
	{
		page[i].id = page[i].m = page[i].removed = 0;
		page[i].word[0] = page[i].word[1] = page[i].word[2] = page[i].word[3] = NULL;
		wd[i].blocked = wd[i].w = 0;
		wd[i].head = NULL;
	}

	for (rint i = 0; i < MAX_TABLE; i++)
	{
		wt[i].blocked = 0;
		wt[i].w = 0;
		wt[i].head = nullptr;
	}
}

void addPage(int mId, int m, char word[][11]) {
	page[mId].id = mId;
	page[mId].m = m;
	page[mId].removed = 0;

	for (rint i = 0; i < m; i++)
	{
		long long temp = strToLL(word[i]);
		if (temp == 19133893899)
		{
		}

		WORD* wd = addWord(temp);
		page[mId].word[i] = wd;

		NODE* newNode = myalloc();
		newNode->id = mId;
		newNode->prev = wd->head;
		wd->head = newNode;
	}
}

void removePage(int mId) {
	page[mId].removed = 1;
}

void blockWord(char word[]) {
	WORD* wd = addWord(strToLL(word));
	wd->blocked = 1;
}

void recoverWord(char word[]) {
	WORD* wd = findWord(strToLL(word));
	wd->blocked = 0;
}

bool isBlockOrRemoved(int id)
{
	if (page[id].removed) { return 0; }
	for (rint i = 0; i < page[id].m; i++)
	{
		if (page[id].word[i]->blocked == 1)
		{
			return 0;
		}
	}
	return 1;
}

int search(char word[2][11], int mode) {
	searchCountNum++;
	int cnt = 0;

	if (mode == 0)
	{
		WORD* wd = findWord(strToLL(word[0]));
		if (!wd) { return 0; }

		for (NODE* pp = wd->head; pp != NULL; pp = pp->prev)
		{
			if (isBlockOrRemoved(pp->id))
			{
				cnt++;
			}
		}
	}
	else
	{
		if (mode == 1) // and ¿¬»ê
		{
			WORD* wd1 = findWord(strToLL(word[0]));
			WORD* wd2 = findWord(strToLL(word[1]));
			if (!wd1 || !wd2) { return 0; }

			for (NODE* pp = wd1->head; pp != NULL; pp = pp->prev)
			{
				if (isBlockOrRemoved(pp->id))
				{
					searchCount[pp->id] = searchCountNum;
				}
			}

			for (NODE* pp = wd2->head; pp != NULL; pp = pp->prev)
			{
				if (searchCount[pp->id] == searchCountNum)
				{
					cnt++;
				}
			}

		}
		else //mode = 2, or¿¬»ê
		{
			WORD* wd1 = findWord(strToLL(word[0]));
			WORD* wd2 = findWord(strToLL(word[1]));
			if (!wd1 && !wd2) { return 0; }

			if (wd1)
			{
				for (NODE* pp = wd1->head; pp != NULL; pp = pp->prev)
				{
					if (isBlockOrRemoved(pp->id))
					{
						searchCount[pp->id] = searchCountNum;
						cnt++;
					}
				}
			}

			if (wd2)
			{
				for (NODE* pp = wd2->head; pp != NULL; pp = pp->prev)
				{
					if (isBlockOrRemoved(pp->id) && searchCount[pp->id] != searchCountNum)
					{
						cnt++;
					}
				}
			}
		}
	}
	return cnt;
}