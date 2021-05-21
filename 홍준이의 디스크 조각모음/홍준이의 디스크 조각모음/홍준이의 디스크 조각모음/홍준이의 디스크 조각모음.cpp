#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std;

#define DISK_SIZE  20000  //disk size의 최대값이다.
#define BUF_SIZE   64
#define MAX_FILE   10 //file id의 최대값은 9라서 배열에 사용하기 위해

#define MAX_COUNT  (DISK_SIZE * 2 * 50) // 2,000,000

int disk[DISK_SIZE]; // fileId를 저장하고 있는 disk. main으로 쓰이는 배열이다.
int buf[BUF_SIZE]; 
int numCount[MAX_FILE]; // data size를 세는 반복문.

int moveCount;
int diskSize;

int totalMoveCount;
int totalDiskSize;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void defragment(); // 조각모음이 있다고 알리는 선언문이다.

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int getdiskSize() // disk의 block을 읽어 buffer에 저장한다.
{
	return diskSize; 
}

int readDisk(int* buf, int addr, int size) // disk의 block을 읽어 buffer에 저장한다.
{
	if (addr < 0 || addr + size > diskSize) // addr은 0보다 커야하고, addr+size가 disksize를 넘지 않아야한다.
		return 0;

	for (int i = 0; i < size; i++)
		buf[i] = disk[addr++];

	return size;
}

int move(int from, int to, int size) 
/* 
disk의 block들을 이동시킨다. 한번에 move할 수 있는 block의 최대크기는 정해져있다.
from~to까지 size를 넣는다.
*/
{
	if (moveCount < MAX_COUNT)
		moveCount++; //이 함수에 들어올떄마다 movecount가 증가한다.

	if (from < 0 || from >= diskSize || to < 0 || to >= diskSize) // from과, to가 형식에 맞지않으면 return함.
		return 0;

	if (size < 1 || size > BUF_SIZE || from + size > diskSize || to + size > diskSize) 
		return 0;
	//한번에 이동시킬 수 있는 개수는 BUF_SIZE개 이고, from+size, to+size가 diskSize보다 크면 return 0한다.

	for (int i = 0; i < size; i++)
	{
		buf[i] = disk[from]; // from부터 size개를 buf에 넣는다.
		disk[from] = 0; // 
		from++;
	}

	for (int i = 0; i < size; i++)
	{
		disk[to++] = buf[i];
	}

	return size; // 0이 아닌값이 return된다.
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
		int fileID = disk[idx]; // disk의 idx번 째 index
		if (checkCount[fileID] != 0) // check Count[disk의 idx번째 index]가 0이면 count를 종료함.
			return 0;

		for (int i = 0; i < numCount[fileID]; i++) // size의 개수만큼 반복
		{
			if (fileID != disk[idx++]) // size가 a에서 다른 숫자로 넘어갈 때
				return 0; // 함수에서 빠져나감
			checkCount[fileID]++; // check Count는 ++함
		}
	}

	if (disk[diskSize - 1] != 0) // 마지막값이 0이 아니면 return0
		return 0;

	for (int i = 0; i < MAX_FILE; i++) // 0부터 10까지
	{
		if (checkCount[i] != numCount[i]) // checkCount랑 numCount가 다르면 return0
			return 0;
	}

	return 1; // 전부 다 아니면 1 리턴
}

void init() // 배열들을 초기화하는 함수
{
	moveCount = 0;

	for (int i = 0; i < MAX_FILE; i++)
		numCount[i] = 0;

	for (int i = 0; i < diskSize; i++)
	{
		numCount[disk[i]]++; // data size를 세는 반복문.
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

		defragment(); // 조각모음하기

		int cnt = MAX_COUNT; // cnt = 2,000,000
		if (checkDisk() == 1) // 디스크 조각 모음이 됐으면
			cnt = moveCount; // move count 를 cnt에 넣음.

		printf("#%d %d\n", tc, cnt);

		totalMoveCount += cnt;
		totalDiskSize += diskSize;
	}

	printf("Total diskSize  : %d\n", totalDiskSize);
	printf("Total moveCount : %d\n", totalMoveCount);
	end = clock();
	printf("%f", end - start);
}


// user code에 붙혀넣을 부분.

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
	while (++idx < mDiskSize) if (mDisk[idx] == 0) mZeroCount++;  //0의 개수를 셈

	mMoveZero();

	idx = 0;
	while (idx < mDiskSize - mZeroCount) idx = mMoveNumber(idx);
}