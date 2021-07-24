#include <stdio.h>

#define MAX_HEAP 10001
#define MAX_MCH 101
#define MAX_TABLE 5000
#define ull unsigned long long

void merge(ull arr[], int left, int mid, int right);
void mergeSort(ull arr[], int left, int right);

struct WAIT
{
	int num;
	int priority;
};

struct SCH
{
	int num;
	ull score;
};

struct FID
{
	int id;
	int index;
};

struct MCH
{
	int id;
	int endTime;
	int capacity;
	int duration;
	int waiting;

	WAIT heap[MAX_HEAP];
	int hSize;

	void init(void)
	{
		endTime = 0;
		hSize = 0;
	}

	int push(WAIT value)
	{
		heap[hSize] = value;

		int current = hSize;
		while (current > 0 && heap[current].priority > heap[(current - 1) / 2].priority)
		{
			WAIT temp = heap[(current - 1) / 2];
			heap[(current - 1) / 2] = heap[current];
			heap[current] = temp;
			current = (current - 1) / 2;
		}

		hSize = hSize + 1;

		return 1;
	}

	WAIT pop(void)
	{
		if (hSize <= 0)
		{
			WAIT empty;
			empty.priority = 0;
			return empty;
		}

		WAIT value = heap[0];
		hSize = hSize - 1;

		heap[0] = heap[hSize];

		int current = 0;
		while (current * 2 + 1 < hSize)
		{
			int child;
			if (current * 2 + 2 == hSize)
			{
				child = current * 2 + 1;
			}
			else
			{
				child = heap[current * 2 + 1].priority > heap[current * 2 + 2].priority ? current * 2 + 1 : current * 2 + 2;
			}

			if (heap[current].priority > heap[child].priority)
			{
				break;
			}

			WAIT temp = heap[current];
			heap[current] = heap[child];
			heap[child] = temp;

			current = child;
		}
		return value;
	}

	int top(void)
	{
		if (hSize <= 0)
		{
			return 0;
		}
		return heap[0].priority;
	}

}mch[MAX_MCH];

int mN;

FID table[MAX_TABLE];

void add(int id, int index)
{
	int key = id % MAX_TABLE;

	while (1)
	{
		if (table[key].id == -1)
		{
			table[key].id = id;
			table[key].index = index;
			//printf("id = %d, key = %d, index = %d\n", id, key, index);
			break;
		}
		key++;
		key = key % MAX_TABLE;
	}
	return;
}

int find(int id)
{
	int key = id % MAX_TABLE;

	while (1)
	{
		if (table[key].id == id)
		{
			break;
		}
		key++;
		key = key % MAX_TABLE;
	}
	return table[key].index;
}

void init(int N, int mId[], int mDuration[], int mCapacity[]) {
	mN = N;
	for (int i = 0; i < MAX_TABLE; i++)
	{
		table[i].id = -1;
	}

	for (int i = 0; i < N; i++)
	{
		mch[i].endTime = 0;
		mch[i].id = 0;
		mch[i].waiting = 0;
		mch[i].init();
		mch[i].id = mId[i];
		add(mId[i], i);
		mch[i].duration = mDuration[i];
		mch[i].capacity = mCapacity[i];
	}
	return;
}

void lazyUpdate(int key, int tStamp)
{
	while (mch[key].endTime <= tStamp)
	{
		if (mch[key].waiting < mch[key].capacity)
		{
			if (mch[key].waiting != 0)
			{
				mch[key].endTime += mch[key].duration;
				mch[key].waiting = 0;
				mch[key].hSize = 0;
			}
			break;
		}
		
		mch[key].endTime += mch[key].duration;
		mch[key].waiting -= mch[key].capacity;
		int cnt = 0;
		while (1)
		{
			cnt += mch[key].heap[0].num;
			if (cnt < mch[key].capacity)
			{
				mch[key].pop();
			}
			else if (cnt == mch[key].capacity)
			{
				mch[key].pop();
				break;
			}
			else if (cnt > mch[key].capacity)
			{
				mch[key].heap[0].num = (cnt-mch[key].capacity);
				break;
			}
		}
	}
}

void lazyUpdate_prev(int key, int tStamp)
{
	if (mch[key].endTime == 0)
	{
		mch[key].endTime = tStamp;
	}
	while (mch[key].endTime < tStamp)
	{
		if (mch[key].waiting < mch[key].capacity)
		{
			if (mch[key].waiting != 0)
			{
				mch[key].endTime += mch[key].duration;
				mch[key].waiting = 0;
				mch[key].hSize = 0;
			}
			break;
		}
		mch[key].endTime += mch[key].duration;
		mch[key].waiting -= mch[key].capacity;
		int cnt = 0;
		while (1)
		{
			cnt += mch[key].heap[0].num;
			if (cnt < mch[key].capacity)
			{
				mch[key].pop();
			}
			else if (cnt == mch[key].capacity)
			{
				mch[key].pop();
				break;
			}
			else if (cnt > mch[key].capacity)
			{
				mch[key].heap[0].num = (cnt - mch[key].capacity);
				break;
			}
		}
	}
	if (mch[key].endTime <= tStamp && mch[key].waiting == 0)
	{
		mch[key].endTime = tStamp;
	}
}

int add(int tStamp, int mId, int mNum, int mPriority) {
	WAIT nWait;
	nWait.num = mNum;
	nWait.priority = mPriority;

	int key = find(mId);
	lazyUpdate_prev(key, tStamp);

	mch[key].push(nWait);
	mch[key].waiting += nWait.num;
	lazyUpdate(key, tStamp);

	return mch[key].top();
}

void mergeSort(ull arr[], int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int mid = (left + right) / 2;
	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}
ull temp[MAX_MCH];
void merge(ull arr[], int left, int mid, int right)
{
	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right)
	{
		if (arr[i] < arr[j])
		{
			temp[k++] = arr[j++];
		}
		else
		{
			temp[k++] = arr[i++];
		}
	}

	while (i <= mid) { temp[k++] = arr[i++]; }
	while (j <= right) { temp[k++] = arr[j++]; }
	for (int a = left; a <= right; a++)
	{
		arr[a] = temp[a];
	}
}

void search(int tStamp, int mCount, int mId[], int mWait[]) {
	ull arr[MAX_MCH];
	for (int i = 0; i < mN; i++)
	{
		lazyUpdate(i, tStamp);
		arr[i] = ((ull)mch[i].waiting << 32) + mch[i].id;
	}

	mergeSort(arr, 0, mN - 1);
	for (int i = 0; i < mCount; i++)
	{
		mWait[i] = (arr[i] >> 32);
		mId[i] = (arr[i] & 0xFFFFFFFF);
		//printf("mId[%d] : %d, mWait[%d] : %d\n", i, mId[i], i, mWait[i]);
	}
	return;
}