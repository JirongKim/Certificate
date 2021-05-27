#include <stdio.h>

/*
  DO NOT USE ANY GLOBAL VARIABLE OR STATIC VARIABLE IN USER CODE.
  ONLY LOCAL VARIABLE AND CONSTANT ARE ALLOWED. ALSO, IT IS NOT
  ALLOWED TO ALLOCATE MEMORY BY CALLING malloc FUNCTION OR 'new' KEYWORD.
*/

// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.
//
/* bool mstrncmp(unsigned char *a, unsigned char *b, int n) {
     while(*a && *a == *b && n)
         ++a, ++b, n--;
     return *a - *b;
	}
 */

  bool mstrncmp(unsigned char *a, unsigned char *b, int n) {
	 int i = 0;
     while(*a && *a == *b && i < n)
         ++a, ++b, ++i;
	 if (i == n) return 0;
     return *a - *b;
 }

 int mstrlen(unsigned char *a) {
     int len = 0;
     while (*a)
         ++a, ++len;
     return len;
 }

extern bool memread(unsigned char dest[], int pos, int len);
extern bool memwrite(unsigned char src[], int pos, int len);

#define MAXLEN 12
#define MAX_TABLE 2520
#define LEN_IDX 2
#define LEN_VAL 11
#define LEN_STRUCT (LEN_IDX + LEN_VAL)
#define getIdx(hash, isVal) (hash * LEN_STRUCT + (isVal * MAX_TABLE * LEN_STRUCT))

unsigned long myhash(const unsigned char* str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

void encode(unsigned char str[])
{
	if (mstrlen(str) < 12) { return; }
	for (int i = 0; i < 8; i++)
	{
		if (str[11] & (1 << i))
		{
			str[i] += (1 << 7);
		}
	}
	str[11] = 0;
}

void decode(unsigned char str[])
{
	str[11] = 0;
	for (int i = 0; i < 8; i++)
	{
		if (str[i] & (1 << 7))
		{
			str[11] += (1 << i);
			str[i] -= (1 << 7);
		}
	}
	str[12] = 0;
}

int addHash(unsigned char str[], int isVal)
{
	unsigned char temp[1];
	int hash = myhash(str);

	while (1)
	{
		memread(temp, getIdx(hash, isVal), 1);
		if (temp[0] == 0)
		{
			encode(str);
			memwrite(str, getIdx(hash, isVal), LEN_VAL);
			return hash;
		}
		else
		{
			//open addressing
			hash = hash + 1;
			if (hash == MAX_TABLE) { hash = 0; }
		}
	}
}

int findHash(unsigned char str[], int isVal)
{
	unsigned char temp[LEN_VAL];
	int hash = myhash(str);

	encode(str);

	while (1)
	{
		memread(temp, getIdx(hash, isVal), LEN_VAL);
		if (!mstrncmp(temp, str, LEN_VAL))
		{
			return hash;
		}
		else
		{
			//open addressing
			hash = hash + 1;
			if (hash == MAX_TABLE) { hash = 0; }
		}
	}
}

bool init(int N) {
	unsigned char strNull[1] = { 0 };
	for (int i = 0; i < MAX_TABLE; i++)
	{
		memwrite(strNull, getIdx(i, 0), 1);
		memwrite(strNull, getIdx(i, 1), 1);
	}
	return true; // if the value of 'false' is returned, this testcase would be skipped. 
}

void put(unsigned char key_in[MAXLEN + 1], unsigned char value_in[MAXLEN + 1]) {
	int keyIdx = addHash(key_in, 0);
	int valIdx = addHash(value_in, 1);

	unsigned char idx[2] = { 0, };
	idx[0] = keyIdx / 100;
	idx[1] = keyIdx % 100;
	memwrite(idx, getIdx(valIdx, 1) + LEN_VAL, 2);

	idx[0] = valIdx / 100;
	idx[1] = valIdx % 100;
	memwrite(idx, getIdx(keyIdx, 0) + LEN_VAL, 2);
}

void del(unsigned char key_in[MAXLEN + 1]) {
	int keyIdx = findHash(key_in, 0);
	int valIdx;

	unsigned char idx[2];
	memread(idx, getIdx(keyIdx, 0) + LEN_VAL, 2);
	valIdx = (idx[0] * 100) + idx[1];

	unsigned char strNull[1] = { 0 };
	memwrite(strNull, getIdx(keyIdx, 0), 1);
	memwrite(strNull, getIdx(valIdx, 1), 1);
}

void get(unsigned char key_in[MAXLEN + 1], unsigned char value_out[MAXLEN + 1]) {
	int keyIdx = findHash(key_in, 0);
	int valIdx;

	unsigned char idx[2];
	memread(idx, getIdx(keyIdx, 0) + LEN_VAL, 2);
	valIdx = (idx[0] * 100) + idx[1];

	memread(value_out, getIdx(valIdx, 1), LEN_VAL);
	decode(value_out);
	//printf("%s\n", value_out);
}

void getkey(unsigned char value_in[MAXLEN + 1], unsigned char key_out[MAXLEN + 1]) {
	int valIdx = findHash(value_in, 1);
	int keyIdx;

	unsigned char idx[2];
	memread(idx, getIdx(valIdx, 1) + LEN_VAL, 2);
	keyIdx = idx[0] * 100 + idx[1];

	memread(key_out, getIdx(keyIdx, 0), LEN_VAL);
	decode(key_out);
	//printf("%s\n", key_out);
}