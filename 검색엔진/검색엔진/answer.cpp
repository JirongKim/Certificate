//#define MAX_PAGES 50000
//#define MAX_TABLE 20001
//
//struct WORD;
//
//struct PAGE
//{
//	int id;
//	bool removed;
//	int nWord;
//	WORD* word[4];
//};
//
//struct NODE
//{
//	PAGE* page;
//	NODE* next;
//};
//
//struct WORD
//{
//	long long key;
//	bool blocked;
//	NODE* head;
//};
//
//PAGE page[MAX_PAGES];
//WORD tb[MAX_TABLE];
//
//int foundIds[MAX_PAGES] = { 0, };
//int searchCnt;
//
//long long wordToLL(char* s)
//{
//	long long h = 0;
//	while (*s)
//		h = (h << 5) + *s++ - 'a' + 1;
//	return h;
//}
//
//WORD* addWord(long long k)
//{
//	int h = k % MAX_TABLE;
//
//	while (tb[h].key != k)
//	{
//		if (tb[h].key == 0)
//		{
//			tb[h].key = k;
//			break;
//		}
//		h = (h + 1) % MAX_TABLE;
//	}
//	return &tb[h];
//}
//
//WORD* findWord(long long k)
//{
//	int h = k % MAX_TABLE;
//	int cnt = MAX_TABLE;
//
//	while (tb[h].key != k && cnt--)
//	{
//		if (tb[h].key == 0)
//			return nullptr;
//		h = (h + 1) % MAX_TABLE;
//	}
//	return &tb[h];
//}
//
//void init(int n)
//{
//	for (int i = 0; i < MAX_TABLE; i++)
//	{
//		for (NODE* cur = tb[i].head, *next; cur; cur = next)
//		{
//			next = cur->next;
//			delete cur;
//		}
//		tb[i].key = 0;
//		tb[i].blocked = false;
//		tb[i].head = nullptr;
//	}
//}
//
//void addPage(int mId, int m, char word[][11])
//{
//	page[mId].id = mId;
//	page[mId].removed = false;
//	page[mId].nWord = m;
//
//	for (int i = 0; i < m; i++)
//	{
//		long long k = wordToLL(word[i]);
//		WORD* wd = addWord(k);
//		page[mId].word[i] = wd;
//
//		NODE* newNode = new NODE;
//		newNode->page = &page[mId];
//		newNode->next = wd->head;
//		wd->head = newNode;
//	}
//}
//
//void removePage(int mId)
//{
//	page[mId].removed = true;
//}
//
//void blockWord(char word[])
//{
//	WORD* wd = addWord(wordToLL(word));
//	wd->blocked = true;
//}
//
//void recoverWord(char word[])
//{
//	WORD* wd = findWord(wordToLL(word));
//	wd->blocked = false;
//}
//
//bool isBlockedOrRemoved(PAGE* page)
//{
//	if (page->removed)
//		return true;
//
//	for (int i = 0; i < page->nWord; i++)
//	{
//		if (page->word[i]->blocked)
//			return true;
//	}
//
//	return false;
//}
//
//int search(char word[2][11], int mode)
//{
//	long long k1 = wordToLL(word[0]);
//	long long k2 = wordToLL(word[1]);
//	WORD* wd1 = findWord(k1);
//	WORD* wd2 = findWord(k2);
//	int cnt = 0;
//
//	++searchCnt;
//
//	if (mode == 0)
//	{
//		if (!wd1) return 0;
//		for (NODE* cur = wd1->head; cur; cur = cur->next)
//		{
//			if (!isBlockedOrRemoved(cur->page))
//				++cnt;
//		}
//	}
//	else if (mode == 1)
//	{
//		if (!wd1 || !wd2) return 0;
//
//		for (NODE* cur = wd1->head; cur; cur = cur->next)
//		{
//			if (!isBlockedOrRemoved(cur->page))
//				foundIds[cur->page->id] = searchCnt;
//		}
//
//		for (NODE* cur = wd2->head; cur; cur = cur->next)
//		{
//			if (foundIds[cur->page->id] == searchCnt)
//				++cnt;
//		}
//	}
//	else if (mode == 2)
//	{
//		if (wd1)
//		{
//			for (NODE* cur = wd1->head; cur; cur = cur->next)
//			{
//				if (!isBlockedOrRemoved(cur->page))
//				{
//					foundIds[cur->page->id] = searchCnt;
//					++cnt;
//				}
//			}
//		}
//
//		if (wd2)
//		{
//			for (NODE* cur = wd2->head; cur; cur = cur->next)
//			{
//				if (foundIds[cur->page->id] != searchCnt && !isBlockedOrRemoved(cur->page))
//					++cnt;
//			}
//		}
//	}
//	return cnt;
//}