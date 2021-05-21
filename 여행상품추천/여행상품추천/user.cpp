#include <stdio.h>

#define MAX_ADD 40000
#define MAX_USER 1001
#define MAX_AREA 11
#define MAX_FRIEND 21
#define MAX_TABLE 100007
#define TP TravelPackage
#define ull unsigned long long
#define rint register int
#define hash(pid) pid % MAX_TABLE

#define NULL 0
#define nullptr 0

struct TravelPackage
{
	bool sold;
	int pid;
	int area;
	int price;
	ull score;
	TP* prev;
} tp[MAX_ADD];
TP* pidTable[MAX_TABLE];

int arr_idx = 0;
TP* myalloc(void) { return &tp[arr_idx++]; }

struct USER
{
	int follow[MAX_FRIEND];
	int count;
	int area[MAX_AREA];
	int area_total[MAX_AREA];
} user[MAX_USER];

struct HEAP
{
	int arr[MAX_ADD+1];
	int heapSize;
	int cur;

	void heapPush(int idx)
	{
		if (heapSize == MAX_ADD) { return; }
		cur = ++heapSize;
		while (tp[idx].score < tp[arr[cur >> 1]].score && (cur >> 1) > 0)
		{
			arr[cur] = arr[cur >> 1];
			cur = cur >> 1;
		}
		arr[cur] = idx;
		//heapSize++;
	}

	int heapPop(void)
	{
		if (!heapSize) return -1;
		int ret = arr[1];
		rint e = arr[heapSize--];
		rint cur = 1, ch = 2;
		while (ch <= heapSize) {
			if (ch + 1 <= heapSize && tp[arr[ch]].score > tp[arr[ch + 1]].score) ch++;
			if (tp[e].score <= tp[arr[ch]].score) break;
			arr[cur] = arr[ch];
			cur = ch; ch <<= 1;
		}
		arr[cur] = e;
		return ret;
	}

	int heapTop(void)
	{
		if (!heapSize) return -1;
		return arr[1];
	}
} heap[MAX_AREA];

void init(int N, int M)
{
	arr_idx = 0;
	for (rint i = 0; i < MAX_AREA; i++)
	{
		heap[i].heapSize = 0;
	}

	for (rint i = 0; i < MAX_TABLE; i++)
	{
		pidTable[i] = nullptr;
	}

	for (rint i = 0; i < MAX_USER; i++)
	{
		user[i].count = 0;
		for (rint j = 0; j < MAX_AREA; j++)
		{
			user[i].area[j] = 0;
			user[i].area_total[j] = 0;
		}
		user[i].follow[user[i].count++] = i;
	}
}

void befriend(int uid1, int uid2)
{
	user[uid1].follow[user[uid1].count++] = uid2;
	user[uid2].follow[user[uid2].count++] = uid1;

	/*for (rint i = 0; i < user[uid1].count; i++)
	{
		for (rint j = 0; j < MAX_AREA; j++)
		{
			user[user[uid1].follow[i]].area_total[j] += user[uid2].area_total[j];
		}
	}

	for (rint i = 0; i < user[uid2].count; i++)
	{
		for (rint j = 0; j < MAX_AREA; j++)
		{
			user[user[uid2].follow[i]].area_total[j] = user[uid1].area_total[j];
		}
	}*/
	for (rint j = 0; j < MAX_AREA; j++)
	{
		user[uid1].area_total[j] += user[uid2].area[j];
		user[uid2].area_total[j] += user[uid1].area[j];
	}


	//printf("%d follow %d\n%d follow %d\n", uid1, user[uid1].follow[user[uid1].count - 1], uid2, user[uid2].follow[user[uid2].count - 1]);
}

void add(int pid, int area, int price)
{
	TP* newTP = myalloc();
	newTP->pid = pid;
	newTP->area = area;
	newTP->price = price;
	newTP->sold = 0;
	newTP->score = ((ull)price << 30) | pid;
	newTP->prev = pidTable[hash(pid)];
	pidTable[hash(pid)] = newTP;

	//printf("pid : %d, area : %d, price : %d, sold : %d, score : %lld, hash : %d\n", newTP->pid, newTP->area, newTP->price, newTP->sold, newTP->score, hash(pid));

	heap[area].heapPush(arr_idx - 1);
}

TP* findTP(int pid)
{
	for (TP* pp = pidTable[hash(pid)]; pp != NULL; pp = pp->prev)
	{
		if (pp->pid == pid)
			return pp;
	}
}

void reserve(int uid, int pid)
{
	TP* newTP = findTP(pid);
	newTP->sold = 1;
	user[uid].area[newTP->area]++;
	for (rint i = 0; i < user[uid].count; i++)
	{
		user[user[uid].follow[i]].area_total[newTP->area]++;
	}

	while (tp[heap[newTP->area].heapTop()].sold == true && heap[newTP->area].heapSize)
	{
		heap[newTP->area].heapPop();
	}
}

void quickSort(ull* temp, int first, int last)
{
	int pivot;
	int i;
	int j;
	ull t;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (temp[i] <= temp[pivot] && i < last)
			{
				i++;
			}
			while (temp[j] > temp[pivot])
			{
				j--;
			}
			if (i < j)
			{
				t = temp[i];
				temp[i] = temp[j];
				temp[j] = t;
			}
		}

		t = temp[pivot];
		temp[pivot] = temp[j];
		temp[j] = t;

		quickSort(temp, first, j - 1);
		quickSort(temp, j + 1, last);
	}
}

int recommend(int uid)
{
	ull temp[MAX_AREA];
	int cnt = 1;
	for (rint i = 0; i < MAX_AREA; i++) { temp[i] = 0; }

	for (rint i = 0; i < MAX_AREA; i++)
	{
		int t = heap[i].heapTop();
		if (t == -1) { continue; }
		temp[cnt++] = (((ull)MAX_ADD+1 - (ull)user[uid].area_total[i]) << 40) | tp[t].score;
	}

	quickSort(temp, 1, cnt - 1);

	/*for (rint i = 0; i < MAX_AREA; i++)
	{
		printf("%d & 0x3FFFFFFF = %d\n", i, temp[i] & 0x3FFFFFFF);
	}
	printf("\n");*/

	return (int)(temp[1] & 0x3FFFFFFF);
}