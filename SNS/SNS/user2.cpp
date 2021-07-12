#include <stdio.h>
#include <algorithm>

#define MAX_USER      1000
#define MAX_TAG       5000
#define MAX_TABLE	  10007
#define NULL 0
#define ull unsigned long long

struct MSG
{
	int score;
	int mid;
	MSG* prev;
} msg[50000];
int arr_idx;
MSG* myalloc(void) { return &msg[arr_idx++]; }

MSG user[MAX_USER][6];
int user_cnt[MAX_USER];
int follow[MAX_USER][MAX_USER];
int follow_cnt[MAX_USER];

struct HASH
{
	ull val;
	int top_score[6];
	int top_mid[6];
	int tnum;
} hTable[MAX_TABLE];

bool compare(const MSG& p1, const MSG& p2) {
	return p1.score > p2.score;
}

void init()
{
	arr_idx = 0;
	for (int i = 0; i < MAX_USER; i++)
	{
		user_cnt[i] = 0;
		follow_cnt[i] = 1;
		follow[i][0] = i;
	}

	for (int i = 0; i < MAX_TABLE; i++)
	{
		hTable[i].val = 0;
		hTable[i].tnum = 0;
	}
}

void createMessage(int msgID, int userID, char msgData[])
{
	int time = 0;
	time = (msgData[7] - '0') + (msgData[6] - '0') * 10 +
		(msgData[4] - '0') * 100 + (msgData[3] - '0') * 1000 +
		(msgData[1] - '0') * 10000 + (msgData[0] - '0') * 100000;

	int score = (time << 10) + (MAX_USER - userID);

	MSG* newMsg = myalloc();
	newMsg->score = score;
	newMsg->mid = msgID;

	/*if (user_cnt[userID] == 0)
	{
		user[userID][0].score = score;
		user[userID][0].mid = msgID;
		user_cnt[userID]++;
	}
	else if (!(user_cnt[userID] >= 5 && user[userID][4].score > score))
	{
		if (user_cnt[userID] > 5) { user_cnt[userID] = 5; }

		for (int i = user_cnt[userID] - 1; i >= 0; i--)
		{
			user[userID][i + 1] = user[userID][i];
			if (user[userID][i].score < score)
			{
				user[userID][i].score = score;
				user[userID][i].mid = msgID;
				user_cnt[userID]++;
				break;
			}
		}
	}*/

	user[userID][user_cnt[userID]].score = score;
	user[userID][user_cnt[userID]].mid = msgID;
	user_cnt[userID]++;
	if (user_cnt[userID] == 6)
	{
		user_cnt[userID] = 5;
	}
	std::sort(user[userID], user[userID] + user_cnt[userID], compare);

	int sp = 9;
	while (1)
	{
		if (msgData[sp] != '#') { break; }

		ull str = 0;
		sp++; //#에서 벗어나기 위한 +

		while (1)
		{
			if (msgData[sp] == ' ' || msgData[sp] == '\0') { break; }
			str = (str << 5);
			str = str | (ull)(msgData[sp] - 'a' + 1);
			sp++; //\0로 가기위한 +
		}

		int key = str % MAX_TABLE;
		while (1)
		{
			if (hTable[key].val == str || hTable[key].val == 0)
			{
				break;
			}
			key++;
			key = key % MAX_TABLE;
		}

		hTable[key].val = str;
		


		/*if (hTable[key].tnum == 0)
		{
			hTable[key].top_score[0] = score;
			hTable[key].top_mid[0] = msgID;
			hTable[key].tnum++;
		}
		else if (!(hTable[key].tnum >= 5 && hTable[key].top_score[4] > score))
		{
			if (hTable[key].tnum > 5) { hTable[key].tnum = 5; }

			for (int i = hTable[key].tnum - 1; i >= 0; i--)
			{
				hTable[key].top_score[i + 1] = hTable[key].top_score[i];
				hTable[key].top_mid[i + 1] = hTable[key].top_mid[i];
				if (hTable[key].top_score[i] < score)
				{
					hTable[key].top_score[i] = score;
					hTable[key].top_mid[i] = msgID;
					hTable[key].tnum++;
					break;
				}
			}
		}*/

		sp++; //\0에서 #으로 가기위한 +
	}
}

void followUser(int userID1, int userID2)
{
	follow[userID1][follow_cnt[userID1]++] = userID2;
}

int searchByHashtag(char tagName[], int retIDs[])
{
	ull str = 0;

	for (int i = 1; tagName[i] != '\0'; i++)
	{
		str = (str << 5);
		str = str | (ull)(tagName[i] - 'a' + 1);
	}

	int key = str % MAX_TABLE;
	int nc = 0;
	while (1)
	{
		if (hTable[key].val == str)
		{
			break;
		}
		key++;
		key = key % MAX_TABLE;
		nc++;
		if (nc > MAX_TABLE) { return 0; }
	}

	printf("HashTag Result : \n");
	if (hTable[key].tnum > 5)
	{
		hTable[key].tnum = 5;
	}

	for (int i = 0; i < hTable[key].tnum; i++)
	{
		retIDs[i] = hTable[key].top_mid[i];
		printf("%d \n", retIDs[i]);
	}
	printf("\n");

 	return hTable[key].tnum;
}

int getMessages(int userID, int retIDs[])
{
	MSG top5[7] = { 0, };
	int tnum = 0;
	int k = 0;
	printf("UserID Result : \n");
	for (int i = 0; i < follow_cnt[userID]; i++)
	{
		int t = follow[userID][i];
		for (int j = 0; j < user_cnt[t]; j++)
		{
			top5[tnum].mid = user[t][j].mid;
			top5[tnum++].score = user[t][j].score;
			std::sort(top5, top5 + tnum, compare);
			if (tnum == 6)
			{
				tnum = 5;
			}
			//if (tnum == 5 && user[t][j].score > top5[tnum - 1].score) { continue; }
			//if (tnum == 0) { top5[0].mid = user[t][j].mid, top5[0].score = user[t][j].score; tnum++; continue; }
			//for (k = tnum - 1; k >= 0; k--) // 5에서 1까지.
			//{
			//	top5[k + 1].mid = top5[k].mid;
			//	top5[k + 1].score = top5[k].score;
			//	if (user[t][j].score < top5[k].score)
			//	{
			//		top5[k].mid = user[t][j].mid;
			//		top5[k].score = user[t][j].score;
			//		tnum++;
			//		if (tnum == 6) { tnum = 5; }
			//		break;
			//	}
			//}

		}
	}

	for (int i = 0; i < tnum; i++)
	{
		retIDs[i] = top5[i].mid;
		printf("%d \n", top5[i].mid);
	}
	printf("\n");
	return 0;
}