//#include <stdio.h>
//
//#define NULL 0
//#define nullptr 0
//const int MAX = 100000;
//
//struct NODE
//{
//	int track;
//	bool isDel;
//	NODE* queue;
//	NODE* prev;
//	NODE* next;
//} a[MAX];
//
//
//int arr_idx = 0;
//
//NODE* myalloc(void) { a[arr_idx].isDel = 0; return &a[arr_idx++]; }
//
//NODE* QUEUE; // Queue와 같은 역할
//NODE* q;
//NODE* sorted;
//
//NODE* h = NULL; // head
//NODE* pre_h = NULL;
//NODE* tail = NULL; // tail
//
//bool dir = 0;
//
//void init(int track_size, int head) {
//	dir = 0;
//	arr_idx = 0;
//	QUEUE = NULL;
//	tail = NULL;
//
//	NODE* newNode = myalloc();
//	newNode->isDel = 1; // 단순 방향을 위한 용도.
//	newNode->track = head;
//
//	QUEUE = newNode; // 내가 사용하던 linked list와는 다른 방향으로.
//	q = newNode;
//	// q->queue = newNode // 젤 앞대가리는 QUEUE임.
//
//	newNode->next = NULL;
//	newNode->prev = NULL;
//	sorted = newNode;
//
//	pre_h = h;
//	h = newNode;
//}
//
//void request(int track) {
//	//printf("%d\n", track);
//	NODE* newNode = myalloc();
//	newNode->track = track;
//	
//	q->queue = newNode;
//	q = newNode;
//
//	for (NODE* p = sorted; p != NULL; p = p->prev)
//	{
//		if (p->track > newNode->track)
//		{
//			if (p->next == NULL)
//			{
//				newNode->next = NULL;
//				newNode->prev = p;
//
//				p->next = newNode;
//				sorted = newNode;
//				break;
//			}
//			else
//			{
//				NODE* temp = p->next;
//				temp->prev = newNode;
//
//				newNode->next = temp;
//				newNode->prev = p;
//
//				p->next = newNode;
//				break;
//			}
//		}
//		else
//		{
//			if (p->prev == NULL)
//			{
//				p->prev = newNode;
//
//				newNode->next = p;
//				newNode->prev = NULL;
//				break;
//			}
//			else
//			{
//				continue;
//			}
//		}
//	}
//
//	if (tail == NULL || tail->track < newNode->track)
//		tail = newNode;
//}
//
//int fcfs() {	
//	while (QUEUE && QUEUE->isDel) { QUEUE = QUEUE->queue; }
//	
//	pre_h = h;
//	h = QUEUE;
//
//	int track_no = QUEUE->track;
//
//	QUEUE->isDel = 1;
//	QUEUE = QUEUE->queue;
//
//	return track_no;
//}
//
//int sstf() {
//	int track_no = -1;	// TO DO : Need to be changed
//
//	NODE* temp1;
//	NODE* temp2;
//	temp1 = h->next;
//	temp2 = h->prev;
//	while (temp1 && temp1->isDel) { temp1 = temp1->next; }
//	while (temp2 && temp2->isDel) { temp2 = temp2->prev; }
//	
//	int t1 = -200001;
//	int t2 = 300001;
//	if (temp1) { t1 = temp1->track; }
//	if (temp2) { t2 = temp2->track; }
//	if ((h->track - t1) > (t2 - h->track))
//	{
//		temp1 = temp2;
//	}
//	temp1->isDel = 1;
//	pre_h = h;
//	h = temp1;
//	track_no = temp1->track;
//
//	return track_no;
//}
//
//int look() {
//	int track_no = -1;	// TO DO : Need to be changed
//
//	NODE* temp1;
//	if (dir == 0)
//	{
//		temp1 = h->next;
//		while (temp1 && temp1->isDel) { temp1 = temp1->next; }
//		if (temp1 == NULL)
//		{
//			NODE* temp2;
//			temp2 = h->prev;
//			while (temp2 && temp2->isDel) { temp2 = temp2->prev; }
//			temp1 = temp2;
//			dir = 1;
//		}
//	}
//	else // idr == 1
//	{
//		temp1 = h->prev;
//		while (temp1 && temp1->isDel) { temp1 = temp1->prev; }
//		if (temp1 == NULL)
//		{
//			NODE* temp2;
//			temp2 = h->next;
//			while (temp2 && temp2->isDel) { temp2 = temp2->next; }
//			temp1 = temp2;
//			dir = 0;
//		}
//	}
//
//	temp1->isDel = 1;
//	pre_h = h;
//	h = temp1;
//	track_no = temp1->track;
//
//	return track_no;
//}
//
//int clook() {
//	int track_no = -1;	// TO DO : Need to be changed
//
//	NODE* temp1;
//	temp1 = h->next;
//	while (temp1 && temp1->isDel) { temp1 = temp1->next; }
//	if (temp1 == NULL)
//	{
//		NODE* temp2;
//		temp2 = tail;
//		while (temp2 && temp2->isDel) { temp2 = temp2->next; } // 왼쪽
//		temp1 = temp2;
//	}
//	temp1->isDel = 1;
//	pre_h = h;
//	h = temp1;
//	track_no = temp1->track;
//
//	return track_no;
//}