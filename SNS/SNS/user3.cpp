#define MAX_USER      1000
#define MAX_TAG       5000
#define MAX_TABLE     20007
#define hash(n) (n % MAX_TABLE)
#define getScore(t, id) ((t << 10) + (MAX_USER - id))
#define ull unsigned long long
#define R register

struct MSG
{
    ull score;
	int mid;
    int uid;
} msg[MAX_TABLE];

MSG user[MAX_USER][5];
int user_follow[MAX_USER][MAX_USER];
int user_follow_cnt[MAX_USER];

struct TAG
{
	ull score;
	int mid;
	ull tagName;
};
TAG hTable[MAX_TABLE][5];

void insertionSort(MSG s1[], MSG s2)
{
	R int i = 0;
	while (i < 5 && s1[i].uid != 1000)
	{
		if (s1[i].score < s2.score)
		{
			for (R int j = 4; j > i; j--)
			{
				s1[j] = s1[j - 1];
			}
			break;
		}
		i++;
	}
	if (i < 5)
	{
		s1[i] = s2;
	}
}

void insertionSort_TAG(TAG s1[], TAG s2)
{
	R int i = 0;
	while (i < 5 && s1[i].tagName != 0)
	{
		if (s1[i].score < s2.score)
		{
			for (R int j = 4; j > i; j--)
			{
				s1[j] = s1[j - 1];
			}
			break;
		}
		i++;
	}
	if (i < 5)
	{
		s1[i] = s2;
	}
}

void init()
{
	for (R int i = 0; i < MAX_USER; i++)
	{
		user_follow_cnt[i] = 0;
		user_follow[i][user_follow_cnt[i]++] = i;
		for (R int j = 0; j < 5; j++)
		{
			user[i][j].uid = 1000;
		}
	}
	for (R int i = 0; i < MAX_TABLE; i++)
	{
		for (R int j = 0; j < 5; j++)
		{
			hTable[i][j].tagName = 0;
		}
	}
}

void addTag(ull tagName, TAG t)
{
	R int key = hash(tagName);
	while (1)
	{
		if (hTable[key][0].tagName == 0 || hTable[key][0].tagName == tagName)
		{
			insertionSort_TAG(hTable[key], t);
			break;
		}
		key++;
		key = hash(key);
	}
}

int findTag(ull tagName)
{
	R int key = hash(tagName);
	while (1)
	{
		if (hTable[key][0].tagName == tagName || hTable[key][0].tagName == 0)
		{
			return key;
		}
		key++;
		key = hash(key);
	}
}

void createMessage(int msgID, int userID, char msgData[])
{
	R int time = 0;
	time = time * 10 + (msgData[0] - '0');
	time = time * 10 + (msgData[1] - '0');
	time = time * 10 + (msgData[3] - '0');
	time = time * 10 + (msgData[4] - '0');
	time = time * 10 + (msgData[6] - '0');
	time = time * 10 + (msgData[7] - '0');
	
	R ull score = getScore((ull)time, (ull)userID);
	R MSG nMsg;
	nMsg.uid = userID;
	nMsg.mid = msgID;
	nMsg.score = score;
	insertionSort(user[userID], nMsg);

	R int sp = 9;
	while (1)
	{
		R ull tagName = 0;
		while (msgData[++sp] != ' ' && msgData[sp] != '\0')
		{
			tagName = tagName << 5;
			tagName = tagName + (msgData[sp] - 'a' + 1);
		}
		R TAG t;
		t.tagName = tagName;
		t.mid = msgID;
		t.score = score;
		addTag(tagName, t);

		if (msgData[sp] == '\0')
		{
			break;
		}
		sp++;
	}
}

void followUser(int userID1, int userID2)
{
	user_follow[userID1][user_follow_cnt[userID1]++] = userID2;
}

int searchByHashtag(char tagName[], int retIDs[])
{
	R ull hashTag = 0;
	for (R int i = 1; tagName[i] != '\0'; i++)
	{
		hashTag = hashTag << 5;
		hashTag = hashTag + (tagName[i] - 'a' + 1);
	}

	R int cnt = 0;
	R int key = findTag(hashTag);
	if (hTable[key][0].tagName == 0)
	{
		return 0;
	}
	for (R int i = 0; hTable[key][i].tagName != 0 && i < 5; i++)
	{
		retIDs[i] = hTable[key][i].mid;
		cnt++;
	}

	return cnt;
}

int getMessages(int userID, int retIDs[])
{
	R MSG ret[5];
	ret[0].uid = ret[1].uid = ret[2].uid = ret[3].uid = ret[4].uid = 1000;

	for (R int i = 0; i < user_follow_cnt[userID]; i++)
	{
		R int uID = user_follow[userID][i];
		for (R int j = 0; user[uID][j].uid != 1000 && j < 5; j++)
		{
			insertionSort(ret, user[uID][j]);
		}
	}

	R int cnt = 0;
	for (R int i = 0; ret[i].uid != 1000 && i < 5; i++)
	{
		retIDs[i] = ret[i].mid;
		cnt++;
	}
	return cnt;
}