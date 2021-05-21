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
#define MAX_HASH 264217 //hash table의 크기.

unsigned int pos[MAX], mpos[MAX]; // block의 조합을 저장해놓음.
int min_Arr[MAX], max_Arr[MAX]; // block의 min, max값을 저장하는 배열

int num_table[10]; // block의 base를 저장하는곳.
int table[10][MAX]; // block의 base를 hash table로 생성함
int used[MAX]; // block의 몇번째는 사용하였다는 것을 저장하는 배열
int hash_table[MAX_HASH]; // hash table

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
            min = min > MyModule[i][j] ? MyModule[i][j] : min; // mymodule 배열의 min 값을 찾음.
            max = max < MyModule[i][j] ? MyModule[i][j] : max; // mymodule 배열의 max 값을 찾음.
        }

    }

    used[num] = 0; // num은 block의 index.
    min_Arr[num] = min;
    max_Arr[num] = max;

    table[min][num_table[min]++] = num; // base기준으로 중복 되지 않는 위치에, block index값을 넣어줌.

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            Norm[i][j] = MyModule[i][j] - min; // norm 배열은, block배열에서 base 값을 빼서 0,1,2 로만 표현함
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
    //상화좌우 돌려봐서 shift연산자로 int형에 넣었을 때 int형이 가장 큰 것을 rot[0], rev_rot[0]에 입력함.

    pos[num] = rot[0]; //pos에는 rot[0]을 넣고
    mpos[num] = rev_rot[0]; //mpos에는 rev_rot[0]을 넣음
}

void MakeHashTable()
{
    register int i = 0, j = 0;
    int block_num;

    for (i = 8; i > 0; i--) // 최대값을 구하기 위하여, base가 큰 값부터 hash table에 넣음.
    {
        for (j = 0; j < num_table[i]; j++)
        {
            block_num = table[i][j]; // block index를 block_num에 넣음.

            int h = mpos[block_num] % MAX_HASH; //max hast는 1과 자기자신 제외하고 나눠떨어지지 않는 소수임.
            // h는 해쉬의 key 값이 됨.
            while (hash_table[h] != 0) // 해쉬의 key값의 배열이 0인곳을 찾아서 
            {
                h = (h + 1) % MAX_HASH; // 해쉬의 key값의 배열이 0이아니라면

            }
            hash_table[h] = block_num; // 그곳에 block index를 넣음.
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
            block_num = table[i][j]; // block_num에 block index를 넣어줌.

            if (used[block_num]) // 만약 이 블럭이 이미 재사용이 되었다고 한다면, 건너뜀.
                continue;

            used[block_num] = 1; // 블럭이 이제 사용됨.

            match = 2863311530u - pos[block_num]; // match는 0xAAAAAAAA (block의 최대값)에서 shift연산한 값을 뺌.
            if (max_Arr[block_num] - min_Arr[block_num] == 1) //근데 만약 최대가 5인데, 최소가 4라면
            {
                match = 1431655765u - pos[block_num]; // match는 0x55555555에서 shift연산한 값을 뺌.
            }

            int ha = match % MAX_HASH; // ha는 함수 key값임.
            while (hash_table[ha]) // hash_table에 ha번째 값이 0이면 나가짐.
            {
                int rev_block = hash_table[ha]; // pos+mpos가 0xAAAAAAAA 아니면 0x55555555가 되야 딲 맞는거임.
                if (!used[rev_block]) //rev_block이 사용됐다면 skip.
            
                {
                    if (match == mpos[rev_block]) //match는 0xAAAAAAAA-pos 이기 때문에, 둘이 딱 맞다면 true임.
                    {
                        ret += min_Arr[block_num] + max_Arr[rev_block]; // ret에는 block_num의 최소, rev_block의 최대를 더함.
                        used[rev_block] = 1; //rev_block은 사용한 배열로 처리해줌
                        break;
                    }
                }
                ha = (ha + 1) % MAX_HASH; //만약 딱 맞아떨어지는 부품이 아니면 한개씩 증가하면서 탐색.
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
        num_table[i] = 0; // block의 base를 세는 변수 초기화
    }

    for (i = 0; i < MAX; i++)
    {
        GetBlockInfo(i, module[i]); // 
    }

    for (i = 0; i < MAX_HASH; i++)
    {
        hash_table[i] = 0;
    }

    MakeHashTable();

    ret = FindHash();

    return ret;
}