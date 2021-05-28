//const int MAX = 100001;
//
//bool table[MAX];
//bool isDeleted[MAX];
//int q[MAX];
//int front, rear;
//
//bool dir;
//int h;
//int trackSize;
//
//void init(int track_size, int head) {
//	front = rear = 0;
//	for (int i = 0; i < track_size; i++)
//	{
//		table[i] = 0;
//		isDeleted[i] = 0;
//	}
//	dir = 0;
//	h = head;
//	isDeleted[h] = 1;
//	q[rear++] = head;
//	trackSize = track_size;
//}
//
//void request(int track) {
//	table[track] = 1;
//	isDeleted[track] = 0;
//	q[rear++] = track;
//}
//
//int fcfs() {
//	int track_no = -1;	// TO DO : Need to be changed
//
//	while (isDeleted[q[front]]) { front++; }
//	h = q[front];
//	track_no = q[front];
//	isDeleted[q[front++]] = 1;
//
//	return track_no;
//}
//
//int findLeft(const int h)
//{
//	int l = h - 1;
//	while (1) {
//		if (l == -1) { break; }
//		if (isDeleted[l] == 0 && table[l] == 1)
//		{
//			break;
//		}
//		l--;
//	}
//	return l;
//}
//
//int findRight(const int h)
//{
//	int r = h + 1;
//	while (1) {
//		if (r == MAX) { break; }
//		if (isDeleted[r] == 0 && table[r] == 1)
//		{
//			break;
//		}
//		r++;
//	}
//	return r;
//}
//
//int sstf() {
//	int track_no = -1;	// TO DO : Need to be changed
//
//	int l = findLeft(h);
//	int r = findRight(h);
//
//	if (l == -1) {
//		l = r;
//	}
//	else if ((h - l) > (r - h) && l != -1 && r != MAX) {
//		l = r;
//	}
//
//	track_no = l;
//	isDeleted[l] = 1;
//	h = l;
//
//	return track_no;
//}
//
//int look() {
//	int track_no = -1;	// TO DO : Need to be changed
//
//	int l;
//	if (dir == 0) //left
//	{
//		l = findLeft(h);
//		if (l == -1)
//		{
//			int r = findRight(h);
//			l = r;
//			dir = 1;
//		}
//	}
//	else //right
//	{
//		int r = findRight(h);
//		if (r == MAX)
//		{
//			l = findLeft(h);
//			dir = 0;
//			r = l;
//		}
//		l = r;
//	}
//	track_no = l;
//	isDeleted[l] = 1;
//	h = l;
//
//	return track_no;
//}
//
//int clook() {
//	int track_no = -1;	// TO DO : Need to be changed
//
//	int l = findLeft(h);
//	if (l == -1)
//	{
//		l = findLeft(trackSize);
//	}
//	track_no = l;
//	isDeleted[l] = 1;
//	h = l;
//
//	return track_no;
//}