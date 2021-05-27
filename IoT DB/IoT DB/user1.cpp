///*
//  DO NOT USE ANY GLOBAL VARIABLE OR STATIC VARIABLE IN USER CODE.
//  ONLY LOCAL VARIABLE AND CONSTANT ARE ALLOWED. ALSO, IT IS NOT
//  ALLOWED TO ALLOCATE MEMORY BY CALLING malloc FUNCTION OR 'new' KEYWORD.
//*/
//
// /*The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.*/
//
// bool mstrcmp(unsigned char *a, unsigned char *b) {
//     while(*a && *a == *b)
//         ++a, ++b;
//     return *a == *b;
// }
//
// int mstrlen(unsigned char *a) {
//     int len = 0;
//     while (*a)
//         ++a, ++len;
//     return len;
// }
//
//#include <stdio.h>
//
//extern bool memread(unsigned char dest[], int pos, int len);
//extern bool memwrite(unsigned char src[], int pos, int len);
//
//#define MAXLEN 12
//#define MAX_MSTR 27
//#define MAX_TABLE (65535 - MAX_MSTR)
//
//int hash(const unsigned char* s)
//{
//	unsigned long long h[2] = { 0,0 };
//	for (int i = 0, n = 0; s[i] != '\0'; i++)
//	{
//		if (s[i] >= 'A' && s[i] <= 'Z')
//			h[n] = (h[n] << 6) + s[i] - 'A' + 1;
//		else if (s[i] >= 'a' && s[i] <= 'z')
//			h[n] = (h[n] << 6) + s[i] - 'a' + 27;
//		else if (s[i] >= '0' && s[i] <= '9')
//			h[n] = (h[n] << 6) + s[i] - '0' + 53;
//
//		if (i == 6)
//		{
//			n = n + 1;
//		}
//	}
//	int a = (int)((h[0] % MAX_TABLE) + (h[1] % MAX_TABLE)) % MAX_TABLE;
//	printf("hash : %d\n", a);
//	if (a < 0)
//	{
//		printf("Stop");
//	}
//	return a;
//}
//
//int len(const unsigned char* s)
//{
//	int i = 0;
//	for (i = 0; s[i] != '\0'; i++) {}
//	return i;
//}
//
//void makeStr(unsigned char insert[MAX_MSTR], const unsigned char* s, const unsigned char* t)
//{
//	int a = 1;
//	insert[0] = '~';
//	for (int i = 0; s[i] != '\0'; i++)
//	{
//		insert[a++] = s[i];
//	}
//	insert[a++] = '|';
//	for (int i = 0; t[i] != '\0'; i++)
//	{
//		insert[a++] = t[i];
//	}
//	insert[a++] = '!';
//	insert[a++] = '\0';
//}
//
//bool init(int N) {
//	/*unsigned char clear[MAX_TABLE + 26];
//	for (int i = 0; i < MAX_TABLE + 26; i++)
//	{
//		clear[i] = '\0';
//	}
//	memwrite(clear, 0, MAX_TABLE + 26);*/
//	return true; // if the value of 'false' is returned, this testcase would be skipped. 
//}
//
//int add(int k, const unsigned char* str)
//{
//	unsigned char temp[MAX_MSTR];
//	int l = len(str);
//
//	while (1)
//	{
//		memread(temp, k, MAX_MSTR);
//		int i = 0;
//		for (i = 0; i < MAX_MSTR; i++) {
//			if (temp[i] != '\0') { break; }
//		}
//		if (i >= l) { break; }
//		for (i; i < MAX_MSTR; i++) {
//			if (temp[i] == '\0') { break; }
//		}
//		k = (k + i) % MAX_TABLE;
//	}
//	return k;
//}
//
//int find(int k, unsigned char* str, unsigned char* value)
//{
//	unsigned char key_check[MAXLEN + 1];
//	unsigned char temp[27];
//	int l = len(str);
//	int v = 0;
//
//	while (1)
//	{
//		memread(temp, k, MAX_MSTR);
//		if (temp[0] != '~')
//		{
//			int i = 0;
//			for (i = 0; i < MAX_MSTR; i++)
//			{
//				if (temp[i] == '~')
//				{
//					break;
//				}
//			}
//			k = (k + i) % MAX_TABLE;
//			continue;
//		}
//		int i = 0;
//		for (i = 0; i < l; i++)
//		{
//			key_check[i] = temp[i]; // i+1을 해야 key_check에 ~가 정상적으로 들어감.
//		}
//		key_check[l] = '\0';
//		if (mstrcmp(key_check, str) && temp[i] == '|')
//		{
//			for (i = i + 1; temp[i] != '!'; i++)
//			{
//				value[v++] = temp[i];
//			}
//			value[v] = '\0';
//			break;
//		}
//		for (i; i < MAX_MSTR; i++) {
//			if (temp[i] == '\0') { break; }
//		}
//		k = (k + i) % MAX_TABLE;
//	}
//}
//
//void put(unsigned char key_in[MAXLEN + 1], unsigned char value_in[MAXLEN + 1]) {	
//	unsigned char insert[27];
//
//	makeStr(insert, key_in, value_in);
//
//	int k;
//	int l = len(insert);
//	k = add(hash(key_in), insert);
//	memwrite(insert, k, l);
//
//	//////
//
//	makeStr(insert, value_in, key_in);
//	k = add(hash(value_in), insert);
//	memwrite(insert, k, l);
//}
//
//void del(unsigned char key_in[MAXLEN + 1]) {
//	unsigned char insert[MAX_MSTR];
//	unsigned char value[MAXLEN + 1];
//	for (int i = 0; i < MAX_MSTR; i++) { insert[i] = '\0'; }
//	
//	int k;
//	int l = len(key_in);
//
//	k = find(hash(key_in), key_in, value);
//	memwrite(insert, k, l);
//
//	/////
//	
//	l = len(value);
//	k = find(hash(value), value, key_in);
//	memwrite(insert, k, l);
//}
//
//void get(unsigned char key_in[MAXLEN + 1], unsigned char value_out[MAXLEN + 1]) {
//	int k;
//	int l = len(key_in);
//
//	k = find(hash(key_in), key_in, value_out);
//}
//
//void getkey(unsigned char value_in[MAXLEN + 1], unsigned char key_out[MAXLEN + 1]) {
//	int k;
//	int l = len(value_in);
//
//	k = find(hash(value_in), value_in, key_out);
//}