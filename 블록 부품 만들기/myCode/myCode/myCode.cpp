#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <time.h>

#define MAX 30000

using namespace std;

int makeBlock(int module[][4][4]);

int main(void)
{
	clock_t start, end;
	start = clock();
	static int module[MAX][4][4];

	srand(3); // 3 will be changed

	for (int tc = 1; tc <= 10; tc++)
	{
		for (int c = 0; c < MAX; c++)
		{
			int base = 1 + (rand() % 6);
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					module[c][y][x] = base + (rand() % 3);
					//module[c][y][x] += 0;
				}
			}
		}
		cout << "#" << tc << " " << makeBlock(module) << endl;
	}
	end = clock();
	printf(" %f ", (double)end - start);
	return 0;
}

//#define MAX 30000
#define HASH_MAX 264217 // hash table의 최대값은 264217이고, hash key는 x%HASH_MAX임

int num_Table[10] = { 0, }; /* base기준으로 sort 되고, sort된걸 기준으로 hash table이 만들어지는데,
							base가 몇개 입력되었는지를 저장하는 변수*/
int base_Sort_Module[10][MAX] = { 0, }; // base와 num_Table을 받아서, module의 index를 저장함.
int max_Arr[MAX] = { 0, }; // module의 max를 저장하는 배열
int min_Arr[MAX] = { 0, }; // module의 min을 저장하는 배열
unsigned int block_Max_Value[MAX] = { 0, }; /* module을 가만히, (시계방향으로) 90, 180, 270도를 회전시킨 값중에
								   젤 높은 값을 저장함. */
unsigned int rev_block_Max_Value[MAX] = { 0, }; /* module을 뒤집은 상태에서 가만히, (시계방향으로) 90, 180, 270도를
									   회전시킨 값중에 젤 높은 값을 저장함.*/
int hash_Table[HASH_MAX] = { 0, }; // hash table
int used[MAX] = { 0, }; // module의 index가 사용(check)되었는지 저장하는 배열

void getBlockInfo(int idx, int myModule[4][4])
{
	int max = 0; //max값의 초기화를 위해 최솟값 저장
	int min = 10; //min값의 초기화를 위해 최대값 저장
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (myModule[i][j] > max) max = myModule[i][j]; // Max를 탐색
			if (myModule[i][j] < min) min = myModule[i][j]; // min을 탐색
		}
	}
	max_Arr[idx] = max;
	min_Arr[idx] = min;
	base_Sort_Module[min][num_Table[min]++] = idx;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			myModule[i][j] -= min;
		}
	}

	unsigned int form[4] = { 0, };
	unsigned int rev_form[4] = { 0, };

	form[0] = (myModule[0][0] << 30) + (myModule[0][1] << 28) + (myModule[0][2] << 26) + (myModule[0][3] << 24) +
		(myModule[1][0] << 22) + (myModule[1][1] << 20) + (myModule[1][2] << 18) + (myModule[1][3] << 16) +
		(myModule[2][0] << 14) + (myModule[2][1] << 12) + (myModule[2][2] << 10) + (myModule[2][3] << 8) +
		(myModule[3][0] << 6) + (myModule[3][1] << 4) + (myModule[3][2] << 2) + (myModule[3][3] << 0);

	form[1] = (myModule[0][3] << 30) + (myModule[1][3] << 28) + (myModule[2][3] << 26) + (myModule[3][3] << 24) +
		(myModule[0][2] << 22) + (myModule[1][2] << 20) + (myModule[2][2] << 18) + (myModule[3][2] << 16) +
		(myModule[0][1] << 14) + (myModule[1][1] << 12) + (myModule[2][1] << 10) + (myModule[3][1] << 8) +
		(myModule[0][0] << 6) + (myModule[1][0] << 4) + (myModule[2][0] << 2) + (myModule[3][0] << 0);

	form[2] = (myModule[3][3] << 30) + (myModule[3][2] << 28) + (myModule[3][1] << 26) + (myModule[3][0] << 24) +
		(myModule[2][3] << 22) + (myModule[2][2] << 20) + (myModule[2][1] << 18) + (myModule[2][0] << 16) +
		(myModule[1][3] << 14) + (myModule[1][2] << 12) + (myModule[1][1] << 10) + (myModule[1][0] << 8) +
		(myModule[0][3] << 6) + (myModule[0][2] << 4) + (myModule[0][1] << 2) + (myModule[0][0] << 0);

	form[3] = (myModule[3][0] << 30) + (myModule[2][0] << 28) + (myModule[1][0] << 26) + (myModule[0][0] << 24) +
		(myModule[3][1] << 22) + (myModule[2][1] << 20) + (myModule[1][1] << 18) + (myModule[0][1] << 16) +
		(myModule[3][2] << 14) + (myModule[2][2] << 12) + (myModule[1][2] << 10) + (myModule[0][2] << 8) +
		(myModule[3][3] << 6) + (myModule[2][3] << 4) + (myModule[1][3] << 2) + (myModule[0][3] << 0);

	///////////////// reverse.

	rev_form[0] = (myModule[0][3] << 30) + (myModule[0][2] << 28) + (myModule[0][1] << 26) + (myModule[0][0] << 24) +
		(myModule[1][3] << 22) + (myModule[1][2] << 20) + (myModule[1][1] << 18) + (myModule[1][0] << 16) +
		(myModule[2][3] << 14) + (myModule[2][2] << 12) + (myModule[2][1] << 10) + (myModule[2][0] << 8) +
		(myModule[3][3] << 6) + (myModule[3][2] << 4) + (myModule[3][1] << 2) + (myModule[3][0] << 0);

	rev_form[1] = (myModule[0][0] << 30) + (myModule[1][0] << 28) + (myModule[2][0] << 26) + (myModule[3][0] << 24) +
		(myModule[0][1] << 22) + (myModule[1][1] << 20) + (myModule[2][1] << 18) + (myModule[3][1] << 16) +
		(myModule[0][2] << 14) + (myModule[1][2] << 12) + (myModule[2][2] << 10) + (myModule[3][2] << 8) +
		(myModule[0][3] << 6) + (myModule[1][3] << 4) + (myModule[2][3] << 2) + (myModule[3][3] << 0);

	rev_form[2] = (myModule[3][0] << 30) + (myModule[3][1] << 28) + (myModule[3][2] << 26) + (myModule[3][3] << 24) +
		(myModule[2][0] << 22) + (myModule[2][1] << 20) + (myModule[2][2] << 18) + (myModule[2][3] << 16) +
		(myModule[1][0] << 14) + (myModule[1][1] << 12) + (myModule[1][2] << 10) + (myModule[1][3] << 8) +
		(myModule[0][0] << 6) + (myModule[0][1] << 4) + (myModule[0][2] << 2) + (myModule[0][3] << 0);

	rev_form[3] = (myModule[3][3] << 30) + (myModule[2][3] << 28) + (myModule[1][3] << 26) + (myModule[0][3] << 24) +
		(myModule[3][2] << 22) + (myModule[2][2] << 20) + (myModule[1][2] << 18) + (myModule[0][2] << 16) +
		(myModule[3][1] << 14) + (myModule[2][1] << 12) + (myModule[1][1] << 10) + (myModule[0][1] << 8) +
		(myModule[3][0] << 6) + (myModule[2][0] << 4) + (myModule[1][0] << 2) + (myModule[0][0] << 0);

	if (form[0] < form[1]) { form[0] = form[1]; }
	if (form[0] < form[2]) { form[0] = form[2]; }
	if (form[0] < form[3]) { form[0] = form[3]; }
	if (rev_form[0] > rev_form[1]) { rev_form[0] = rev_form[1]; }
	if (rev_form[0] > rev_form[2]) { rev_form[0] = rev_form[2]; }
	if (rev_form[0] > rev_form[3]) { rev_form[0] = rev_form[3]; }

	block_Max_Value[idx] = form[0];
	rev_block_Max_Value[idx] = rev_form[0];

	return;
}

void makeHashTable(void)
{
	unsigned int h;
	for (int i = 8; i > 0; i--)
	{
		for (int j = 0; j < num_Table[i]; j++)
		{
			int idx = base_Sort_Module[i][j];
			h = rev_block_Max_Value[idx] % HASH_MAX;
			while (hash_Table[h] != 0)
			{
				h += 1;
				h = h % HASH_MAX;
			}
			hash_Table[h] = idx;
		}
	}
	return;
}

int findHash(void)
{
	int sum = 0;
	for (int i = 8; i > 0; i--)
	{
		for (int j = 0; j < num_Table[i]; j++)
		{
			int idx = base_Sort_Module[i][j];
			
			if (used[idx]) { continue; }
			used[idx] = 1;
			unsigned int h;
			unsigned int match;

			if ((max_Arr[idx] - min_Arr[idx]) == 1)
				match = 0x55555555 - block_Max_Value[idx];
			else
				match = 0xAAAAAAAA - block_Max_Value[idx];
			h = match % HASH_MAX;

			while (hash_Table[h] != 0)
			{
				int rev_block = hash_Table[h];
				if ((rev_block_Max_Value[rev_block] == match) && (used[rev_block] == 0))
				{
					sum = sum + max_Arr[rev_block] + min_Arr[idx];
					used[rev_block] = 1;
					break;
				}
				h += 1;
				h = h % HASH_MAX;
			}
		}
	}
	return sum;
}

int makeBlock(int module[][4][4])
{
	for (int i = 0; i < HASH_MAX; i++)
	{
		hash_Table[i] = 0;
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			base_Sort_Module[i][j] = 0;
		}
	}

	for (int i = 0; i < MAX; i++)
	{
		max_Arr[i] = 0;
		min_Arr[i] = 0;
		block_Max_Value[i] = 0;
		rev_block_Max_Value[i] = 0;
		used[i] = 0;
	}

	int ret = 0;

	for (int i = 0; i < MAX; i++)
	{
		getBlockInfo(i, module[i]);
	}

	makeHashTable();

	ret = findHash();
	
	return ret;
}