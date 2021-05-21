#include <stdio.h>

#define NULL 0
#define nullptr 0
#define MAX_N			5
#define MAX_NAME_LEN	7
#define MAX_TAG_LEN		4
#define MAX_M			101
#define MAX_ADD			50000*2+7

#define rint register int

void mstrcpy(char dst[], const char src[]) {
	int c = 0;
	while ((dst[c] = src[c]) != '\0') ++c;
}

int mstrcmp(const char str1[], const char str2[]) {
	int c = 0;
	while (str1[c] != '\0' && str1[c] == str2[c]) ++c;
	return str1[c] - str2[c];
}

unsigned long hash(const char* str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 6) + hash) + c) % MAX_ADD; // 영문자, 소문자
	}

	return hash % MAX_ADD;
}

struct BOOK;

struct SEC
{
	char book_name[MAX_NAME_LEN]; //Book의 Name
	int exist; //Book의 삭제&이동 여부
	BOOK* book_info; //Book의 주소값
	SEC* prev; //LinkedList
} a[200000];

struct BOOK
{
	int typeNum; //type의 개수
	char book_types[MAX_N][MAX_TAG_LEN]; //type의 종류
	int type_hash[MAX_N]; //type의 hash값
	char book_name[MAX_NAME_LEN]; //Book의 Name
	SEC* section; //Section의 주소값
	BOOK* prev;
} b[MAX_ADD];

int arr_sec = 0;
int arr_book = 0;

SEC* myalloc_sec(void) { return &a[arr_sec++]; }
BOOK* myalloc_book(void) { return &b[arr_book++]; }

SEC* secTable[MAX_M];
BOOK* bookTable[MAX_ADD];

SEC* secPtr;
BOOK* bookPtr;

void init(int M)
{
	arr_sec = 0;
	arr_book = 0;
	for (rint i = 0; i <= M; i++) { secTable[i] = nullptr; }
	for (rint i = 0; i < MAX_ADD; i++) { bookTable[i] = nullptr; }
}

void add(char mName[MAX_NAME_LEN], int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{
	int key = (int)hash(mName);

	bookPtr = myalloc_book();
	mstrcpy(bookPtr->book_name, mName);
	bookPtr->typeNum = mTypeNum;

	for (rint i = 0; i < mTypeNum; i++)
	{
		mstrcpy(bookPtr->book_types[i], mTypes[i]);
		bookPtr->type_hash[i] = (int)hash(bookPtr->book_types[i]);
	}

	secPtr = myalloc_sec();
	mstrcpy(secPtr->book_name, mName);
	secPtr->exist = 1;
	secPtr->book_info = bookPtr;
	secPtr->prev = secTable[mSection];
	secTable[mSection] = secPtr;

	bookPtr->section = secPtr;
	bookPtr->prev = bookTable[key];
	bookTable[key] = bookPtr;

	/*printf("BookName : %s, key : %d\n", bookPtr->book_name, key);
	for (int i = 0; i < 5; i++)
	{
		printf("BookType[%d] : %s\n", i, bookPtr->book_types[i]);
		printf("TypeHash[%d] : %d\n", i, bookPtr->type_hash[i]);
	}
	printf("Type개수 : %d\n", bookPtr->typeNum);
	printf("Section : %d\n", mSection);
	printf("\n");*/
}

int moveType(char mType[MAX_TAG_LEN], int mFrom, int mTo)
{
	int count = 0;
	int key = (int)hash(mType);
	SEC* secTemp;
	SEC** prevSec = &secTable[mFrom];
	for (SEC* ss = secTable[mFrom]; ss != NULL; ss = ss->prev)
	{
		//printf("%s\n", ss->book_name);
		if (ss->exist == 0) { continue; }
		for (rint i = 0; i < ss->book_info->typeNum; i++)
		{
			if (key == ss->book_info->type_hash[i])
			{
				if (mstrcmp(mType, ss->book_info->book_types[i])) { continue; } //types가 hash는 같은데, 실제 문자가 다르면?
				//printf("%s ", ss->book_info->book_name);
				//printf("\n");
				secTemp = myalloc_sec();
				*secTemp = *ss;
				secTemp->prev = secTable[mTo];
				secTable[mTo] = secTemp;

				int key_book = (int)hash(secTemp->book_name);
				for (BOOK* bb = bookTable[key_book]; bb != NULL; bb = bb->prev)
				{
					if (!mstrcmp(ss->book_info->book_name, bb->book_name))
					{
						bb->section = secTable[mTo];
						break;
					}
				}

				ss->exist = 0;
				*prevSec = ss->prev;
				count++;
				break;
			}
		}
		prevSec = &ss->prev;
	}
	return count;
}

void moveName(char mName[MAX_NAME_LEN], int mSection)
{
	int key = (int)hash(mName);
	SEC* secTemp;
	secTemp = myalloc_sec();
	for (BOOK* bb = bookTable[key]; bb != NULL; bb = bb->prev)
	{
		if (!mstrcmp(mName, bb->book_name))
		{
			*secTemp = *(bb->section);
			bb->section->exist = 0;
			secTemp->prev = secTable[mSection];
			secTable[mSection] = secTemp;
			bb->section = secTable[mSection];
			break;
		}
	}
}

void deleteName(char mName[MAX_NAME_LEN])
{
	int key = (int)hash(mName);
	for (BOOK* bb = bookTable[key]; bb != NULL; bb = bb->prev)
	{
		if (!mstrcmp(mName, bb->book_name))
		{
			bb->section->exist = 0;
			break;
		}
	}
}

int countBook(int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{
	int count = 0;
	int temp[5];
	for (rint i = 0; i < mTypeNum; i++)
	{
		temp[i] = (int)hash(mTypes[i]);
	}

	for (SEC* ss = secTable[mSection]; ss != NULL; ss = ss->prev)
	{
		if (ss->exist == 0) { continue; }
		for (rint i = 0; i < mTypeNum; i++)
		{
			rint flag = 0;
			for (rint j = 0; j < ss->book_info->typeNum; j++)
			{
				if (temp[i] == ss->book_info->type_hash[j])
				{
					if (mstrcmp(mTypes[i], ss->book_info->book_types[j])) { continue; } //types가 hash는 같은데, 실제 문자가 다르면?
					count++;
					flag = 1;
					break;
				}
			}
			if (flag == 1) { break; }
		}
	}

	return count;
}