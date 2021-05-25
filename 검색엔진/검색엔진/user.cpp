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

struct WORD
{
	long long key;
	bool blocked;
	PAGE* page;
	WORD* prev;
} a[MAX_PAGE];

int arr_idx = 0;
WORD* myalloc(void)
{
	a[arr_idx].key = 0;
	a[arr_idx].blocked = 0;
	a[arr_idx].page = nullptr;
	a[arr_idx].prev = nullptr;
	return &a[arr_idx++];
}

WORD* wt[MAX_TABLE];

WORD* findWord(long long k)
{
	int key = (int)(k % MAX_TABLE);
	for (WORD* pp = wt[key]; pp != NULL; pp = pp->prev)
	{
		if (pp->key == k)
		{
			return pp;
		}
	}
	return nullptr;
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
		page[i].word[0] = page[i].word[1] = page[i].word[2] = page[i].word[3] = nullptr;
	}
	
	for (rint i = 0; i < MAX_TABLE; i++)
	{
		wt[i] = nullptr;
	}
}

void addPage(int mId, int m, char word[][11]) {
	page[mId].id = mId;
	page[mId].m = m;
	
	for (rint i = 0; i < m; i++)
	{
		long long temp = strToLL(word[i]);
		int key = (int)(temp % MAX_TABLE);

		WORD* wd = myalloc();
		wd->key = temp;
		wd->page = &page[mId];
		wd->prev = wt[key];
		wt[key] = wd;
		page[mId].word[i] = wd;
	}
}

void removePage(int mId) {
	page[mId].removed = 0;
}

void blockWord(char word[]) {
	WORD* wd = findWord(strToLL(word));
	if (wd)
	{
		wd->blocked = 1;
	}
	else
	{
		wd = myalloc();
		wd->key = strToLL(word);
		wd->prev = wt[(int)(strToLL(word) % MAX_TABLE)];
		wd->page = &page[0];
		wt[(int)(strToLL(word) % MAX_TABLE)] = wd;
	}
}

void recoverWord(char word[]) {
	WORD* wd = findWord(strToLL(word));
	wd->blocked = 0;
}

bool isBlockOrRemoved(PAGE* c)
{
	if (c->removed) { return 0; }
	for (rint i = 0; i < c->m; i++)
	{
		if (c->word[i]->blocked == 1)
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

		for (WORD* pp = wd; pp != NULL; pp = pp->prev)
		{
			if (isBlockOrRemoved(pp->page))
			{
				cnt++;
			}
		}
	}
	else
	{
		if (mode == 1) // and 연산
		{
			WORD* wd1 = findWord(strToLL(word[0]));
			WORD* wd2 = findWord(strToLL(word[1]));
			if (!wd1) { return 0; }

			for (WORD* pp = wd1; pp != NULL; pp = pp->prev)
			{
				if (isBlockOrRemoved(pp->page))
				{
					searchCount[pp->page->id] = searchCountNum;
				}
			}
			if (!wd2) { return 0; }

			for (WORD* pp = wd2; pp != NULL; pp = pp->prev)
			{
				if (searchCount[pp->page->id] == searchCountNum)
				{
					cnt++;
				}
			}

		}
		else //mode = 2, or연산
		{
			WORD* wd1 = findWord(strToLL(word[0]));
			WORD* wd2 = findWord(strToLL(word[1]));
			if (!wd1 && !wd2) { return 0; }

			for (WORD* pp = wd1; pp != NULL; pp = pp->prev)
			{
				if (isBlockOrRemoved(pp->page))
				{
					searchCount[pp->page->id] = searchCountNum;
					cnt++;
				}
			}

			for (WORD* pp = wd2; pp != NULL; pp = pp->prev)
			{
				if (isBlockOrRemoved(pp->page) && searchCount[pp->page->id] != searchCountNum)
				{
					cnt++;
				}
			}
		}
	}
	return cnt;
}