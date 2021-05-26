#define NULL 0
#define nullptr 0
#define MAXM	3
#define MAX_USER 1001
#define MAX_MSG 100001

#define uint unsigned int
#define rint register int

struct RECV;

struct SEND
{
	uint ts;
	uint sendTS;
	int from;
	int to;
	int mID;
	bool isDelete;
	bool isRead;
	RECV* recv;
	SEND* prev;
} s[MAX_MSG];

struct RECV
{
	uint ts;
	int from;
	int to;
	int mID;
	bool isDelete;
	bool isRead;
	SEND* send;
	RECV* prev;
} r[MAX_MSG];

int arr_s = 0;
int arr_r = 0;
SEND* myalloc_send(void) { s[arr_s].isDelete = s[arr_s].isRead = 0; return &s[arr_s++]; }
RECV* myalloc_recv(void) { r[arr_r].isDelete = r[arr_r].isRead = 0; return &r[arr_r++]; }

SEND* user_send[MAX_USER];
RECV* user_recv[MAX_USER];

void init(int N)
{
	arr_r = arr_s = 0;
	for (rint i = 0; i <= N; i++)
	{
		user_send[i] = nullptr;
		user_recv[i] = nullptr;
	}
}

void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp)
{
	SEND* sd = myalloc_send();
	sd->from = uID1;
	sd->to = uID2;
	sd->mID = mID;
	sd->ts = cTimestamp;
	sd->sendTS = scheduleTimestamp;

	RECV* rv = myalloc_recv();
	rv->from = uID1;
	rv->to = uID2;
	rv->mID = mID;
	rv->ts = scheduleTimestamp;

	sd->recv = rv;
	rv->send = sd;
	sd->prev = user_send[uID1];
	user_send[uID1] = sd;

	// linked list Á¤·Ä
	if (user_recv[uID2] == NULL)
	{
		rv->prev = user_recv[uID2];
		user_recv[uID2] = rv;
	}
	else
	{
		int flag = 0;
		RECV* temp = NULL;
		for (RECV* cur = user_recv[uID2]; cur != NULL; temp = cur, cur = cur->prev)
		{
			if (rv->ts >= cur->ts)
			{
				if (rv->ts == cur->ts && rv->mID < cur->mID) { continue; }
				if (temp == NULL)
				{
					flag = 1;
					user_recv[uID2] = rv;
					rv->prev = cur;
					break;
				}
				else
				{
					flag = 1;
					temp->prev = rv;
					rv->prev = cur;
					break;
				}
			}
		}
		if(flag==0){
			temp->prev = rv;
			rv->prev = NULL;
		}
	}

	/*for (SEND* pp = user_send[uID1]; pp != NULL; pp = pp->prev)
	{
		printf("From : %d, To : %d, mID : %d, Send.ts : %d\n", pp->from, pp->to, pp->mID, pp->ts);
	}
	for (RECV* pp = user_recv[uID2]; pp != NULL; pp = pp->prev)
	{
		printf("To : %d, From : %d, mID : %d, Recv.ts : %d\n", pp->to, pp->from, pp->mID, pp->ts);
	}
	printf("\n");*/
}

int retrieveSentbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
	int cnt = 0;
	for (SEND* pp = user_send[uID]; pp != NULL && cnt != 3; pp = pp->prev)
	{
		if (pp->isDelete == 1) { continue; }
		mIDList[cnt] = pp->mID;
		uIDList[cnt] = pp->to;
		readList[cnt] = pp->isRead;
		cnt++;
	}

	/*for (int i = 0; i < cnt; i++)
	{
		printf("mIDList[%d] : %d\n", i, mIDList[i]);
	}
	for (int i = 0; i < cnt; i++)
	{
		printf("uIDList[%d] : %d\n", i, uIDList[i]);
	}
	for (int i = 0; i < cnt; i++)
	{
		printf("readList[%d] : %d\n", i, readList[i]);
	}
	printf("\n");*/
	return cnt;
}

int retrieveInbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
	int cnt = 0;
	for (RECV* pp = user_recv[uID]; pp != NULL && cnt != 3; pp = pp->prev)
	{
		if (pp->isDelete == 1 || pp->ts > cTimestamp) { continue; }
		mIDList[cnt] = pp->mID;
		uIDList[cnt] = pp->from;
		readList[cnt] = pp->isRead;
		cnt++;
	}

	/*for (int i = 0; i < cnt; i++)
	{
		printf("mIDList[%d] : %d\n", i, mIDList[i]);
	}
	for (int i = 0; i < cnt; i++)
	{
		printf("uIDList[%d] : %d\n", i, uIDList[i]);
	}
	for (int i = 0; i < cnt; i++)
	{
		printf("readList[%d] : %d\n", i, readList[i]);
	}
	printf("\n");*/
	return cnt;
}

int readMessage(int cTimestamp, int uID, int mID)
{
	for (RECV* pp = user_recv[uID]; pp != NULL; pp = pp->prev)
	{
		if (pp->mID != mID) { continue; }
		if (pp->isDelete == 1 || pp->ts > cTimestamp) { continue; }
		pp->isRead = 1;
		pp->send->isRead = 1;
		return 1;
	}

	for (SEND* pp = user_send[uID]; pp != NULL; pp = pp->prev)
	{
		if (pp->mID != mID) { continue; }
		if (pp->isDelete == 1) { continue; }
		return 1;
	}
	return 0;
}

int deleteMessage(int cTimestamp, int uID, int mID)
{
	for (RECV* pp = user_recv[uID]; pp != NULL; pp = pp->prev)
	{
		if (pp->mID != mID) { continue; }
		if (pp->isDelete == 1 || pp->ts > cTimestamp) { continue; }
		pp->isDelete = 1;
		return 1;
	}

	for (SEND* pp = user_send[uID]; pp != NULL; pp = pp->prev)
	{
		if (pp->mID != mID) { continue; }
		if (pp->isDelete == 1) { continue; }
		pp->isDelete = 1;
		if (pp->sendTS > cTimestamp)
		{
			pp->recv->isDelete = 1;
		}
		return 1;
	}

	return 0;
}