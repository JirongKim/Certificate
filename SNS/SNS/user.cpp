#define MAX_USER 1010
#define MAX_TAG 200007 //5000*2+7
#define MAX_MESSAGE 1000031

#define NULL 0
#define nullptr 0

int mstrcmp(const char* a, const char* b)
{
	register int i;
	for (i = 0; a[i] != '\0'; ++i) if (a[i] != b[i]) return a[i] - b[i];
	return a[i] - b[i];
}

int mstrcpy(char* dest, const char* src)
{
	register int i = 0;
	while (src[i] != ' ' && src[i] != '\0') { dest[i] = src[i]; i++; }
	dest[i] = src[i];
	return i;
}

unsigned long hash(const char* str)
{
	unsigned long hash = 5381;
	register int cc;

	while (cc = *str++)
	{
		hash = (((hash << 5) + hash) + cc) % MAX_TAG;
	}

	return hash % MAX_TAG;
}

struct MSG
{
	char hashtag[10];
	int time;
	int msgID;
	int userID;
	MSG* prev;
} b[MAX_TAG];
MSG c[MAX_MESSAGE];

int arr_ibx = 0;
MSG* myalloc_hashtag(void) { return &b[arr_ibx++]; }
MSG* newTag;
MSG* hashtagTable[MAX_TAG];

int arr_icx = 0;
MSG* userMsg;
MSG* myalloc_user(void) { return &c[arr_icx++]; }
MSG* myPost[MAX_USER];

MSG userTopFive[MAX_USER][5];

int user_following[MAX_USER][MAX_USER];
int user_following_count[MAX_USER];

void init()
{
	arr_ibx = 0;
	arr_icx = 0;
	for (register int i = 0; i < MAX_USER; i++) {
		for (register int j = 0; j < MAX_USER; j++)
		{
			user_following[i][j] = 0;
		}
		user_following_count[i] = 0;
		user_following[i][user_following_count[i]++] = i;
		myPost[i] = nullptr;
		for (register int j = 0; j < 5; j++)
		{
			userTopFive[i][j].userID = 1000;
		}
	}

	for (register int i = 0; i < MAX_TAG; i++)
	{
		hashtagTable[i] = nullptr;
	}
	newTag = nullptr;
	userMsg = nullptr;
}

void createMessage(int msgID, int userID, char msgData[])
{
	register int msgTime = 0;
	msgTime = msgData[0] - '0';
	msgTime = (msgTime * 10) + msgData[1] - '0';
	msgTime = (msgTime * 10) + msgData[3] - '0';
	msgTime = (msgTime * 10) + msgData[4] - '0';
	msgTime = (msgTime * 10) + msgData[6] - '0';
	msgTime = (msgTime * 10) + msgData[7] - '0';


	userMsg = myalloc_user();
	userMsg->msgID = msgID;
	userMsg->userID = userID;
	userMsg->time = msgTime;
	userMsg->prev = myPost[userID];
	myPost[userID] = userMsg;

	MSG tt = *userMsg;
	register int i, j;
	i = j = 0;
	for (i = 0; i < 5; i++) // insertion Sort
	{
		if (userTopFive[userID][i].userID == 1000) { break; }
		if (tt.time > userTopFive[userID][i].time) { break; }
		else if (tt.time == userTopFive[userID][i].time && tt.userID < userTopFive[userID][i].userID) { break; }
	}
	for (j = 3; j >= i; j--)
	{
		userTopFive[userID][j + 1] = userTopFive[userID][j];
	}
	userTopFive[userID][i] = tt;

	i = 9; // hashTag 부분 문자열 추출
	char temp[10];
	while (1)
	{
		register int flag = mstrcpy(temp, &msgData[i]);
		temp[flag] = '\0';

		register int key = int(hash(&temp[1])); //#부분은 제외하고 Hashing
		newTag = myalloc_hashtag();
		newTag->msgID = msgID;
		newTag->userID = userID;
		newTag->time = msgTime;
		mstrcpy(newTag->hashtag, temp);
		newTag->prev = hashtagTable[key];
		hashtagTable[key] = newTag;

		if (msgData[i + flag] == '\0') { break; }
		i += flag + 1; // i+1를 해줘서, 다음 문자열로 옮김.
	}
	//printf("\n");
}

void followUser(int userID1, int userID2)
{
	user_following[userID1][user_following_count[userID1]++] = userID2;
}

int searchByHashtag(char tagName[], int retIDs[])
{
	MSG rank[7];
	for (int i = 0; i < 6; i++) { rank[i].msgID = 0; }
	register int i, j, r;
	i = j = r = 0;

	register int count = 0;
	register int key = int(hash(&tagName[1]));
	for (MSG* pp = hashtagTable[key]; pp != NULL; pp = pp->prev)
	{
		if (mstrcmp(pp->hashtag, tagName)) { continue; } // hashTag가 다른데, hashing 값만 같으면 continue

		count++; //게시글이 한개도 없는경우
		for (i = 0; i < r; i++) // insertion Sort
		{
			if (rank[i].time < pp->time) { break; }
			else if (rank[i].time == pp->time && rank[i].userID > pp->userID) { break; }
		}
		for (j = r; j >= i; j--)
		{
			rank[j + 1] = rank[j];
		}
		rank[i] = *pp;
		r++;
		if (r == 6) { r = 5; }
	}

	if (count < 5 && r == 5) { r = r - 1; } // r에 4개만 들어있으면 r--

	for (i = 0; i < r; i++)
	{
		retIDs[i] = rank[i].msgID;
	}
	return r;
}

int getMessages(int userID, int retIDs[])
{
	MSG rank[7];
	for (int i = 0; i < 7; i++) { rank[i].msgID = 0; }
	register int i, j, r;
	i = j = r = 0;

	register int count = 0;
	for (register int k = 0; k < user_following_count[userID]; k++)
	{
		register int temp = user_following[userID][k];
		for (register int aa = 0; aa < 5; aa++)
		{
			MSG pp = userTopFive[temp][aa];
			if (pp.userID == 1000) { break; }
			count++; //게시글이 한개도 없는경우
			for (i = 0; i < r; i++) // insertion Sort
			{
				if (rank[i].time < pp.time) { break; }
				else if (rank[i].time == pp.time && rank[i].userID > pp.userID) { break; }
			}
			for (j = r; j >= i; j--)
			{
				rank[j + 1] = rank[j];
			}
			rank[i] = pp;
			r++;
			if (r == 6) { r = 5; }
		}
	}

	if (count == 0) { return 0; } //자기 자신만 follow 하는건 아닌지 check
	if (count < 5 && r == 5) { r = r - 1; } // r에 4개만 들어있으면 r--

	for (i = 0; i < r; i++)
	{
		retIDs[i] = rank[i].msgID;
	}
	return r;
}