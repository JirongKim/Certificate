#define MAXN        100
#define MAXL        8
#define MAX_BIC     20000
#define MAX_C       10000
#define CHASH       20003
typedef unsigned long long ull;

struct RentStation {
    int newBic;
    int delTime;
    int queue[MAX_BIC];
    int front;
    int rear;
} R[MAXN];
int _heap[MAXN][MAX_BIC];
int _heapSize[MAXN];

struct Client {
    ull key;
    int idx;
    int validTime;
    int time;
    bool rent;
    Client* next;
} C[MAX_C], * cTable[CHASH];
int cIndex;

int duraT;

#define heap _heap[i]
#define heapSize _heapSize[i]
void heapPush(int i, int value);
int heapPop(int i);
ull c2ull(char* item);

void init(int N, int durableTime, int deliveryTimes[MAXN])
{
    duraT = durableTime;
    for (register int i = 0; i < N; ++i) {
        R[i].delTime = deliveryTimes[i];
        R[i].front = R[i].rear = R[i].newBic = heapSize = 0;
    }

    cIndex = 0;
    for (register int i = 0; i < CHASH; ++i) {
        cTable[i] = 0;
    }
}

void addBicycle(int cTimestamp, int pID, int bicycleNum)
{
    R[pID].newBic += bicycleNum;
}

void buyTicket(int cTimestamp, char uName[MAXL], int validTime)
{
    ull key = c2ull(uName);
    int chash = key % CHASH;
    int idx = -1;
    Client* c = cTable[chash];
    while (c) {
        if (key == c->key) {
            idx = c->idx;
            break;
        }
        c = c->next;
    }

    if (idx == -1) {
        c = &C[cIndex];
        c->key = key;
        idx = cIndex;
        c->idx = cIndex++;
        c->rent = false;
        c->time = c->validTime = 0;
        c->next = cTable[chash];
        cTable[chash] = c;
    }

    if (C[idx].validTime < cTimestamp)
        C[idx].validTime = cTimestamp + validTime - 1;
    else
        C[idx].validTime += validTime;

}

int rentBicycle(int cTimestamp, char uName[MAXL], int pID)
{
    ull key = c2ull(uName);
    int chash = key % CHASH;
    int idx = -1;
    Client* c = cTable[chash];
    while (c) {
        if (key == c->key) {
            idx = c->idx;
            break;
        }
        c = c->next;
    }

    while (R[pID].front != R[pID].rear) {
        if (R[pID].queue[R[pID].rear] > cTimestamp) break;
        ++R[pID].newBic;
        ++R[pID].rear;
        if (R[pID].rear == MAX_BIC) R[pID].rear = 0;
    }

    if (idx == -1 || C[idx].rent ||
        C[idx].validTime < cTimestamp ||
        (R[pID].newBic == 0 && _heapSize[pID] == 0))
        return -1;

    C[idx].rent = true;
    if (R[pID].newBic != 0) {
        --R[pID].newBic;
        C[idx].time = -cTimestamp;
        return 0;
    }
    else {
        int usingTime = heapPop(pID);
        C[idx].time = usingTime - cTimestamp;
        return usingTime;
    }
}

int returnBicycle(int cTimestamp, char uName[MAXL], int pID)
{
    ull key = c2ull(uName);
    int chash = key % CHASH;
    int idx = -1;
    Client* c = cTable[chash];
    while (c) {
        if (key == c->key) {
            idx = c->idx;
            break;
        }
        c = c->next;
    }

    if (idx == -1 || !C[idx].rent) return -1;
    C[idx].rent = false;

    int usingTime = cTimestamp + C[idx].time;

    if (usingTime > duraT) {
        R[pID].queue[R[pID].front++] = cTimestamp + R[pID].delTime;
        if (R[pID].front == MAX_BIC) R[pID].front = 0;
    }
    else {
        heapPush(pID, usingTime);
    }

    if (C[idx].validTime >= cTimestamp) return 0;
    else return cTimestamp - C[idx].validTime;
}

void heapPush(int i, int value)
{

    heap[heapSize] = value;

    int current = heapSize;
    while (current > 0 && heap[current] < heap[(current - 1) / 2])
    {
        int temp = heap[(current - 1) / 2];
        heap[(current - 1) / 2] = heap[current];
        heap[current] = temp;
        current = (current - 1) / 2;
    }

    ++heapSize;

    return;
}

int heapPop(int i)
{
    int ret = heap[0];

    --heapSize;
    heap[0] = heap[heapSize];

    int current = 0;
    while (current * 2 + 1 < heapSize)
    {
        int child;
        if (current * 2 + 2 == heapSize)
        {
            child = current * 2 + 1;
        }
        else
        {
            child = heap[current * 2 + 1] < heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
        }

        if (heap[current] < heap[child])
        {
            break;
        }

        int temp = heap[current];
        heap[current] = heap[child];
        heap[child] = temp;

        current = child;
    }
    return ret;
}

ull c2ull(char* item) {
    ull key = 0;
    for (register int i = 0; item[i]; ++i) {
        key = (key << 5) + item[i] - 96;
    }
    return key;
}