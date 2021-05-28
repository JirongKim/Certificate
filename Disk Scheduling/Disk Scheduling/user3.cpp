//#include <stdio.h>
//
//#define NULL 0
//#define nullptr 0
//const int MAX = 100001;
//#define SCALE 10
//#define KEY(track) (track/SCALE)
//
//struct NODE
//{
//	int t;
//	NODE* next;
//} a[MAX];
//int arr_idx = 0;
//NODE* myalloc(void) { return &a[arr_idx++]; }
//
//NODE* ht[MAX / SCALE + 1];
//
//int h;
//int q[MAX];
//int front, rear;
//int TS;
//
//bool isDeleted[MAX];
//bool dir;
//
//NODE* add(int track)
//{
//	NODE* n = myalloc();
//	n->t = track;
//
//	if (ht[KEY(track)] == NULL)
//	{
//		n->next = ht[KEY(track)];
//		ht[KEY(track)] = n;
//	}
//	else
//	{
//		NODE* prev = NULL;
//		for (NODE* p = ht[KEY(track)]; p != NULL; prev = p, p = p->next)
//		{
//			if (n->t > p->t)
//			{
//				if (prev == NULL)
//				{
//					n->next = p;
//					ht[KEY(track)] = n;
//					break;
//				}
//				else
//				{
//					// 4¹ø
//					prev->next = n;
//					n->next = p;
//					break;
//				}
//			}
//			else
//			{
//				if (p->next == NULL)
//				{
//					//2¹ø
//					p->next = n;
//					n->next = NULL;
//					break;
//				}
//				else
//				{
//					continue;
//				}
//			}
//		}
//	}
//
//	/*for (NODE* pp = ht[KEY(track)]; pp != NULL; pp = pp->next)
//	{
//		printf("%d ", pp->t);
//	}
//	printf("\n");*/
//	return n;
//}
//
//int findLeft(int track)
//{
//	NODE max;
//	max.t = -1;
//
//	int k = 0;
//
//	while (1)
//	{
//		for (NODE* p = ht[KEY(track) - k]; p != NULL; p = p->next)
//		{
//			if (p->t > max.t && p->t < track && isDeleted[p->t] == 0)
//			{
//				max = *p;
//			}
//		}
//		if (max.t != -1) { return max.t; }
//
//		k++;
//		if(KEY(track) - k < 0)
//		{
//			return -1;
//		}
//	}
//}
//
//int findRight(int track)
//{
//	NODE min;
//	min.t = MAX;
//
//	int k = 0;
//
//	while (1)
//	{
//		for (NODE* p = ht[KEY(track) + k]; p != NULL; p = p->next)
//		{
//			if (p->t < min.t && p->t > track && isDeleted[p->t] == 0)
//			{
//				min = *p;
//			}
//		}
//		if (min.t != MAX) { return min.t; }
//
//		k++;
//		if (KEY(track) + k == KEY(TS) + 1)
//		{
//			return -1;
//		}
//	}
//}
//
//void init(int track_size, int head) {
//	dir = 0;
//	arr_idx = 0;
//	front = rear = 0;
//
//	for (int i = 0; i <= KEY(track_size); i++)
//	{
//		ht[i] = nullptr;
//	}
//	
//	for (int i = 0; i <= track_size; i++)
//	{
//		isDeleted[i] = 0;
//	}
//	
//	TS = track_size;
//	add(head);
//	isDeleted[head] = 1;
//	h = head;
//}
//
//void request(int track) {
//	add(track);
//	isDeleted[track] = 0;
//	q[rear++] = track;
//}
//
//int fcfs() {
//	int track_no = -1;	// TO DO : Need to be changed
//
//	while (isDeleted[q[front]]) { front++; }
//	track_no = q[front];
//	isDeleted[q[front]] = 1;
//	h = track_no;
//	front++;
//
//	return track_no;
//}
//
//int sstf() {
//	int l = findLeft(h);
//	int r = findRight(h);
//
//	if (l == -1) { l = r; }
//	else if (r == -1) { l; }
//	else if ((h - l) > (r - h)) { l = r; }
//
//	h = l;
//	isDeleted[l] = 1;
//
//	return l;
//}
//
//int look() {
//	int lr = 0;
//	if (dir == 0) //left
//	{
//		lr = findLeft(h);
//		if (lr == -1)
//		{
//			lr = findRight(h);
//			dir = 1;
//		}
//	}
//	else
//	{
//		lr = findRight(h);
//		if (lr == -1)
//		{
//			lr = findLeft(h);
//			dir = 0;
//		}
//	}
//	h = lr;
//	isDeleted[lr] = 1;
//
//	return lr;
//}
//
//int clook() {
//	int l = findLeft(h);
//
//	if (l == -1)
//	{
//		l = findLeft(TS);
//	}
//
//	h = l;
//	isDeleted[l] = 1;
//
//	return l;
//}