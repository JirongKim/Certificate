#include <stdio.h>

#define MAX_NEWS 50001
#define MAX_USER 100001
#define MAX_SEC 10
#define SCORE(x,y) (x<<16) | (y)

struct NEWS
{
	unsigned short id, s, si;
	unsigned int score;
	bool isDeleted;
} news[MAX_NEWS];

struct SEC
{
	int heap[MAX_NEWS * 3];
	int size = 0;

	void init(void) { size = 0; }

	int push(int value)
	{
		heap[size] = value;

		int cur = size;
		while (cur > 0 && heap[cur] > heap[(cur - 1) / 2])
		{
			int temp = heap[(cur - 1) / 2];
			heap[(cur - 1) / 2] = heap[cur];
			heap[cur] = temp;
			cur = (cur - 1) / 2;
		}

		size = size + 1;
		return 1;
	}

	int heapPop(void)
	{
		if (size <= 0) { return -1; }

		int t = heap[0];
		size = size - 1;

		heap[0] = heap[size];

		int cur = 0;
		while (cur * 2 + 1 < size)
		{
			int child;
			if (cur * 2 + 2 == size)
			{
				child = cur * 2 + 1;
			}
			else
			{
				child = heap[cur * 2 + 1] > heap[cur * 2 + 2] ? cur * 2 + 1 : cur * 2 + 2;
			}

			if (heap[cur] > heap[child])
			{
				break;
			}

			int temp = heap[cur];
			heap[cur] = heap[child];
			heap[child] = temp;

			cur = child;
		}
		return t;
	}
} sec[MAX_SEC];

unsigned short user[MAX_USER]; //tc 당 100씩 추가 할 것.
unsigned short deleted[MAX_SEC][5000];
int dnum[MAX_SEC];

int tc = 0;

void init()
{
	tc++;
	for (int i = 0; i < MAX_SEC; i++)
	{
		sec[i].init();
		dnum[i] = 0;
	}
}

void addNews(int mSection, int mNewsId)
{
	news[mNewsId].id = mNewsId;
	news[mNewsId].isDeleted = 0;
	news[mNewsId].s = mSection;
	news[mNewsId].score = SCORE(0, mNewsId);

	sec[mSection].push(news[mNewsId].score);
}

void eraseNews(int mNewsId)
{
	NEWS& temp = news[mNewsId];
	temp.isDeleted = 1;

	deleted[temp.s][dnum[temp.s]++] = temp.id;
}

void readNews(int mUserId, int mNewsId)
{
	NEWS& temp = news[mNewsId];
	temp.score += (1 << 16);
	user[mUserId] = temp.s + (tc * 100);

	sec[temp.s].push(temp.score);
}

void changeSection(int mNewsId, int mSection)
{
	NEWS& temp = news[mNewsId];
	deleted[temp.s][dnum[temp.s]++] = temp.id;

	temp.s = mSection;
	sec[temp.s].push(temp.score);
}

int cc[MAX_USER];
int cnum = 0;
int getList(int mUserId, int mList[])
{
	cnum++;
	unsigned int popList[MAX_NEWS];
	unsigned short popList2[MAX_NEWS];
	int pl = 0;
	unsigned int list[11];
	int lnum = 0;
	for (int i = 0; i < 11; i++) { list[i] = 0; }

	for (int i = 0; i < MAX_SEC; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			L:
			int temp = sec[i].heapPop();
			if (temp == -1) { break; }

			for (int k = 0; k < dnum[i]; k++)
			{
				if (deleted[i][k] == (temp & 0xFFFF))
				{
					goto L;
				}
			}

			if (cc[(temp & 0xFFFF)] == cnum) { goto L; }
			cc[(temp & 0xFFFF)] = cnum;

			popList[pl] = temp;
			popList2[pl++] = i;

			if (i + (tc * 100) == user[mUserId]) { temp += (10 << 16); }

			int k;
			for (k = 0; k < 11; k++)
			{
				if (temp > list[k])
				{
					for (int l = lnum++; l > k; l--)
					{
						list[l] = list[l - 1];
					}
					list[k] = temp;

					if (lnum == 11) { lnum = 10; }
					break;
				}
				else
				{
					continue;
				}
			}
		}
	}

	for (int i = 0; i < lnum; i++)
	{
		mList[i] = (list[i] & 0xFFFF);
		//printf("%d ", mList[i]);
	}
	//printf("\n");

	for (int i = 0; i < pl; i++)
	{
		sec[popList2[i]].push(popList[i]);
	}

	return lnum;
}