//#define MAX_NEWS 50001
//#define MAX_USER 100001
//#define MAX_SEC 10
//#define SCORE(x,y) (x<<16) | (y)
//
//struct NEWS
//{
//	unsigned short id, s, si;
//	unsigned int score;
//	bool isDeleted;
//} news[MAX_NEWS];
//
//unsigned short user[MAX_USER]; //tc 당 100씩 추가 할 것.
//unsigned short sec[MAX_SEC][MAX_NEWS];
//unsigned short snum[MAX_SEC];
//
//int tc = 0;
//
//void init()
//{
//	tc++;
//	for (register int i = 0; i < MAX_SEC; i++)
//	{
//		snum[i] = 0;
//	}
//}
//
//void addNews(int mSection, int mNewsId)
//{
//	news[mNewsId].id = mNewsId;
//	news[mNewsId].isDeleted = 0;
//	news[mNewsId].s = mSection;
//	news[mNewsId].score = SCORE(0, mNewsId);
//
//	sec[mSection][snum[mSection]] = mNewsId;
//	news[mNewsId].si = snum[mSection]++;
//}
//
//void eraseNews(int mNewsId)
//{
//	NEWS& temp = news[mNewsId];
//	temp.isDeleted = 1;
//
//	sec[temp.s][temp.si] = sec[temp.s][--snum[temp.s]];
//	news[sec[temp.s][temp.si]].si = temp.si;
//}
//
//void readNews(int mUserId, int mNewsId)
//{
//	news[mNewsId].score += (1 << 16);
//	user[mUserId] = news[mNewsId].s + (tc * 100);
//}
//
//void changeSection(int mNewsId, int mSection)
//{
//	NEWS& temp = news[mNewsId];
//
//	sec[temp.s][temp.si] = sec[temp.s][--snum[temp.s]];
//	news[sec[temp.s][temp.si]].si = temp.si;
//
//	temp.s = mSection;
//	sec[mSection][snum[mSection]] = mNewsId;
//	news[mNewsId].si = snum[mSection]++;
//}
//
//int getList(int mUserId, int mList[])
//{
//	NEWS list[11];
//	register int lnum = 0;
//	for (register int i = 0; i < 11; i++) { list[i].score = 0; }
//
//	for (register int i = 0; i < MAX_SEC; i++)
//	{
//		for (register int j = 0; j < snum[i]; j++)
//		{
//			register int t = sec[i][j];
//			if (news[t].isDeleted == 1) { continue; }
//
//			NEWS temp;
//			if (news[t].s + (tc * 100) == user[mUserId])
//			{
//				temp.score = news[t].score + (10 << 16);
//			}
//			else
//			{
//				temp.score = news[t].score;
//			}
//			temp.id = news[t].id;
//
//			if (temp.score < list[9].score) { continue; }
//
//			register int k;
//			for (k = 9; k > 0; k--)
//			{
//				if (temp.score <= list[k - 1].score)
//				{
//					if (temp.score == list[k].score && temp.id < list[k].id) { continue; }
//					break;
//				}
//				list[k] = list[k - 1];
//			}
//			list[k] = temp;
//			lnum++;
//			if (lnum == 11)
//			{
//				lnum = 10;
//			}
//		}
//	}
//
//	for (register int i = 0; i < lnum; i++)
//	{
//		mList[i] = list[i].id;
//	}
//
//	return lnum;
//}