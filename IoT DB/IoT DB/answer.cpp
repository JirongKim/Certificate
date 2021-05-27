//#include <stdio.h>
//
///*
//  DO NOT USE ANY GLOBAL VARIABLE OR STATIC VARIABLE IN USER CODE.
//  ONLY LOCAL VARIABLE AND CONSTANT ARE ALLOWED. ALSO, IT IS NOT
//  ALLOWED TO ALLOCATE MEMORY BY CALLING malloc FUNCTION OR 'new' KEYWORD.
//*/
//
// /*The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.*/
//
// bool mstrncmp(unsigned char *a, unsigned char *b, int n) {
//	 int i = 0;
//     while(*a && *a == *b && i < n)
//         ++a, ++b, ++i;
//	 if (i == n) return 0;
//     return *a - *b;
// }
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
//#define MAX_TABLE 2520
//#define DATA_LEN 11 //12에서 압축해서 11이 됨.
//#define IDX_LEN 2
//#define STRUCT_LEN (DATA_LEN + IDX_LEN)
//#define HASH_POS(hashKey, isVal) (hashKey * STRUCT_LEN + (isVal * MAX_TABLE * STRUCT_LEN)) //+뒷부분은 상위,하위테이블을 나누는방법.
//
//unsigned long myhash(unsigned char* str)
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
//void encode(unsigned char data[])
//{
//	if (mstrlen(data) < MAXLEN) return; //12보다 작음면 압축할 필요가 없음.
//
//	for (int i = 0; i < 8; i++)
//	{
//		// data[11]; -> data[0~7]의 최상위 비트위에 올림.
//		if (data[11] & (1 << i)) //얘가 만약 on이면
//		{
//			data[i] += (1 << 7); //0~7의 최상위 비트에 on 시켜준다.
//		}
//	}
//	data[11] = 0;
//}
//
//void decode(unsigned char data[])
//{
//	data[11] = 0;
//	for (int i = 0; i < 8; i++)
//	{
//		// data[0~7]의 최상위 비트를 data[11]의 0~7비트에 저장함.
//		if (data[i] & (1 << 7)) //얘가 만약 on이면
//		{
//			data[11] += (1 << i); //0~7의 최상위 비트가 켜져있으면, data[11]을 순차적으로 shift시킨걸 더해준다.
//			data[i] -= (1 << 7);
//		}
//	}
//	data[12] = 0;
//}
//
//int addToHashTbl(unsigned char data[], int isVal)
//{
//	unsigned char t[MAXLEN] = "DtUcVyU98yw";
//	if (!mstrncmp(t, data, MAXLEN))
//	{
//		//encode(data);
//	}
//	int hashKey = myhash(data);
//	unsigned char tempStr[1];
//	while (1)
//	{
//		memread(tempStr, HASH_POS(hashKey,isVal), 1); // 마지막 문자열 1개만 압축해서 11바이트로 만들고, 거기에 위치정보를 담은 2바이트까지 해서 13바이트임.
//		if (tempStr[0] == 0)
//		{
//			//만약 비어있는 경우에?
//			encode(data);
//			memwrite(data, HASH_POS(hashKey, isVal), DATA_LEN);
//			return hashKey;
//		}
//		else //open Addressing
//		{
//			hashKey++;
//			if (hashKey == MAX_TABLE) hashKey = 0;
//		}
//	}
//}
//
//int findHashIndex(unsigned char data[], int isVal)
//{
//	int hashKey = myhash(data);
//	unsigned char tempStr[DATA_LEN];
//	encode(data);
//
//	while (1)
//	{
//		memread(tempStr, HASH_POS(hashKey, isVal), DATA_LEN);
//		if (mstrncmp(tempStr, data, DATA_LEN) == 0)// 찾은거
//		{
//			return hashKey;
//		}
//		else
//		{
//			hashKey++;
//			if (hashKey == MAX_TABLE) hashKey = 0;
//		}
//	}
//}
//
//bool init(int N) {
//	unsigned char tempNull[1] = { 0 };
//
//	for (int i = 0; i < MAX_TABLE; i++)
//	{
//		memwrite(tempNull, HASH_POS(i, 0), 1);
//		memwrite(tempNull, HASH_POS(i, 1), 1);
//	}
//
//	return true; // if the value of 'false' is returned, this testcase would be skipped. 
//}
//
//void put(unsigned char key_in[MAXLEN + 1], unsigned char value_in[MAXLEN + 1]) {
//	//short keyIdx = addToHashTbl(key_in, 0);
//	//short valIdx = addToHashTbl(value_in, 1);
//	//memwrite((unsigned char*)&valIdx, HASH_POS(keyIdx, 0) + DATA_LEN, IDX_LEN); // 대신 idx를 int 대신 short로 해줘야함.
//	//memwrite((unsigned char*)&keyIdx, HASH_POS(valIdx, 1) + DATA_LEN, IDX_LEN); // 대신 idx를 int 대신 short로 해줘야함.
//
//	int keyIdx = addToHashTbl(key_in, 0);
//	int valIdx = addToHashTbl(value_in, 1);
//	// 요렇게 해도 되지만 위에처럼 강제 형변환을 해도 됨
//	// 0~2399 -> char로 바꿀려면
//	// 2399의 위에 2개(23), 아래두개(99)로 바꿈
//	unsigned char tempStr[2];
//	tempStr[0] = valIdx / 100; // 23
//	tempStr[1] = valIdx % 100; // 99
//	memwrite(tempStr, HASH_POS(keyIdx, 0) + DATA_LEN, IDX_LEN); // key뒤에는 val의 idx(hash)를 붙이고,
//
//	tempStr[0] = keyIdx / 100; // 23
//	tempStr[1] = keyIdx % 100; // 99
//	memwrite(tempStr, HASH_POS(valIdx, 1) + DATA_LEN, IDX_LEN); // value뒤에는 key의 idx(hash)를 붙임.
//	
//}
//
//void del(unsigned char key_in[MAXLEN + 1]) {
//	int keyIdx= findHashIndex(key_in, 0);
//	unsigned char tempStr[IDX_LEN] = { 0, };
//
//	int valIdx;
//	memread(tempStr, HASH_POS(keyIdx, 0) + DATA_LEN, IDX_LEN);
//	valIdx = tempStr[0] * 100 + tempStr[1];
//
//	tempStr[0] = 0;
//	memwrite(tempStr, HASH_POS(keyIdx, 0), 1);
//	memwrite(tempStr, HASH_POS(valIdx, 1), 1);
//}
//
//void get(unsigned char key_in[MAXLEN + 1], unsigned char value_out[MAXLEN + 1]) {
//	int keyIdx = findHashIndex(key_in, 0);
//
//	unsigned char tempStr[IDX_LEN] = { 0, };
//	int valIdx;
//	memread(tempStr, HASH_POS(keyIdx, 0) + DATA_LEN, IDX_LEN);
//	valIdx = tempStr[0] * 100 + tempStr[1];
//
//	memread(value_out, HASH_POS(valIdx, 1), DATA_LEN);
//	decode(value_out);
//}
//
//void getkey(unsigned char value_in[MAXLEN + 1], unsigned char key_out[MAXLEN + 1]) {
//	int valIdx = findHashIndex(value_in, 1);
//
//	unsigned char tempStr[IDX_LEN] = { 0, };
//	int keyIdx;
//	memread(tempStr, HASH_POS(valIdx, 1) + DATA_LEN, IDX_LEN);
//	keyIdx = tempStr[0] * 100 + tempStr[1];
//
//	memread(key_out, HASH_POS(keyIdx, 0), DATA_LEN);
//	decode(key_out);
//}