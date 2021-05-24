#define MAX_GROUP 100
#define MAX_ID 1000
#define MAX_USER 100
#define MAX_DIF_NAME 200
#define MAX_SAME_NAME 5
#define MAX_NAME 15

void mstrcpy(char dst[], const char src[]) {
	int c = 0;
	while ((dst[c] = src[c]) != 0) ++c;
}

int mstrcmp(const char str1[], const char str2[]) {
	int c = 0;
	while (str1[c] != 0 && str1[c] == str2[c]) ++c;
	return str1[c] - str2[c];
}

struct EVENT
{
	char ename[MAX_NAME];
	int eventUid_cnt;
	int eventUid[MAX_SAME_NAME];
} eventName[MAX_GROUP][MAX_DIF_NAME];

int event_cnt[MAX_GROUP];

struct USER
{
	char ename[MAX_NAME];
	int groupID;
} user[MAX_ID][MAX_USER];

int user_cnt[MAX_ID];

void init()
{
	for (int i = 0; i < MAX_GROUP; i++)
	{
		for (int j = 0; j < MAX_DIF_NAME; j++)
		{
			eventName[i][j].eventUid_cnt = 0;
			for (int k = 0; k < MAX_SAME_NAME; k++)
			{
				eventName[i][j].eventUid[k] = 0;
			}
		}
	}
	for (int i = 0; i < MAX_ID; i++)
	{
		user_cnt[i] = 0;
	}
	for (int i = 0; i < MAX_GROUP; i++)
	{
		event_cnt[i] = 0;
	}
}

void addEvent(int uid, char ename[], int groupid)
{
	bool same = 0;
	for (int i = 0; i < event_cnt[groupid]; i++)
	{
		EVENT* temp = &eventName[groupid][i];
		if (!mstrcmp(temp->ename, ename))
		{
			temp->eventUid[temp->eventUid_cnt++] = uid;
			same = 1;
			break;
		}
	}
	
	mstrcpy(user[uid][user_cnt[uid]].ename, ename);
	user[uid][user_cnt[uid]++].groupID = groupid;

	if (same == 0)
	{
		EVENT* temp = &eventName[groupid][event_cnt[groupid]];
		mstrcpy(temp->ename, ename);
		temp->eventUid[0] = uid;
		temp->eventUid_cnt = 1;
		event_cnt[groupid]++;
	}
}

int deleteEvent(int uid, char ename[])
{
	int cnt = 1;
	bool same = 0;
	int groupID = 0;
	for (int i = 0; i < user_cnt[uid]; i++)
	{
		if (!mstrcmp(user[uid][i].ename, ename))
		{
			same = 1;
			groupID = user[uid][i].groupID;
			USER temp = user[uid][user_cnt[uid] - 1];

			user[uid][i].groupID = temp.groupID;
			mstrcpy(user[uid][i].ename, temp.ename);
			user_cnt[uid]--;
			break;
		}
	}
	if (same == 0) { return 0; }
	
	bool master = 0;
	for (int i = 0; i < event_cnt[groupID]; i++)
	{
		if (!mstrcmp(eventName[groupID][i].ename, ename))
		{
			EVENT* origin = &eventName[groupID][event_cnt[groupID] - 1];
			EVENT* temp = &eventName[groupID][i];

			if (temp->eventUid[0] == uid && temp->eventUid_cnt != 0) { master = 1; }
			else { master = 0; }

			if (master == 1)
			{
				cnt = temp->eventUid_cnt;
				mstrcpy(temp->ename, origin->ename);
				for (int j = 0; j < MAX_SAME_NAME; j++)
				{
					temp->eventUid[j] = origin->eventUid[j];
					origin->eventUid[j] = 0;
				}
				temp->eventUid_cnt = origin->eventUid_cnt;
				origin->eventUid_cnt = 0;
				event_cnt[groupID]--;
			}
			else
			{
				for (int j = 0; j < temp->eventUid_cnt; j++)
				{
					if (temp->eventUid[j] == uid)
					{
						temp->eventUid[j] = temp->eventUid[temp->eventUid_cnt - 1];
						temp->eventUid_cnt--;
						break;
					}
				}
			}
			break;
		}
	}

	return cnt;
}

int changeEvent(int uid, char ename[], char cname[])
{
	int cnt = 1;
	int same = 0;
	int groupID = 0;
	for (int i = 0; i < user_cnt[uid]; i++)
	{
		if (!mstrcmp(user[uid][i].ename, ename))
		{
			same = 1;
			groupID = user[uid][i].groupID;
			mstrcpy(user[uid][i].ename, cname);
			break;
		}
	}
	if (same == 0) { return 0; }

	bool master = 0;
	for (int i = 0; i < event_cnt[groupID]; i++)
	{
		EVENT* temp = &eventName[groupID][i];
		if (!mstrcmp(temp->ename, ename))
		{
			if (temp->eventUid[0] == uid && temp->eventUid_cnt != 0) { master = 1; }
			else { master = 0; }

			if (master == 1)
			{
				cnt = temp->eventUid_cnt;
				mstrcpy(temp->ename, cname);
			}
			else
			{
				same = -1;
				for (int j = 0; j < event_cnt[groupID]; j++)
				{
					if (!mstrcmp(eventName[groupID][j].ename, cname)) {
						same = j;
						break;
					}
				}

				if (same == -1)
				{
					mstrcpy(eventName[groupID][event_cnt[groupID]].ename, cname);
					eventName[groupID][event_cnt[groupID]].eventUid[0] = uid;
					eventName[groupID][event_cnt[groupID]++].eventUid_cnt = 1;
				}
				else
				{
					cnt = 2;
					eventName[groupID][same].eventUid[eventName[groupID][same].eventUid_cnt++] = eventName[groupID][same].eventUid[0];
					eventName[groupID][same].eventUid[0] = uid;
				}
			}
			break;
		}
	}

	return cnt;
}

int getCount(int uid)
{
	return user_cnt[uid];
}