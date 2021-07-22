//#define SIZE 10007
//
//struct LIST
//{
//    int timeStamp;
//    LIST* next;
//};
//LIST* list[100];
//LIST* tail[100];
//LIST POOL_list[25000];
//int pool_list;
//int ride[100];
//
//struct  HASH
//{
//    int index;
//    unsigned long long hashkey;
//    HASH* next;
//};
//HASH POOLH[10000];
//int ph;
//HASH* table[SIZE];
//
//struct USER
//{
//    int TimeTicket;
//    bool ride;
//    int rentTime;
//    int rideTime;
//};
//
//
//USER user[10000];
//int poolUser = 0;
//
//int heap[100][20000];
//int size[100];
//int _delivery[100];
//int _durableTime;
//
//
//void heapPush(int Pid, int rideTime)
//{
//    heap[Pid][size[Pid]] = rideTime;
//
//    int current = size[Pid];
//    while (current > 0 && heap[Pid][current] < heap[Pid][(current - 1) / 2])
//    {
//
//        int tempTime = heap[Pid][(current - 1) / 2];
//
//        heap[Pid][(current - 1) / 2] = heap[Pid][current];
//
//        heap[Pid][current] = tempTime;
//
//        current = (current - 1) / 2;
//    }
//
//    size[Pid]++;
//
//}
//void heapPop(int Pid)
//{
//    if (size[Pid] == 0) return;
//    size[Pid]--;
//    int current = 0;
//    heap[Pid][0] = heap[Pid][size[Pid]];
//    while (current * 2 + 1 < size[Pid])
//    {
//        int child;
//        if (current * 2 + 1 == size[Pid])
//        {
//            child = current * 2 + 1;
//        }
//        else
//        {
//            child = heap[Pid][current * 2 + 1] < heap[Pid][current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
//        }
//
//        if (heap[Pid][current] < heap[Pid][child])
//        {
//            break;
//        }
//        int tempTime = heap[Pid][current];
//
//        heap[Pid][current] = heap[Pid][child];
//
//        heap[Pid][child] = tempTime;
//
//        current = child;
//    }
//}
//
//unsigned long long hashkey(char name[]) {
//    unsigned long long h = 1;
//    for (int i = 0; name[i] != '\0'; i++) {
//        h = (h << 5) + name[i] - 'a';
//    }
//    return h;
//}
//
//void addHash(char name[]) {
//    unsigned long long key = hashkey(name);
//    int id = key % SIZE;
//
//    HASH* node = &POOLH[ph++];
//    node->hashkey = key;
//    node->index = poolUser;
//    node->next = nullptr;
//
//    if (table[id] == nullptr) {
//        table[id] = node;
//    }
//    else {
//        node->next = table[id];
//        table[id] = node;
//    }
//}
//
//int searchHash(char name[]) {
//    unsigned long long key = hashkey(name);
//    int id = key % SIZE;
//    HASH* node = table[id];
//    while (node)
//    {
//        if (node->hashkey == key) return node->index;
//        node = node->next;
//    }
//    return -1;
//}
//void init(int N, int durableTime, int delivery[]) {
//    pool_list = 0;
//    poolUser = 0;
//    ph = 0;
//    for (int i = 0; i < N; i++) {
//        _delivery[i] = delivery[i];
//        size[i] = 0;
//        list[i] = nullptr;
//        ride[i] = 0;
//    }
//    _durableTime = durableTime;
//    for (int i = 0; i < SIZE; i++) table[i] = nullptr;
//}
//
//void addBicycle(int cTimestamp, int pID, int bicycleNum) {
//    //heapPush(pID, bicycleNum, 0);
//    ride[pID] += bicycleNum;
//}
//
//void buyTicket(int cTimestamp, char uName[], int validTime) {
//    int index = searchHash(uName);
//    if (index == -1) {
//        addHash(uName);
//        user[poolUser].TimeTicket = validTime + cTimestamp - 1;
//        user[poolUser].ride = false;
//        user[poolUser].rideTime = 0;
//        poolUser++;
//    }
//    else {
//        if (user[index].TimeTicket < cTimestamp) {
//            user[index].TimeTicket = validTime + cTimestamp - 1;
//        }
//        else {
//            user[index].TimeTicket += validTime;
//        }
//    }
//}
//void updateBicycle(int pID, int cTime) {
//    LIST* temp = list[pID];
//    while (temp != nullptr && temp->timeStamp <= cTime)
//    {
//        //heapPush(pID, 1, 0);
//        ride[pID]++;
//        temp = temp->next;
//    }
//    list[pID] = temp;
//}
//int rentBicycle(int cTimestamp, char uName[], int pID) {
//
//    updateBicycle(pID, cTimestamp);
//
//    int index = searchHash(uName);
//    if (index == -1 || user[index].ride || user[index].TimeTicket < cTimestamp) return -1;
//    if (ride[pID] > 0) {
//        ride[pID]--;
//        user[index].ride = true;
//        user[index].rentTime = cTimestamp;
//        user[index].rideTime = 0;
//        return 0;
//    }
//    if (size[pID] == 0) return -1;
//    user[index].ride = true;
//    user[index].rentTime = cTimestamp;
//    user[index].rideTime = heap[pID][0];
//
//    heapPop(pID);
//
//    return user[index].rideTime;
//}
//
//int returnBicycle(int cTimestamp, char uName[], int pID) {
//    int index = searchHash(uName);
//    if (index == -1 || user[index].ride == false) return -1;
//    user[index].ride = false;
//    if (cTimestamp - user[index].rentTime + user[index].rideTime > _durableTime) {
//        LIST* newnode = &POOL_list[pool_list++];
//        newnode->next = nullptr;
//        newnode->timeStamp = cTimestamp + _delivery[pID];
//        if (list[pID] == nullptr) {
//            list[pID] = newnode;
//            tail[pID] = newnode;
//        }
//        else {
//            tail[pID]->next = newnode;
//            tail[pID] = newnode;
//        }
//    }
//    else {
//        heapPush(pID, cTimestamp - user[index].rentTime + user[index].rideTime);
//    }
//    if (user[index].TimeTicket >= cTimestamp) return 0;
//    return cTimestamp - user[index].TimeTicket;
//}