//#define MAXN		100
//#define MAXL		8
//#define MAX_TABLE 50000
//#define hash(a) (a % MAX_TABLE)
//#define NULL 0
//#define ull unsigned long long
//#define R register
//
//struct BI
//{
//	int dTime; //durableTime
//	int isUsed; //입고시간
//	int pID; //자전거의 위치
//}bi[100000];
//int arr_bi;
//BI* myalloc_BI(void)
//{
//	bi[arr_bi].dTime = bi[arr_bi].isUsed = 0;
//	return &bi[arr_bi++];
//}
//
//struct TICKET
//{
//	ull name;
//	int st; //start
//	int end; //end
//	int rt; // rent Time
//	BI* rent;
//}ticket[MAX_TABLE];
//
//struct STORE
//{
//	BI* heap[70000]; //각 대여점의 최대 자전거 개수
//	int heapSize;
//	int deliveryTime; //배달되는 시간
//
//	void init(void)
//	{
//		heapSize = 0; //초기화
//	}
//
//	int heapPush(BI* nbi)
//	{
//		heap[heapSize] = nbi;
//
//		R int current = heapSize;
//		while (current > 0 && heap[current]->dTime < heap[(current - 1) / 2]->dTime)
//		{
//			R BI* temp = heap[(current - 1) / 2];
//			heap[(current - 1) / 2] = heap[current];
//			heap[current] = temp;
//			current = (current - 1) / 2;
//		}
//
//		heapSize = heapSize + 1;
//
//		return 1;
//	}
//
//	BI* heapPop(void)
//	{
//		if (heapSize <= 0)
//		{
//			R BI t;
//			t.isUsed = -1;
//			return &t;
//		}
//
//		R BI* value = heap[0];
//		heapSize = heapSize - 1;
//
//		heap[0] = heap[heapSize];
//
//		R int current = 0;
//		while (current * 2 + 1 < heapSize)
//		{
//			R int child;
//			if (current * 2 + 2 == heapSize)
//			{
//				child = current * 2 + 1;
//			}
//			else
//			{
//				child = heap[current * 2 + 1]->dTime < heap[current * 2 + 2]->dTime ? current * 2 + 1 : current * 2 + 2;
//			}
//
//			if (heap[current]->dTime < heap[child]->dTime)
//			{
//				break;
//			}
//
//			R BI* temp = heap[current];
//			heap[current] = heap[child];
//			heap[child] = temp;
//
//			current = child;
//		}
//		return value;
//	}
//} store[MAXN];
//
//BI* h[70000];
//int hS;
//int hPush(BI* nbi)
//{
//	h[hS] = nbi;
//
//	int current = hS;
//	while (current > 0 && h[current]->isUsed < h[(current - 1) / 2]->isUsed)
//	{
//		BI* temp = h[(current - 1) / 2];
//		h[(current - 1) / 2] = h[current];
//		h[current] = temp;
//		current = (current - 1) / 2;
//	}
//
//	hS = hS + 1;
//
//	return 1;
//}
//
//BI* hPop(void)
//{
//	if (hS <= 0)
//	{
//		BI t;
//		t.isUsed = -1;
//		return &t;
//	}
//
//	BI* value = h[0];
//	hS = hS - 1;
//
//	h[0] = h[hS];
//
//	int current = 0;
//	while (current * 2 + 1 < hS)
//	{
//		int child;
//		if (current * 2 + 2 == hS)
//		{
//			child = current * 2 + 1;
//		}
//		else
//		{
//			child = h[current * 2 + 1]->isUsed < h[current * 2 + 2]->isUsed ? current * 2 + 1 : current * 2 + 2;
//		}
//
//		if (h[current]->isUsed < h[child]->isUsed)
//		{
//			break;
//		}
//
//		BI* temp = h[current];
//		h[current] = h[child];
//		h[child] = temp;
//
//		current = child;
//	}
//	return value;
//}
//
//int hTop(void)
//{
//	return h[0]->isUsed;
//}
//
//int DTIME; //durableTIme
//
//void init(int N, int durableTime, int deliveryTimes[MAXN])
//{
//	arr_bi = 0;
//	for (R int i = 0; i < N; i++)
//	{
//		store[i].init();
//		store[i].deliveryTime = deliveryTimes[i];
//	}
//	DTIME = durableTime; //최대이용시간
//
//	for (R int i = 0; i < MAX_TABLE; i++)
//	{
//		ticket[i].name = 0; //ticket hashTable 초기화
//		ticket[i].st = ticket[i].end = ticket[i].rt = 0;
//		ticket[i].rent = NULL;
//	}
//	hS = 0;
//}
//
//void addBicycle(int cTimestamp, int pID, int bicycleNum)
//{
//	for (R int i = 0; i < bicycleNum; i++)
//	{
//		R BI* nbi = myalloc_BI(); //새로운 자전거 할당
//		nbi->isUsed = cTimestamp; //cTime부터 사용가능합니다
//
//		store[pID].heapPush(nbi); //pID 대여소에 추가.
//	}
//}
//
//TICKET* find(char uName[MAXL]) //고객정보 찾기
//{
//	R ull n = 0; //str to ull
//	for (R int i = 0; uName[i] != NULL; i++)
//	{
//		n = n << 5;
//		n = n + (uName[i] - 'a' + 1);
//	}
//
//	R int key = hash(n); //hashing
//	while (1)
//	{
//		if (ticket[key].name == n || ticket[key].name == 0)
//		{
//			if (ticket[key].name == 0)
//			{
//				ticket[key].name = n; //구매정보가 없으면 만들어줌.
//			}
//			break;
//		}
//
//		key = key + 1;
//		key = hash(key); //open addressing
//	}
//
//	return &ticket[key]; //현재 key를 return
//}
//
//void buyTicket(int cTimestamp, char uName[MAXL], int validTime)
//{
//	R TICKET* nTicket = find(uName); //고객찾기
//	if (nTicket->end < cTimestamp)
//	{
//		nTicket->st = cTimestamp; //st시간부터
//		nTicket->end = cTimestamp + validTime - 1; //end시간까지 티켓구매
//	}
//	else
//	{
//		nTicket->end += validTime; //아직 만료 안 됐으면 티켓에 시간 추가
//	}
//}
//
//int rentBicycle(int cTimestamp, char uName[MAXL], int pID)
//{
//	R TICKET* bTicket = find(uName); //고객찾기
//	if (bTicket->rent != NULL) //아직 반납 안했으면 -1
//	{
//		return -1;
//	}
//	else if (bTicket->end < cTimestamp) //티켓이 만료됐으면 -1
//	{
//		return -1;
//	}
//
//	while (1)
//	{
//		if (hS == 0)
//		{
//			break;
//		}
//		if (hTop() <= cTimestamp)
//		{
//			R BI* t = hPop();
//			store[t->pID].heapPush(t); //각 대여소에 자전거 추가.
//		}
//		else
//		{
//			break;
//		}
//	}
//
//	R BI* t = store[pID].heapPop(); //대여소에서 우선순위 젤 높은거 한개 뽑음.
//	if (t->isUsed == -1) //만약 자전거가 없으면 -1
//	{
//		return -1;
//	}
//	else //자전거가 있으면
//	{
//		bTicket->rent = t; //bTicket(고객)은 이 자전거를 빌림.
//		bTicket->rt = cTimestamp; //cTimestamp 시간에.
//	}
//
//	return bTicket->rent->dTime; //현재 자전거의 운용시간을 return
//}
//
//int returnBicycle(int cTimestamp, char uName[MAXL], int pID)
//{
//	R TICKET* bTicket = find(uName); //고객정보 찾음
//	if (bTicket->rent == NULL) //빌린게 없으면 -1
//	{
//		return -1;
//	}
//
//	bTicket->rent->dTime += (cTimestamp - bTicket->rt); //일단 운용시간에 빌린시간(탔던시간)을 더함.
//	if (bTicket->rent->dTime > DTIME) //그게 만약 최대운용시간을 넘으면?
//	{
//		bTicket->rent->dTime = 0; //운용시간 초기화.
//		bTicket->rent->isUsed = cTimestamp + store[pID].deliveryTime; //도착할 시간으로 바꾸고
//		bTicket->rent->pID = pID; //대여소 정보도 입력 후
//		hPush(bTicket->rent);
//	}
//	else
//	{
//		store[pID].heapPush(bTicket->rent); //최대운용시간을 넘지않으면 그대로 대여소에 추가.
//	}
//
//	bTicket->rent = NULL; //bTicket(고객)은 빌린걸 반납했으니, NULL로 초기화.
//
//	if (bTicket->end >= cTimestamp) //만약에 연체가 아니면
//	{
//		return 0; //0을 return
//	}
//	else //연체면?
//	{
//		return cTimestamp - (bTicket->end); //연체된 시간을 return
//	}
//}
