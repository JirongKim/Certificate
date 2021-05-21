#include <iostream>
#include <stdlib.h>

#define MAX 30000

using namespace std;

extern int makeBlock(int module[][4][4]);

int main(void)
{
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
				}
			}
		}
		cout << "#" << tc << " " << makeBlock(module) << endl;
	}

	return 0;
}


//#include <stdio.h>

#define MAX 30000
#define MAX_HASH 264217

unsigned int pos[MAX], mpos[MAX];
int min_Arr[MAX], max_Arr[MAX];

int num_table[10];
int table[10][MAX];
int used[MAX];
int hash_table[MAX_HASH];

void GetBlockInfo(int num, int MyModule[4][4])
{
    register int i = 0, j = 0;
    int min = 100;
    int max = 0;
    unsigned int Norm[4][4];

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            min = min > MyModule[i][j] ? MyModule[i][j] : min;
            max = max < MyModule[i][j] ? MyModule[i][j] : max;
        }

    }

    used[num] = 0;
    min_Arr[num] = min;
    max_Arr[num] = max;

    table[min][num_table[min]++] = num;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            Norm[i][j] = MyModule[i][j] - min;
        }
    }



    unsigned int rot[4] = { 0, };
    unsigned int rev_rot[4] = { 0, };
    unsigned int rot_max = 0;
    unsigned int rev_max = 0;

    rot[0] = (Norm[3][3] << 30) | (Norm[3][2] << 28) | (Norm[3][1] << 26) | (Norm[3][0] << 24) |
        (Norm[2][3] << 22) | (Norm[2][2] << 20) | (Norm[2][1] << 18) | (Norm[2][0] << 16) |
        (Norm[1][3] << 14) | (Norm[1][2] << 12) | (Norm[1][1] << 10) | (Norm[1][0] << 8) |
        (Norm[0][3] << 6) | (Norm[0][2] << 4) | (Norm[0][1] << 2) | (Norm[0][0] << 0);

    rot[1] = (Norm[0][3] << 30) | (Norm[1][3] << 28) | (Norm[2][3] << 26) | (Norm[3][3] << 24) |
        (Norm[0][2] << 22) | (Norm[1][2] << 20) | (Norm[2][2] << 18) | (Norm[3][2] << 16) |
        (Norm[0][1] << 14) | (Norm[1][1] << 12) | (Norm[2][1] << 10) | (Norm[3][1] << 8) |
        (Norm[0][0] << 6) | (Norm[1][0] << 4) | (Norm[2][0] << 2) | (Norm[3][0] << 0);

    rot[2] = (Norm[0][0] << 30) | (Norm[0][1] << 28) | (Norm[0][2] << 26) | (Norm[0][3] << 24) |
        (Norm[1][0] << 22) | (Norm[1][1] << 20) | (Norm[1][2] << 18) | (Norm[1][3] << 16) |
        (Norm[2][0] << 14) | (Norm[2][1] << 12) | (Norm[2][2] << 10) | (Norm[2][3] << 8) |
        (Norm[3][0] << 6) | (Norm[3][1] << 4) | (Norm[3][2] << 2) | (Norm[3][3] << 0);

    rot[3] = (Norm[3][0] << 30) | (Norm[2][0] << 28) | (Norm[1][0] << 26) | (Norm[0][0] << 24) |
        (Norm[3][1] << 22) | (Norm[2][1] << 20) | (Norm[1][1] << 18) | (Norm[0][1] << 16) |
        (Norm[3][2] << 14) | (Norm[2][2] << 12) | (Norm[1][2] << 10) | (Norm[0][2] << 8) |
        (Norm[3][3] << 6) | (Norm[2][3] << 4) | (Norm[1][3] << 2) | (Norm[0][3] << 0);


    rev_rot[0] = (Norm[3][0] << 30) | (Norm[3][1] << 28) | (Norm[3][2] << 26) | (Norm[3][3] << 24) |
        (Norm[2][0] << 22) | (Norm[2][1] << 20) | (Norm[2][2] << 18) | (Norm[2][3] << 16) |
        (Norm[1][0] << 14) | (Norm[1][1] << 12) | (Norm[1][2] << 10) | (Norm[1][3] << 8) |
        (Norm[0][0] << 6) | (Norm[0][1] << 4) | (Norm[0][2] << 2) | (Norm[0][3] << 0);

    rev_rot[1] = (Norm[0][0] << 30) | (Norm[1][0] << 28) | (Norm[2][0] << 26) | (Norm[3][0] << 24) |
        (Norm[0][1] << 22) | (Norm[1][1] << 20) | (Norm[2][1] << 18) | (Norm[3][1] << 16) |
        (Norm[0][2] << 14) | (Norm[1][2] << 12) | (Norm[2][2] << 10) | (Norm[3][2] << 8) |
        (Norm[0][3] << 6) | (Norm[1][3] << 4) | (Norm[2][3] << 2) | (Norm[3][3] << 0);

    rev_rot[2] = (Norm[0][3] << 30) | (Norm[0][2] << 28) | (Norm[0][1] << 26) | (Norm[0][0] << 24) |
        (Norm[1][3] << 22) | (Norm[1][2] << 20) | (Norm[1][1] << 18) | (Norm[1][0] << 16) |
        (Norm[2][3] << 14) | (Norm[2][2] << 12) | (Norm[2][1] << 10) | (Norm[2][0] << 8) |
        (Norm[3][3] << 6) | (Norm[3][2] << 4) | (Norm[3][1] << 2) | (Norm[3][0] << 0);

    rev_rot[3] = (Norm[3][3] << 30) | (Norm[2][3] << 28) | (Norm[1][3] << 26) | (Norm[0][3] << 24) |
        (Norm[3][2] << 22) | (Norm[2][2] << 20) | (Norm[1][2] << 18) | (Norm[0][2] << 16) |
        (Norm[3][1] << 14) | (Norm[2][1] << 12) | (Norm[1][1] << 10) | (Norm[0][1] << 8) |
        (Norm[3][0] << 6) | (Norm[2][0] << 4) | (Norm[1][0] << 2) | (Norm[0][0] << 0);

    if (rot[0] > rot[1]) rot[0] = rot[1];
    if (rot[0] > rot[2]) rot[0] = rot[2];
    if (rot[0] > rot[3]) rot[0] = rot[3];
    if (rev_rot[0] < rev_rot[1]) rev_rot[0] = rev_rot[1];
    if (rev_rot[0] < rev_rot[2]) rev_rot[0] = rev_rot[2];
    if (rev_rot[0] < rev_rot[3]) rev_rot[0] = rev_rot[3];

    pos[num] = rot[0];
    mpos[num] = rev_rot[0];
}

void MakeHashTable()
{
    register int i = 0, j = 0;
    int block_num;

    for (i = 8; i > 0; i--)
    {
        for (j = 0; j < num_table[i]; j++)
        {
            block_num = table[i][j];

            int h = mpos[block_num] % MAX_HASH;
            while (hash_table[h] != 0)
            {
                h = (h + 1) % MAX_HASH;

            }
            hash_table[h] = block_num;
        }
    }
}


int FindHash()
{
    register int i = 0, j = 0;
    int block_num;
    unsigned int cur_pos = 0;
    unsigned int match = 0;

    int ret = 0;

    for (i = 8; i > 0; i--)
    {
        for (j = 0; j < num_table[i]; j++)
        {
            block_num = table[i][j];;

            if (used[block_num])
                continue;

            used[block_num] = 1;

            match = 2863311530u - pos[block_num];
            if (max_Arr[block_num] - min_Arr[block_num] == 1)
            {
                match = 1431655765u - pos[block_num];
            }

            int ha = match % MAX_HASH;
            while (hash_table[ha])
            {
                int rev_block = hash_table[ha];
                if (!used[rev_block])
                {
                    if (match == mpos[rev_block])
                    {
                        ret += min_Arr[block_num] + max_Arr[rev_block];
                        used[rev_block] = 1;
                        break;
                    }
                }
                ha = (ha + 1) % MAX_HASH;
            }
        }
    }

    return ret;
}


int makeBlock(int module[][4][4])
{
    register int i = 0, j = 0;
    int ret = 0;

    for (i = 0; i < 10; i++)
    {
        num_table[i] = 0;
    }

    for (i = 0; i < MAX; i++)
    {
        GetBlockInfo(i, module[i]);
    }

    for (i = 0; i < MAX_HASH; i++)
    {
        hash_table[i] = 0;
    }

    MakeHashTable();

    ret = FindHash();

    return ret;
}