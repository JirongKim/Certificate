//#include <stdio.h>

#define MAX_TABLE 100000
#define MAX_ARR 1001

#define NULL 0
#define nullptr 0

struct USER
{
	int following;
	USER* prev;
}a[MAX_TABLE];

struct POST
{
	int poster;
	int TS;
	int like;
	int postID;
	POST* prev;
}b[MAX_TABLE];

int arr_idx = 0;
USER* myalloc(void)
{
	return &a[arr_idx++];
}

int arr_ibx = 0;
POST* myalloc_post(void)
{
	return &b[arr_ibx++];
}

USER* user;
USER* user_Table[MAX_ARR];

POST post_Table[MAX_TABLE];

POST* post;
POST* myPost[MAX_TABLE];

int current_pID;

void init(int N)
{
	arr_idx = 0;
	arr_ibx = 0;
	for (int i = 1; i <= N; i++)
	{
		user_Table[i] = nullptr;
		user = myalloc();
		user->following = i;
		user->prev = user_Table[i];
		user_Table[i] = user;

		post_Table[i].poster = 0;
		myPost[i] = nullptr;
	}
	current_pID = 0;
}

void follow(int uID1, int uID2, int timestamp)
{
	user = myalloc();
	user->following = uID2;
	user->prev = user_Table[uID1];
	user_Table[uID1] = user;
	//for (USER* uu = user_Table[uID1]; uu != NULL; uu = uu->prev)
	//{
		//printf("%d ", uu->following);
	//}
	//printf("\n");
}

void makePost(int uID, int pID, int timestamp)
{
	post_Table[pID].poster = uID;
	post_Table[pID].TS = timestamp;
	post_Table[pID].like = 0;
	post_Table[pID].postID = pID;
	post_Table[pID].prev = NULL;
	current_pID = pID;

	post = myalloc_post();
	post = &post_Table[pID];
	post->prev = myPost[uID];
	myPost[uID] = post;
}

void like(int pID, int timestamp)
{
	post_Table[pID].like++;
}

void getFeed(int uID, int timestamp, int pIDList[])
{
	POST rank[12];
	int r = 0;
	int j = 0;

	for (USER* uu = user_Table[uID]; uu != NULL; uu = uu->prev) // getFeed한 uid가 팔로우 되어 있는지 아닌지 Check
	{
		for (POST* pp = myPost[uu->following]; pp != NULL; pp = pp->prev)
		{
			//printf("postID:%d  Poster : %d  TimeStamp : %d  Like : %d\n", pp->postID, pp->poster, pp->TS, pp->like);
			// 여기부터 랭킹매김
			int temp = timestamp - (pp->TS);
			if (r == 10 && temp > 1000 && rank[9].TS > pp->TS) {
				break;
			};
			if (temp <= 1000)
			{
				for (j = 0; j < r; j++)
				{
					if (rank[j].like < pp->like || (timestamp - rank[j].TS)>1000) { break; }
					else if (rank[j].like == pp->like && rank[j].TS < pp->TS) { break; }
				}
				for (int k = r - 1; k >= j; k--)
				{
					rank[k + 1] = rank[k];
				}
				rank[j] = *pp;
				r++;
				if (r >= 11) { r = 10; }
			}
			else
			{
				for (j = 0; j < r; j++)
				{
					if ((timestamp - rank[j].TS) > 1000 && rank[j].TS < (pp->TS)) {
						break;
					}
				}
				for (int k = r - 1; k >= j; k--)
				{
					rank[k + 1] = rank[k];
				}
				rank[j] = *pp;
				r++;
				if (r >= 11) { r = 10; }
			}
		}
	}

	//printf("uID : %d, timeStamp : %d\n", uID, timestamp);
	for (int j = 0; j < r; j++)
	{
		pIDList[j] = rank[j].postID;
		//printf("%d등 : %d\n", j, pIDList[j]);
	}
	//printf("\n");
}