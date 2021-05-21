//#define R register
//#define ull unsigned long long
//
//#define MAX_USER 1001
//#define MAX_AREA 11
//#define MAX_FND 20 //친구의 총 갯수
//#define MAX_ITEM 40000 //ADD의 총 갯수
//#define MAX_HASH 100003
//
//struct User {
//    int fnd[MAX_FND];
//    int fnd_cnt;
//    int area_cnt[MAX_AREA];
//    int area_total[MAX_AREA];
//} users[MAX_USER];
//
//struct Item {
//    int pid;
//    int area;
//    ull score;
//    bool sold;
//    Item* next;
//}np[MAX_ITEM], * ht[100003];
//int sidx;
//
//#define hval(x) np[data[x]].score
//#define nval(x) np[x].score
//struct Heap {
//    int data[MAX_ITEM + 1];
//    int size;
//    void push(int sidx) {
//        if (size == MAX_ITEM) return;
//        R int cur = ++size;
//        while (cur != 1 && nval(sidx) < hval(cur >> 1)) {
//            data[cur] = data[cur >> 1]; //cur는 비었으니까, swap이 아니고 덮어씌우면 됨. insertion sort와 비슷한 개념.
//            cur >>= 1;
//        }
//        data[cur] = sidx;
//        // np는 0부터 시작하고,
//        // data는 1부터 시작하기 때문에, >>1로만으로도 표현이 가능.
//    }
//    int pop() {
//        if (!size) return -1;
//        int ret = data[1];
//        R int e = data[size--];
//        R int cur = 1, ch = 2;
//        while (ch <= size) {
//            if (ch + 1 <= size && hval(ch) > hval(ch + 1))ch++;
//            if (nval(e) <= hval(ch)) break;
//            data[cur] = data[ch];
//            cur = ch; ch <<= 1;
//        }
//        data[cur] = e;
//        return ret;
//    }
//
//    int top() {
//        return size ? data[1] : -1;
//    }
//}areas[MAX_AREA];
//
//int max_m;
//void init(int N, int M)
//{
//    sidx = 0;
//    max_m = M;
//    for (R int i = 0; i < MAX_HASH; i++) {
//        ht[i] = 0;
//        if (i <= N) {
//            users[i].fnd_cnt = 0;
//            for (R int j = 1; j <= M; j++) {
//                users[i].area_cnt[j] = 0;
//                users[i].area_total[j] = 0;
//            }
//        }
//    }
//    for (R int i = 1; i <= M; i++) {
//        areas[i].size = 0;
//    }
//}
//
//#define SWAP(a, b) R ull t = arr[a]; arr[a] = arr[b]; arr[b] = t;
//void qsort(int l, int r, ull* arr) {
//    if (l < r) {
//        ull p = arr[l];
//        int i = l;
//        int j = r;
//        while (i < j) {
//            while (arr[i] <= p && i < r) i++;
//            while (arr[j] > p) j--;
//            if (i < j) {
//                SWAP(i, j);
//            }
//        }
//        SWAP(l, j);
//        qsort(l, j - 1, arr);
//        qsort(j + 1, r, arr);
//    }
//}
//
//Item* findItem(int pid) {
//    Item* item = ht[pid % MAX_HASH];
//    while (item) {
//        if (item->pid == pid) {
//            return item;
//        }
//        item = item->next;
//    }
//    return item;
//}
//
//#define getScore(x, y) (ull)x << 30 | y
//void befriend(int uid1, int uid2)
//{
//    users[uid1].fnd[users[uid1].fnd_cnt++] = uid2;
//    users[uid2].fnd[users[uid2].fnd_cnt++] = uid1;
//    for (R int i = 1; i <= max_m; i++) {
//        users[uid1].area_total[i] += users[uid2].area_cnt[i]; //이런식으로 user의 토탈 지역개수를 더해줌.
//        users[uid2].area_total[i] += users[uid1].area_cnt[i];
//    }
//}
//
//void add(int pid, int area, int price)
//{
//    Item* item = &np[sidx];
//    item->pid = pid;
//    item->area = area;
//    item->score = getScore(price, pid); //price를 <<30 하고, 거기에 pid를 더해줌. 왜냐하면 pid는 10억이고, 30비트로 표현이 가능함.
//    item->sold = false;
//    item->next = ht[pid % MAX_HASH];
//    ht[pid % MAX_HASH] = item; //linked list.
//    areas[area].push(sidx++);
//}
//
//void reserve(int uid, int pid)
//{
//    Item* item = findItem(pid);
//    item->sold = true;
//    users[uid].area_cnt[item->area]++;
//    users[uid].area_total[item->area]++;
//    for (R int i = 0; i < users[uid].fnd_cnt; i++)
//        users[users[uid].fnd[i]].area_total[item->area]++;
//
//    R int a = item->area;
//    while (areas[a].size && np[areas[a].top()].sold) {
//        areas[a].pop();
//    }
//}
//
//int recommend(int uid)
//{
//    ull arrs[MAX_AREA] = { 0, };
//    int cnt = 1;
//    for (R int i = 1; i <= max_m; i++) {
//        if (!areas[i].size) {
//            continue;
//        }
//        R ull area_cnt = users[uid].area_total[i];
//        area_cnt = (MAX_ITEM + 1) - area_cnt;
//        R int idx = areas[i].top();
//        arrs[cnt] = (ull)area_cnt << 42 | np[idx].score;
//        cnt++;
//    }
//    qsort(1, cnt - 1, arrs);
//
//    return (int)(arrs[1] & 0x3FFFFFFF);
//}
