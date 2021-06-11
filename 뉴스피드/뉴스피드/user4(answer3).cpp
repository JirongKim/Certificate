#define MAX_USER 100001
#define MAX_NEWS 50001
#define MAX_SECTION 10
#define ADD 60000

struct NEWS
{
	int id, s, score, idx;
} news[MAX_NEWS];

struct HEAP
{
	NEWS heap[MAX_NEWS];
	int heapSize;

	void push(NEWS* n)
	{
		heap[heapSize] = *n;
		heap[heapSize].idx = heapSize;

		switchUp(heapSize);

		heapSize++;
		return;
	}

	NEWS pop(void)
	{
		NEWS r = heap[0];

		heap[0] = heap[--heapSize];
		switchDown(0);

		return r;
	}

	void update(NEWS* n, int idx)
	{
		heap[idx] = *n;
		int parent = (idx - 1) / 2;
		if (heap[idx].score > heap[parent].score)
		{
			n->idx = switchUp(idx);
		}
		else
		{
			n->idx = switchDown(idx);
		}
	}

	int switchUp(int cur)
	{
		while (cur)
		{
			int parent = (cur - 1) / 2;
			if (heap[cur].score > heap[parent].score && cur != 0)
			{
				NEWS temp = heap[parent];
				heap[parent] = heap[cur];
				heap[cur] = temp;

				news[heap[parent].id].idx = parent;
				news[heap[cur].id].idx = cur;

				cur = parent;
				continue;
			}
			break;
		}
		return cur;
	}

	int switchDown(int cur)
	{
		while (cur * 2 + 2 < heapSize)
		{
			int l = cur * 2 + 1;
			int r = cur * 2 + 2;
			if (l == heapSize)
			{
				if (heap[cur].score < heap[l].score)
				{
					NEWS temp = heap[l];
					heap[l] = heap[cur];
					heap[cur] = temp;

					cur = l;

					news[heap[l].id].idx = l;
					news[heap[cur].id].idx = cur;
					continue;
				}
			}

			if (heap[cur].score < heap[l].score || heap[cur].score < heap[r].score)
			{
				int t = (heap[l].score > heap[r].score) ? l : r;
				NEWS temp = heap[t];
				heap[t] = heap[cur];
				heap[cur] = temp;

				cur = t;

				news[heap[t].id].idx = t;
				news[heap[cur].id].idx = cur;
				continue;
			}
			break;
		}
		return cur;
	}
} sec[MAX_SECTION];

int u[MAX_USER];

void init()
{
	for (int i = 0; i < MAX_SECTION; i++)
	{
		sec[i].heapSize = 0;
	}
	for (int i = 0; i < MAX_USER; i++)
	{
		u[i] = 10;
	}
}

void addNews(int mSection, int mNewsId)
{
	NEWS& n = news[mNewsId];
	n.id = mNewsId;
	n.score = mNewsId;
	n.s = mSection;

	sec[n.s].push(&n);
}

void eraseNews(int mNewsId)
{
	NEWS& n1 = news[mNewsId];
	sec[n1.s].heap[n1.idx] = sec[n1.s].heap[--sec[n1.s].heapSize];

	NEWS& n2 = news[sec[n1.s].heap[n1.idx].id];
	n2.idx = n1.idx;
	sec[n2.s].update(&n2, n2.idx);
}

void readNews(int mUserId, int mNewsId)
{
	NEWS& n = news[mNewsId];
	n.score += ADD;
	sec[n.s].update(&n, n.idx);

	u[mUserId] = news[mNewsId].s;
}

void changeSection(int mNewsId, int mSection)
{
	NEWS& n = news[mNewsId];
	eraseNews(mNewsId);

	n.s = mSection;
	sec[n.s].push(&n);
}

int getList(int mUserId, int mList[])
{
	NEWS ret[10];
	int i;
	for (i = 0; i < 10; i++)
	{
		ret[i].score = -1;
		for (int j = 0; j < MAX_SECTION; j++)
		{
			if (sec[j].heapSize == 0) { continue; }

			int score = (j == u[mUserId]) ? (sec[j].heap[0].score + (10 * ADD)) : sec[j].heap[0].score;
			if (score > ret[i].score)
			{
				ret[i] = sec[j].heap[0];
				ret[i].score = score;
			}
		}
		if (ret[i].score == -1) break;
		sec[ret[i].s].pop();
	}

	for (int a = 0; a < i; a++)
	{
		mList[a] = ret[a].id;
		sec[ret[a].s].push(&news[ret[a].id]);
	}
	return i;
}