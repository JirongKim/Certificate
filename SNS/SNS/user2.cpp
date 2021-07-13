////#include <stdio.h>
//
//#define MAX_USER      1000
//#define MAX_TAG       5000
//#define MAX_TABLE	  10007
//#define NULL 0
//#define ull unsigned long long
//
//struct MSG
//{
//	int score;
//	int mid;
//	MSG* prev;
//} msg[50000];
//int arr_idx;
//MSG* myalloc(void) { return &msg[arr_idx++]; }
//
//MSG* user[MAX_USER][5];
//int follow[MAX_USER][MAX_USER];
//int follow_cnt[MAX_USER];
//
//struct HASH
//{
//	ull val;
//	MSG* top5[5];
//} hTable[MAX_TABLE];
//
//void insertionSort(MSG* dst[], MSG* src)
//{
//	int i = 0;
//	while (i < 5 && dst[i] != 0)
//	{
//		if (dst[i]->score < src->score)
//		{
//			for (int j = 4; j > i; j--)
//			{
//				dst[j] = dst[j - 1];
//			}
//			break;
//		}
//		i++;
//	}
//	if (i < 5)
//	{
//		dst[i] = src;
//	}
//	return;
//}
//
//void init()
//{
//	arr_idx = 0;
//	for (int i = 0; i < MAX_USER; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			user[i][j] = NULL;
//		}
//		follow_cnt[i] = 1;
//		follow[i][0] = i;
//	}
//
//	for (int i = 0; i < MAX_TABLE; i++)
//	{
//		hTable[i].val = 0;
//		for (int j = 0; j < 5; j++)
//		{
//			hTable[i].top5[j] = NULL;
//		}
//	}
//}
//
//void createMessage(int msgID, int userID, char msgData[])
//{
//	int time = 0;
//	time = (msgData[7] - '0') + (msgData[6] - '0') * 10 +
//		(msgData[4] - '0') * 100 + (msgData[3] - '0') * 1000 +
//		(msgData[1] - '0') * 10000 + (msgData[0] - '0') * 100000;
//
//	int score = (time << 10) + (MAX_USER - userID);
//
//	MSG* newMsg = myalloc();
//	newMsg->score = score;
//	newMsg->mid = msgID;
//
//	insertionSort(user[userID], newMsg);
//
//	int sp = 9;
//	while (1)
//	{
//		if (msgData[sp] != '#') { break; }
//
//		ull str = 0;
//		sp++; //#에서 벗어나기 위한 +
//
//		while (1)
//		{
//			if (msgData[sp] == ' ' || msgData[sp] == '\0') { break; }
//			str = (str << 5);
//			str = str | (ull)(msgData[sp] - 'a' + 1);
//			sp++; //\0로 가기위한 +
//		}
//
//		int key = str % MAX_TABLE;
//		while (1)
//		{
//			if (hTable[key].val == str || hTable[key].val == 0)
//			{
//				break;
//			}
//			key++;
//			key = key % MAX_TABLE;
//		}
//
//		hTable[key].val = str;
//
//		insertionSort(hTable[key].top5, newMsg);
//
//		sp++; //\0에서 #으로 가기위한 +
//	}
//}
//
//void followUser(int userID1, int userID2)
//{
//	follow[userID1][follow_cnt[userID1]++] = userID2;
//}
//
//int searchByHashtag(char tagName[], int retIDs[])
//{
//	//printf("HashTag Result : \n");
//	ull str = 0;
//
//	for (int i = 1; tagName[i] != '\0'; i++)
//	{
//		str = (str << 5);
//		str = str | (ull)(tagName[i] - 'a' + 1);
//	}
//
//	int key = str % MAX_TABLE;
//	if (hTable[key].val == 0) return 0;
//	while (1)
//	{
//		if (hTable[key].val == str)
//		{
//			break;
//		}
//		key++;
//		key = key % MAX_TABLE;
//	}
//
//	int i = 0;
//	while (i < 5 && hTable[key].top5[i] != NULL)
//	{
//		retIDs[i] = hTable[key].top5[i]->mid;
//		//printf("%d \n", hTable[key].top5[i]->score);
//		i++;
//	}
//	//printf("\n");
//
//	return i;
//}
//
//int getMessages(int userID, int retIDs[])
//{
//	MSG* top5[5] = { 0, 0, 0, 0, 0 };
//	//printf("UserID Result : \n");
//	for (int i = 0; i < follow_cnt[userID]; i++)
//	{
//		int t = follow[userID][i];
//		int j = 0;
//		while (j < 5 && user[t][j] != NULL)
//		{
//			insertionSort(top5, user[t][j]);
//			j++;
//		}
//	}
//
//	int i = 0;
//	while (i < 5 && top5[i] != NULL)
//	{
//		retIDs[i] = top5[i]->mid;
//		//printf("%d \n", top5[i]->mid);
//		i++;
//	}
//	//printf("\n");
//	return i;
//}