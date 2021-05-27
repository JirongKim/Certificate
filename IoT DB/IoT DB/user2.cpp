//#include <stdio.h>
//
///*
//  DO NOT USE ANY GLOBAL VARIABLE OR STATIC VARIABLE IN USER CODE.
//  ONLY LOCAL VARIABLE AND CONSTANT ARE ALLOWED. ALSO, IT IS NOT
//  ALLOWED TO ALLOCATE MEMORY BY CALLING malloc FUNCTION OR 'new' KEYWORD.
//*/
//
//// The below commented functions are for your reference. If you want 
//// to use it, uncomment these functions.
////
//bool mstrncmp(unsigned char* a, unsigned char* b, int n) {
//    int i = 0;
//    while (*a && *a == *b && i < n)
//        ++a, ++b, ++i;
//    if (i == n) return 0;
//    return *a - *b;
//}
//
// int mstrlen(unsigned char *a) {
//     int len = 0;
//     while (*a)
//         ++a, ++len;
//     return len;
// }
//
//extern bool memread(unsigned char dest[], int pos, int len);
//extern bool memwrite(unsigned char src[], int pos, int len);
//
//#define MAXLEN 12
//#define MAX_TABLE 2978
//#define LEN_IDX 2
//#define LEN_VAL 9
//#define LEN_STRUCT (LEN_IDX + LEN_VAL)
//#define getIdx(hash, isVal) hash * LEN_STRUCT + (isVal * MAX_TABLE * LEN_STRUCT)
//
//unsigned long myhash(const unsigned char* str)
//{
//	unsigned long hash = 5381;
//	int c;
//
//	while (c = *str++)
//	{
//		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
//	}
//
//	return hash % MAX_TABLE;
//}
//
//void encode(unsigned char str[])
//{
//	if (mstrlen(str) < 10) { return; }
//	long long h[2] = { 0, };
//	for (int i = 0, c = 0; str[i] != 0; i++)
//	{
//		if (str[i] >= '0' && str[i] <= '9')
//			h[c] = (h[c] << 6) + str[i] - '0' + 1;
//		else if (str[i] >= 'a' && str[i] <= 'z')
//			h[c] = (h[c] << 6) + str[i] - 'a' + 11;
//		else if (str[i] >= 'A' && str[i] <= 'Z')
//			h[c] = (h[c] << 6) + str[i] - 'A' + 37;
//
//		if (i == 7) { c++; } //앞에걸 48비트로 사용.
//	}
//
//	for (int i = 0, c = 0; i < 9; i++)
//	{
//		str[i] = h[c] & 0xFF;
//		h[c] = h[c] >> 8;
//
//		if (i == 5) { c++; }
//		//printf("%d ", str[i]);
//	}
//	//printf("\n");
//}
//
//void decode(unsigned char str[])
//{
//	long long h[2] = { 0, };
//	for (int i = 5; i >= 0; i--)
//	{
//		if (str[i] == 0) { 
//			return; 
//		}
//		h[0] = h[0] + str[i];
//		h[0] = h[0] << 8;
//	}
//	for (int i = 8; i >= 6; i--)
//	{
//		if (str[i] == 0) {
//			return;
//		}
//		h[1] = h[1] + str[i];
//		h[1] = h[1] << 8;
//	}
//
//
//	h[0] = h[0] >> 8;
//	h[1] = h[1] >> 8;
//
//	for (int i = 0, c =0; i < 12; i++)
//	{
//		str[i] = h[c] & 0x3F;
//		h[c] = h[c] >> 6;
//
//		if (str[i] >= 1 && str[i] <= 10)
//			str[i] = str[i] + '0' - 1;
//		else if (str[i] >= 11 && str[i] <= 36)
//			str[i] = str[i] + 'a' - 11;
//		else if (str[i] >= 37 && str[i] <= 62)
//			str[i] = str[i] + 'A' - 37;
//		
//		if (i == 7) { c++; }
//	}
//	str[12] = 0;
//}
//
//int addHash(unsigned char str[], int isVal)
//{
//	unsigned char temp[1];
//	int hash = myhash(str);
//
//	while (1)
//	{
//		memread(temp, getIdx(hash, isVal), 1);
//		if (temp[0] == 0)
//		{
//			encode(str);
//			memwrite(str, getIdx(hash, isVal), LEN_VAL);
//			return hash;
//		}
//		else
//		{
//			//open addressing
//			hash = hash + 1;
//			if (hash == MAX_TABLE) { hash = 0; }
//		}
//	}
//}
//
//int findHash(unsigned char str[], int isVal)
//{
//	unsigned char temp[LEN_STRUCT];
//	int hash = myhash(str);
//
//	encode(str);
//
//	while (1)
//	{
//		memread(temp, getIdx(hash, isVal), LEN_STRUCT);
//		if (!mstrncmp(temp, str, LEN_STRUCT))
//		{
//			return hash;
//		}
//		else
//		{
//			//open addressing
//			hash = hash + 1;
//			if (hash == MAX_TABLE) { hash = 0; }
//		}
//	}
//}
//
//bool init(int N) {
//	unsigned char strNull[1] = { 0 };
//	for (int i = 0; i < MAX_TABLE; i++)
//	{
//		memwrite(strNull, getIdx(i, 0), 1);
//		memwrite(strNull, getIdx(i, 1), 1);
//	}
//	return true; // if the value of 'false' is returned, this testcase would be skipped. 
//}
//
//void put(unsigned char key_in[MAXLEN + 1], unsigned char value_in[MAXLEN + 1]) {
//	int keyIdx = addHash(key_in, 0);
//	int valIdx = addHash(value_in, 1);
//
//	unsigned char idx[2] = { 0, };
//	idx[0] = keyIdx / 100;
//	idx[1] = keyIdx % 100;
//	memwrite(idx, getIdx(valIdx, 1) + LEN_STRUCT, 2);
//
//	idx[0] = valIdx / 100;
//	idx[1] = valIdx % 100;
//	memwrite(idx, getIdx(keyIdx, 0) + LEN_STRUCT, 2);
//}
//
//void del(unsigned char key_in[MAXLEN + 1]) {
//	int keyIdx = findHash(key_in, 0);
//	int valIdx;
//
//	unsigned char idx[2];
//	memread(idx, getIdx(keyIdx, 0) + LEN_STRUCT, 2);
//	valIdx = idx[0] * 100 + idx[1];
//
//	unsigned char strNull[1] = { 0 };
//	memwrite(strNull, getIdx(keyIdx, 0), 1);
//	memwrite(strNull, getIdx(valIdx, 1), 1);
//}
//
//void get(unsigned char key_in[MAXLEN + 1], unsigned char value_out[MAXLEN + 1]) {
//	int keyIdx = findHash(key_in, 0);
//	int valIdx;
//
//	unsigned char idx[2];
//	memread(idx, getIdx(keyIdx, 0) + LEN_STRUCT, 2);
//	valIdx = idx[0] * 100 + idx[1];
//
//	memread(value_out, getIdx(valIdx, 1), LEN_STRUCT);
//	decode(value_out);
//	printf("%s\n", value_out);
//}
//
//void getkey(unsigned char value_in[MAXLEN + 1], unsigned char key_out[MAXLEN + 1]) {
//	int valIdx = findHash(value_in, 1);
//	int keyIdx;
//
//	unsigned char idx[2];
//	memread(idx, getIdx(valIdx, 1) + LEN_STRUCT, 2);
//	keyIdx = idx[0] * 100 + idx[1];
//
//	memread(key_out, getIdx(keyIdx, 0), LEN_STRUCT);
//	decode(key_out);
//	printf("%s\n", key_out);
//}