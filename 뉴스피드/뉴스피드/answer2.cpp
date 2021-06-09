//#define MAX_USER    100001
//#define MAX_NEWS    50001
//#define MAX_SECTION 10
//#define SCORE_UNIT  60000
//#define SCORE_BONUS 10
//#define MAX_RET     10
//
//#define PARENT(n)   (((n) - 1) / 2)
//#define LEFT(n)     (((n) * 2) + 1)
//#define RIGHT(n)     (((n) * 2) + 2)
//
//typedef struct _news
//{
//    int id;
//    int section;
//    int read_cnt;
//    int heap_index;
//}NEWS;
//
//NEWS sNews[MAX_NEWS];
//
//NEWS* heap[MAX_SECTION][MAX_NEWS];
//int heap_num[MAX_SECTION];
//
//int user_section[MAX_USER];
//int first_time = 1;
//
//NEWS* ret_arry[MAX_SECTION];
//int ret_arry_num;
//
//void heapDown(register NEWS** p_heap, register int p_heapNum, register int parent);
//void heapUp(register NEWS** p_heap, register int child);
//void heapPush(register int section, register NEWS* pNode);
//NEWS* heapPop(register int section);
//
//void init() {
//    if (first_time) {
//        first_time = 0;
//        for (register int i = 1; i < MAX_NEWS; i++)    sNews[i].id = i;
//    }
//    for (register int i = 1; i < MAX_USER; i++)    user_section[i] = -1;
//    for (register int i = 0; i < MAX_SECTION; i++)    heap_num[i] = 0;
//}
//
//void addNews(register int mSection, register int mNewsId) {
//    sNews[mNewsId].section = mSection;
//    sNews[mNewsId].read_cnt = mNewsId;
//    heapPush(mSection, &sNews[mNewsId]);
//}
//
//void eraseNews(register int mNewsId) {
//    register int section = sNews[mNewsId].section;
//    register int heap_index = sNews[mNewsId].heap_index;
//
//    heap[section][heap_index] = heap[section][--heap_num[section]];
//    heap[section][heap_index]->heap_index = heap_index;
//    heapDown(heap[section], heap_num[section], heap_index);
//    heapUp(heap[section], heap_index);
//
//}
//
//void readNews(register int mUserId, register int mNewsId) {
//    user_section[mUserId] = sNews[mNewsId].section;
//    sNews[mNewsId].read_cnt += SCORE_UNIT;
//    heapUp(heap[sNews[mNewsId].section], sNews[mNewsId].heap_index);
//}
//
//void changeSection(register int mNewsId, register int mSection) {
//    eraseNews(mNewsId);
//    sNews[mNewsId].section = mSection;
//    heapPush(mSection, &sNews[mNewsId]);
//}
//
//int getList(int mUserId, int mList[]) {
//
//    register int section = user_section[mUserId];
//
//    ret_arry_num = 0;
//
//    while (ret_arry_num < 10) {
//        register int maxScore = 0;
//        register int maxScoreSectionIndex = -1;
//
//        for (register int i = 0; i < MAX_SECTION; i++) {
//            if (heap_num[i]) {
//                register int temp = (i != section) ? heap[i][0]->read_cnt : heap[i][0]->read_cnt + (SCORE_UNIT * SCORE_BONUS);
//
//                if (temp > maxScore) {
//                    maxScore = temp;
//                    maxScoreSectionIndex = i;
//                }
//            }
//        }
//
//        if (maxScoreSectionIndex == -1) break;
//
//        ret_arry[ret_arry_num++] = heapPop(maxScoreSectionIndex);
//    }
//
//    for (register int i = 0; i < ret_arry_num; i++) {
//        mList[i] = ret_arry[i]->id;
//        heapPush(ret_arry[i]->section, ret_arry[i]);
//    }
//
//    return ret_arry_num;
//}
//
//void heapDown(register NEWS** p_heap, register int p_heapNum, register int parent)
//{
//    while ((parent * 2) + 1 < p_heapNum)
//    {
//        register int child = (parent * 2) + 1;
//        if ((parent * 2) + 2 < p_heapNum)
//        {
//            if (p_heap[(parent * 2) + 1]->read_cnt < p_heap[(parent * 2) + 2]->read_cnt)
//                child = (parent * 2) + 2;
//        }
//
//        if (p_heap[parent]->read_cnt > p_heap[child]->read_cnt)
//            break;
//
//        register NEWS* pTemp = p_heap[parent];
//        p_heap[parent] = p_heap[child];
//        p_heap[child] = pTemp;
//
//        p_heap[parent]->heap_index = parent;
//        p_heap[child]->heap_index = child;
//
//        parent = child;
//    }
//}
//
//void heapUp(register NEWS** p_heap, register int child)
//{
//    while (child)
//    {
//        if (p_heap[(child - 1) / 2]->read_cnt > p_heap[child]->read_cnt) break;
//
//        register NEWS* pTemp = p_heap[(child - 1) / 2];
//        p_heap[(child - 1) / 2] = p_heap[child];
//        p_heap[child] = pTemp;
//
//        p_heap[(child - 1) / 2]->heap_index = (child - 1) / 2;
//        p_heap[child]->heap_index = child;
//
//        child = (child - 1) / 2;
//    }
//}
//
//
//void heapPush(register int section, register NEWS* pNode)
//{
//    heap[section][heap_num[section]] = pNode;
//    pNode->heap_index = heap_num[section];
//    heapUp(heap[section], heap_num[section]++);
//}
//
//NEWS* heapPop(register int section)
//{
//    register NEWS* pRet = heap[section][0];
//    heap[section][0] = heap[section][--heap_num[section]];
//    heap[section][0]->heap_index = 0;
//    heapDown(heap[section], heap_num[section], 0);
//
//    return pRet;
//}