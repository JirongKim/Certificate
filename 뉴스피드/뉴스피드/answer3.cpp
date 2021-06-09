#define MAX_NEWS 50001
#define MAX_SEC 10
#define MAX_USER 100001

struct News {
    int id;
    int section;
    int read;
    int heapIdx;
    int score;

    void set(int id, int section) {
        this->id = id;
        this->section = section;
        this->read = 0;
        updateScore();
    }

    void updateScore() {
        score = read * 50000 + id - 1;
    }

    void newsRead()
    {
        read++;
        updateScore();
    }
};

struct Heap {
    News* node[MAX_NEWS];
    int size;
    void reset() {
        size = 0;
    }
    void push(News* news) {
        node[size] = news; //1. 맨뒤에 넣고
        node[size]->heapIdx = size;

        moveUp(size++);  //올린다  
    }
    News* pop() {
        if (size <= 0) return nullptr;
        News* tmp = node[0];
        node[0] = node[--size];
        node[0]->heapIdx = 0;

        moveDown(0);
        return tmp;
    }
    void moveUp(int cur) {
        int next = (cur - 1) / 2;
        while (cur > 0 && node[cur]->score > node[next]->score) {
            News* tmp = node[next];
            node[next] = node[cur];
            node[cur] = tmp;
            node[next]->heapIdx = next;
            node[cur]->heapIdx = cur;

            cur = next;
            next = (cur - 1) / 2;
        }
    }

    void moveDown(int cur) {
        int next = cur * 2 + 1;
        while (next < size) {
            int child = next;
            if (next + 1 < size && node[next]->score < node[next + 1]->score)
                child = next + 1;
            if (node[child]->score < node[cur]->score) break;

            News* tmp = node[child];
            node[child] = node[cur];
            node[cur] = tmp;
            node[child]->heapIdx = child;
            node[cur]->heapIdx = cur;

            cur = child;
            next = cur * 2 + 1;
        }
    }
    void update(News* news) {
        if (size <= 1) return;
        int cur = news->heapIdx;
        int parent = (cur - 1) / 2;
        if (cur == 0 || node[cur]->score < node[parent]->score)
            moveDown(cur);
        else
            moveUp(cur);
    }
    void remove(News* news) {
        int cur = news->heapIdx;
        node[cur] = node[--size];
        node[cur]->heapIdx = cur;

        update(node[cur]);
    }
};

int recentlyReadSectionByUser[MAX_USER];
News tbNews[MAX_NEWS];
Heap heap[MAX_SEC];

void init()
{
    register int i;
    for (i = 0; i < MAX_USER; ++i)
        recentlyReadSectionByUser[i] = -1;

    for (i = 0; i < MAX_SEC; ++i)
        heap[i].reset();
}

void addNews(int mSection, int mNewsId)
{
    News* news = &tbNews[mNewsId];
    news->set(mNewsId, mSection);

    heap[mSection].push(news);
}

void eraseNews(int mNewsId)
{
    News* news = &tbNews[mNewsId];
    heap[news->section].remove(news);
}

void readNews(int mUserId, int mNewsId)
{
    News* news = &tbNews[mNewsId];
    news->newsRead();
    heap[news->section].update(news);

    recentlyReadSectionByUser[mUserId] = news->section;
}

void changeSection(int mNewsId, int mSection)
{
    News* news = &tbNews[mNewsId];
    heap[news->section].remove(news);

    news->section = mSection;
    heap[news->section].push(news);
}

int getList(int mUserId, int mList[])
{
    register int i, j;

    struct Data {
        News* news;
        int score;
    }candi[10];  //10개의 후보를 담아둔다.
    int result = 0;

    for (i = 0; i < 10; ++i) {
        candi[i].news = nullptr;
        for (j = 0; j < MAX_SEC; ++j) {
            if (!heap[j].size) continue;
            int bonus = recentlyReadSectionByUser[mUserId] == j ? 500000 : 0;
            int newScore = heap[j].node[0]->score + bonus;
            if (!candi[i].news || newScore > candi[i].score) {  // 10개 힙을 돌면서 가장 값이 큰 경우만 넣어두자
                candi[i].news = heap[j].node[0];
                candi[i].score = newScore;
            }
        }
        if (!candi[i].news)  // 더 이상 들어올게 없으므로 break
            break;

        News* tmp = heap[candi[i].news->section].pop();  //후보에 들어온것은 빼내기
        ++result;
    }
    for (i = 0; i < result; ++i) {
        mList[i] = candi[i].news->id;
        heap[candi[i].news->section].push(candi[i].news);  // 다시 넣어두자.
    }

    return result;
}