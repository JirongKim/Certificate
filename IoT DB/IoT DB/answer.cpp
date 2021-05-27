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
//#define DATA_LEN 11 //12���� �����ؼ� 11�� ��.
//#define IDX_LEN 2
//#define STRUCT_LEN (DATA_LEN + IDX_LEN)
//#define HASH_POS(hashKey, isVal) (hashKey * STRUCT_LEN + (isVal * MAX_TABLE * STRUCT_LEN)) //+�޺κ��� ����,�������̺��� �����¹��.
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
//	if (mstrlen(data) < MAXLEN) return; //12���� ������ ������ �ʿ䰡 ����.
//
//	for (int i = 0; i < 8; i++)
//	{
//		// data[11]; -> data[0~7]�� �ֻ��� ��Ʈ���� �ø�.
//		if (data[11] & (1 << i)) //�갡 ���� on�̸�
//		{
//			data[i] += (1 << 7); //0~7�� �ֻ��� ��Ʈ�� on �����ش�.
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
//		// data[0~7]�� �ֻ��� ��Ʈ�� data[11]�� 0~7��Ʈ�� ������.
//		if (data[i] & (1 << 7)) //�갡 ���� on�̸�
//		{
//			data[11] += (1 << i); //0~7�� �ֻ��� ��Ʈ�� ����������, data[11]�� ���������� shift��Ų�� �����ش�.
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
//		memread(tempStr, HASH_POS(hashKey,isVal), 1); // ������ ���ڿ� 1���� �����ؼ� 11����Ʈ�� �����, �ű⿡ ��ġ������ ���� 2����Ʈ���� �ؼ� 13����Ʈ��.
//		if (tempStr[0] == 0)
//		{
//			//���� ����ִ� ��쿡?
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
//		if (mstrncmp(tempStr, data, DATA_LEN) == 0)// ã����
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
//	//memwrite((unsigned char*)&valIdx, HASH_POS(keyIdx, 0) + DATA_LEN, IDX_LEN); // ��� idx�� int ��� short�� �������.
//	//memwrite((unsigned char*)&keyIdx, HASH_POS(valIdx, 1) + DATA_LEN, IDX_LEN); // ��� idx�� int ��� short�� �������.
//
//	int keyIdx = addToHashTbl(key_in, 0);
//	int valIdx = addToHashTbl(value_in, 1);
//	// �䷸�� �ص� ������ ����ó�� ���� ����ȯ�� �ص� ��
//	// 0~2399 -> char�� �ٲܷ���
//	// 2399�� ���� 2��(23), �Ʒ��ΰ�(99)�� �ٲ�
//	unsigned char tempStr[2];
//	tempStr[0] = valIdx / 100; // 23
//	tempStr[1] = valIdx % 100; // 99
//	memwrite(tempStr, HASH_POS(keyIdx, 0) + DATA_LEN, IDX_LEN); // key�ڿ��� val�� idx(hash)�� ���̰�,
//
//	tempStr[0] = keyIdx / 100; // 23
//	tempStr[1] = keyIdx % 100; // 99
//	memwrite(tempStr, HASH_POS(valIdx, 1) + DATA_LEN, IDX_LEN); // value�ڿ��� key�� idx(hash)�� ����.
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