//#include <stdio.h>

#define NULL 0
#define nullptr 0
#define MAX_M 101
#define MAX_BID 40001
#define MAX_BOOK 100
#define MAX_BNB 10001
#define rint register int
#define score(price, rating, bid) (price << 19 | (5 - rating) << 16 | (MAX_BID - bid))

struct BNB
{
	short book[MAX_BOOK];
	int score;
} bnb[MAX_BID];

struct POS
{
	int bnd_idx;
	POS* prev;
} a[MAX_BNB];

int arr_idx = 0;
POS* myalloc(void) { return &a[arr_idx++]; }

POS* xy[MAX_M][MAX_M];

int arr_bnb[MAX_BNB];
int arr_bnb_cnt = 0;

void init(int M)
{
	arr_idx = 0;
	for (rint i = 0; i <= M; i++)
	{
		for (rint j = 0; j <= M; j++)
		{
			xy[i][j] = nullptr;
		}
	}

	for (rint i = 0; i < arr_bnb_cnt; i++)
	{
		for (rint j = 0; j < MAX_BOOK; j++)
		{
			bnb[arr_bnb[i]].book[j] = 0;
		}
	}
	arr_bnb_cnt = 0;
}

void add_bnb(int bid, int y, int x, int price, int rating)
{
	bnb[bid].score = score(price, rating, bid);
	//printf("score : %d\n", bnb[bid].score);

	POS* newNode = myalloc();
	newNode->bnd_idx = bid;
	newNode->prev = xy[x][y];
	xy[x][y] = newNode;

	arr_bnb[arr_bnb_cnt++] = bid;
}

int reserve(int bid, int cday, int night)
{
	for (rint i = 0; i < night; i++)
	{
		if (bnb[bid].book[cday + i] != 0) { return 0; }
	}

	for (rint i = 1; i < night; i++)
	{
		bnb[bid].book[cday + i] = 1;
	}
	bnb[bid].book[cday] = 10;
	return 1;
}

int cancel(int bid, int cday)
{
	if (bnb[bid].book[cday] < 10)
	{
		return 0;
	}

	for (rint i = 1; i < 7; i++)
	{
		if (bnb[bid].book[cday + i] == 10) { break; }
		bnb[bid].book[cday + i] = 0;
	}
	bnb[bid].book[cday] = 0;
	return 1;
}

void insertionSort(int top5_bid[5], int score)
{
	int i, j;
	for (i = 0; i < 5; i++)
	{
		if (top5_bid[i] > score)
		{
			for (j = 3; j >= i ; j--)
			{
				top5_bid[j + 1] = top5_bid[j];
			}
			top5_bid[i] = score;
			break;
		}
	}
}

int search(int opt, int y, int x, int cday, int night, int top5_bid[5])
{
	for (rint i = 0; i < 5; i++)
	{
		top5_bid[i] = 10e9;
	}

	int cnt = 0;
	if (opt == 1)
	{
		for (rint i = x - 1; i <= x + 1; i++)
		{
			if (i < 0) { continue; }
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (j < 0) { continue; }
				for (POS* pp = xy[i][j]; pp != NULL; pp = pp->prev)
				{
					int idx = pp->bnd_idx;
					int flag = 0;
					for (int k = 0; k < night; k++)
					{
						if (bnb[idx].book[cday + k] != 0) { flag = 1; break; }
					}
					if (flag == 1) { continue; }

					insertionSort(top5_bid, bnb[idx].score);
					cnt++;
				}
			}
		}
	}
	else
	{
		for (POS* pp = xy[x][y]; pp != NULL; pp = pp->prev)
		{
			int idx = pp->bnd_idx;
			int flag = 0;
			for (rint k = 0; k < night; k++)
			{
				if (bnb[idx].book[cday + k] != 0) { flag = 1; break; }
			}
			if (flag == 1) { continue; }

			insertionSort(top5_bid, bnb[idx].score);
			cnt++;
		}
	}
	if (cnt > 5)
	{
		cnt = 5;
	}
	for (rint i = 0; i < cnt; i++)
	{
		top5_bid[i] = MAX_BID - (top5_bid[i] & 0x0000ffff);
		//printf("%d ", top5_bid[i]);
	}
	//printf("\n");
	return cnt;
}