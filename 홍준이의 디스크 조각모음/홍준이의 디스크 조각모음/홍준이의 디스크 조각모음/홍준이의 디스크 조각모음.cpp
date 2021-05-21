#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std;

#define DISK_SIZE  20000  //disk size�� �ִ밪�̴�.
#define BUF_SIZE   64
#define MAX_FILE   10 //file id�� �ִ밪�� 9�� �迭�� ����ϱ� ����

#define MAX_COUNT  (DISK_SIZE * 2 * 50) // 2,000,000

int disk[DISK_SIZE]; // fileId�� �����ϰ� �ִ� disk. main���� ���̴� �迭�̴�.
int buf[BUF_SIZE]; 
int numCount[MAX_FILE]; // data size�� ���� �ݺ���.

int moveCount;
int diskSize;

int totalMoveCount;
int totalDiskSize;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void defragment(); // ���������� �ִٰ� �˸��� �����̴�.

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int getdiskSize() // disk�� block�� �о� buffer�� �����Ѵ�.
{
	return diskSize; 
}

int readDisk(int* buf, int addr, int size) // disk�� block�� �о� buffer�� �����Ѵ�.
{
	if (addr < 0 || addr + size > diskSize) // addr�� 0���� Ŀ���ϰ�, addr+size�� disksize�� ���� �ʾƾ��Ѵ�.
		return 0;

	for (int i = 0; i < size; i++)
		buf[i] = disk[addr++];

	return size;
}

int move(int from, int to, int size) 
/* 
disk�� block���� �̵���Ų��. �ѹ��� move�� �� �ִ� block�� �ִ�ũ��� �������ִ�.
from~to���� size�� �ִ´�.
*/
{
	if (moveCount < MAX_COUNT)
		moveCount++; //�� �Լ��� ���Ë����� movecount�� �����Ѵ�.

	if (from < 0 || from >= diskSize || to < 0 || to >= diskSize) // from��, to�� ���Ŀ� ���������� return��.
		return 0;

	if (size < 1 || size > BUF_SIZE || from + size > diskSize || to + size > diskSize) 
		return 0;
	//�ѹ��� �̵���ų �� �ִ� ������ BUF_SIZE�� �̰�, from+size, to+size�� diskSize���� ũ�� return 0�Ѵ�.

	for (int i = 0; i < size; i++)
	{
		buf[i] = disk[from]; // from���� size���� buf�� �ִ´�.
		disk[from] = 0; // 
		from++;
	}

	for (int i = 0; i < size; i++)
	{
		disk[to++] = buf[i];
	}

	return size; // 0�� �ƴѰ��� return�ȴ�.
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int checkDisk()
{
	int checkCount[MAX_FILE];
	for (int i = 0; i < MAX_FILE; i++)
		checkCount[i] = 0;

	int idx = 0;
	while (idx < diskSize) // 200 <= idx <=20000
	{
		int fileID = disk[idx]; // disk�� idx�� ° index
		if (checkCount[fileID] != 0) // check Count[disk�� idx��° index]�� 0�̸� count�� ������.
			return 0;

		for (int i = 0; i < numCount[fileID]; i++) // size�� ������ŭ �ݺ�
		{
			if (fileID != disk[idx++]) // size�� a���� �ٸ� ���ڷ� �Ѿ ��
				return 0; // �Լ����� ��������
			checkCount[fileID]++; // check Count�� ++��
		}
	}

	if (disk[diskSize - 1] != 0) // ���������� 0�� �ƴϸ� return0
		return 0;

	for (int i = 0; i < MAX_FILE; i++) // 0���� 10����
	{
		if (checkCount[i] != numCount[i]) // checkCount�� numCount�� �ٸ��� return0
			return 0;
	}

	return 1; // ���� �� �ƴϸ� 1 ����
}

void init() // �迭���� �ʱ�ȭ�ϴ� �Լ�
{
	moveCount = 0;

	for (int i = 0; i < MAX_FILE; i++)
		numCount[i] = 0;

	for (int i = 0; i < diskSize; i++)
	{
		numCount[disk[i]]++; // data size�� ���� �ݺ���.
	}
}

int main()
{
	time_t start, end;
	start = clock();
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	totalMoveCount = 0;
	totalDiskSize = 0;

	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d", &diskSize);
		for (int i = 0; i < diskSize; i++)
			scanf("%d", &disk[i]);

		init();

		defragment(); // ���������ϱ�

		int cnt = MAX_COUNT; // cnt = 2,000,000
		if (checkDisk() == 1) // ��ũ ���� ������ ������
			cnt = moveCount; // move count �� cnt�� ����.

		printf("#%d %d\n", tc, cnt);

		totalMoveCount += cnt;
		totalDiskSize += diskSize;
	}

	printf("Total diskSize  : %d\n", totalDiskSize);
	printf("Total moveCount : %d\n", totalMoveCount);
	end = clock();
	printf("%f", end - start);
}


// user code�� �������� �κ�.

/*
int getdiskSize();
int readDisk(int* buf, int addr, int size);
int move(int from, int to, int size);
*/

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
extern int getdiskSize();
extern int readDisk(int* buf, int addr, int size);
extern int move(int from, int to, int size);

#define DISK_SIZE  20000
#define BUF_SIZE   64

#define SWAP(from, to) { int temp = to; to = from; from = temp; }
#define MOVE(from, to) to = from; from = 0;

int mDisk[DISK_SIZE];
int mDiskSize = 0;
int mZeroCount = 0;

void mMoveZero()
{
	register int left = 0;
	register int right = mDiskSize - 1;
	register int count = 0;

	while (left < right)
	{
		while (mDisk[left] != 0) left++;
		while (mDisk[right] == 0) right--;

		if (left < right)
		{
			for (count = 1; count < BUF_SIZE; count++)
			{
				if (mDisk[left + count] != 0)
					break;
				if (mDisk[right - count] == 0)
					break;
				if (left + count == right - count)
					break;
			}

			move(right - count + 1, left, count);

			register int index = -1;
			while (++index < count)
				MOVE(mDisk[right - count + 1 + index], mDisk[left + index]);

			left += count;
			right -= count;
		}
	}
}

int mMoveNumber(int idx)
{
	int left = idx;
	int right = mDiskSize - mZeroCount - 1;
	int count = 0;

	int id = mDisk[left];
	while (id != 0 && left < right)
	{
		while (mDisk[left] == id) left++;
		while (mDisk[right] != id) right--;

		if (left < right)
		{
			for (count = 1; count < BUF_SIZE && count < mZeroCount; count++)
			{
				if (mDisk[left + count] == id)
					break;
				if (mDisk[right - count] != id)
					break;
				if (left + count >= right - count)
					break;
			}

			int from = right - count + 1;
			int to = left;
			int size = count;

			move(to, mDiskSize - mZeroCount, size);
			move(from, to, size);
			move(mDiskSize - mZeroCount, from, size);

			register int index = -1;
			while (++index < size)
				SWAP(mDisk[from + index], mDisk[to + index]);

			left += count;
			right -= count;
		}
	}
	return left;
}

void defragment()
{
	mDiskSize = getdiskSize();
	readDisk(mDisk, 0, mDiskSize);

	mZeroCount = 0;
	register int idx = -1;
	while (++idx < mDiskSize) if (mDisk[idx] == 0) mZeroCount++;  //0�� ������ ��

	mMoveZero();

	idx = 0;
	while (idx < mDiskSize - mZeroCount) idx = mMoveNumber(idx);
}