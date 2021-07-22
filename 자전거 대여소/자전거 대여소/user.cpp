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
//	int isUsed; //�԰�ð�
//	int pID; //�������� ��ġ
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
//	BI* heap[70000]; //�� �뿩���� �ִ� ������ ����
//	int heapSize;
//	int deliveryTime; //��޵Ǵ� �ð�
//
//	void init(void)
//	{
//		heapSize = 0; //�ʱ�ȭ
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
//	DTIME = durableTime; //�ִ��̿�ð�
//
//	for (R int i = 0; i < MAX_TABLE; i++)
//	{
//		ticket[i].name = 0; //ticket hashTable �ʱ�ȭ
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
//		R BI* nbi = myalloc_BI(); //���ο� ������ �Ҵ�
//		nbi->isUsed = cTimestamp; //cTime���� ��밡���մϴ�
//
//		store[pID].heapPush(nbi); //pID �뿩�ҿ� �߰�.
//	}
//}
//
//TICKET* find(char uName[MAXL]) //������ ã��
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
//				ticket[key].name = n; //���������� ������ �������.
//			}
//			break;
//		}
//
//		key = key + 1;
//		key = hash(key); //open addressing
//	}
//
//	return &ticket[key]; //���� key�� return
//}
//
//void buyTicket(int cTimestamp, char uName[MAXL], int validTime)
//{
//	R TICKET* nTicket = find(uName); //��ã��
//	if (nTicket->end < cTimestamp)
//	{
//		nTicket->st = cTimestamp; //st�ð�����
//		nTicket->end = cTimestamp + validTime - 1; //end�ð����� Ƽ�ϱ���
//	}
//	else
//	{
//		nTicket->end += validTime; //���� ���� �� ������ Ƽ�Ͽ� �ð� �߰�
//	}
//}
//
//int rentBicycle(int cTimestamp, char uName[MAXL], int pID)
//{
//	R TICKET* bTicket = find(uName); //��ã��
//	if (bTicket->rent != NULL) //���� �ݳ� �������� -1
//	{
//		return -1;
//	}
//	else if (bTicket->end < cTimestamp) //Ƽ���� ��������� -1
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
//			store[t->pID].heapPush(t); //�� �뿩�ҿ� ������ �߰�.
//		}
//		else
//		{
//			break;
//		}
//	}
//
//	R BI* t = store[pID].heapPop(); //�뿩�ҿ��� �켱���� �� ������ �Ѱ� ����.
//	if (t->isUsed == -1) //���� �����Ű� ������ -1
//	{
//		return -1;
//	}
//	else //�����Ű� ������
//	{
//		bTicket->rent = t; //bTicket(��)�� �� �����Ÿ� ����.
//		bTicket->rt = cTimestamp; //cTimestamp �ð���.
//	}
//
//	return bTicket->rent->dTime; //���� �������� ���ð��� return
//}
//
//int returnBicycle(int cTimestamp, char uName[MAXL], int pID)
//{
//	R TICKET* bTicket = find(uName); //������ ã��
//	if (bTicket->rent == NULL) //������ ������ -1
//	{
//		return -1;
//	}
//
//	bTicket->rent->dTime += (cTimestamp - bTicket->rt); //�ϴ� ���ð��� �����ð�(�����ð�)�� ����.
//	if (bTicket->rent->dTime > DTIME) //�װ� ���� �ִ���ð��� ������?
//	{
//		bTicket->rent->dTime = 0; //���ð� �ʱ�ȭ.
//		bTicket->rent->isUsed = cTimestamp + store[pID].deliveryTime; //������ �ð����� �ٲٰ�
//		bTicket->rent->pID = pID; //�뿩�� ������ �Է� ��
//		hPush(bTicket->rent);
//	}
//	else
//	{
//		store[pID].heapPush(bTicket->rent); //�ִ���ð��� ���������� �״�� �뿩�ҿ� �߰�.
//	}
//
//	bTicket->rent = NULL; //bTicket(��)�� ������ �ݳ�������, NULL�� �ʱ�ȭ.
//
//	if (bTicket->end >= cTimestamp) //���࿡ ��ü�� �ƴϸ�
//	{
//		return 0; //0�� return
//	}
//	else //��ü��?
//	{
//		return cTimestamp - (bTicket->end); //��ü�� �ð��� return
//	}
//}
