#define MAX_NAME_LEN (4+1)
#define MAX_GROUP 20
#define MAX_NAME 30000
#define MAX_NUMBER 100000
#define MAX_TABLE (MAX_NAME * 2 + 7)
#define NULL 0

#define hash(h) (h % MAX_TABLE)
#define SCORE(t, f) ((t << 1) + f)

struct NUMBER
{
    int score;
    int asset;
    bool isDeleted;
} number[MAX_NUMBER];

struct GROUP
{
    int user_name;
    int user_group;
    NUMBER* num;
    GROUP* prev;
} group[MAX_GROUP];
int arr_group = 0;

struct NAME
{
    int user_name;
    NUMBER* num;
    NAME* prev;
} name[MAX_NAME];
int arr_name = 0;
NAME* myalloc_name(void) { return &name[arr_name++]; }

NAME* nameTable[MAX_TABLE];

void init() {
    for (int i = 0; i < arr_name; i++)
    {
        name[i].user_name = 0;
        name[i].num = NULL;
        name[i].prev = NULL;
    }
    arr_group = 0;
    arr_name = 0;

    for (int i = 0; i < MAX_TABLE; i++)
    {
        nameTable[i] = NULL;
    }

    for (int i = 0; i < MAX_NAME; i++)
    {
        number[i].score = 0;
        number[i].asset = 0;
        number[i].isDeleted = 0;
    }
}

int strToint(char* str)
{
    int r = 0;
    for (int i = 0; str[i] != NULL; i++)
    {
        r = r << 5;
        r = r + (str[i] - 'a' + 1);
    }
    return r;
}

void addName(int n, NUMBER* newNum)
{
    int key = hash(n);

    while (1)
    {
        if (nameTable[key] == NULL)
        {
            NAME* newName = myalloc_name();
            newName->user_name = n;
            newName->num = newNum;
            break;
        }
        else
        {
            if (nameTable[key]->user_name == n)
            {
                // 이부분 수정
            }
        }
        key = key + 1;
        key = hash(key);
    }
}

void openAccount(int mTime, char mName[MAX_NAME_LEN], char mGroup[MAX_NAME_LEN], int mNumber, int mAsset) {
    number[mNumber].asset = mAsset;
    number[mNumber].score = SCORE(mTime, 0);

    addName(strToint(mName), &number[mNumber]);
}

int closeAccount(int mTime, int mNumber) {
    return 0;
}

int sendByNumber(int mTime, int mNumber, int mReceiveNumber, int mValue) {
    return 0;
}

int sendByName(int mTime, int mNumber, char mReceiveName[MAX_NAME_LEN], int mValue) {
    return 0;
}

void sendBonus(int mTime, char mGroup[MAX_NAME_LEN], int mValue) {

}