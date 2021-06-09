//int n[11][50001];
//int section[50001];
//int ncnt;
//int delcnt;
//int del[50001];
//
//struct USER
//{
//    int userid;
//    int prefer;
//}u[100001];
//
//void init()
//{
//    ncnt = 0;
//    delcnt = 0;
//    for (register int i = 0; i <= 100000; i++)
//    {
//        u[i].prefer = 10;
//    }
//    for (register int i = 0; i <= 10; i++)
//    {
//        n[i][0] = 0;
//    }
//}
//
//void addNews(int mSection, int mNewsId)
//{
//    ncnt++;
//    for (register int i = 0; i <= 10; i++)
//    {
//        n[i][mNewsId] = 0;
//    }
//    n[mSection][mNewsId] = 10;
//    section[mNewsId] = mSection;
//    del[mNewsId] = 0;
//}
//
//void eraseNews(int mNewsId)
//{
//    delcnt++;
//    del[mNewsId] = 1;
//}
//
//void readNews(int mUserId, int mNewsId)
//{
//    u[mUserId].prefer = section[mNewsId];
//    for (register int i = 0; i <= 10; i++)
//    {
//        n[i][mNewsId]++;
//    }
//}
//
//void changeSection(int mNewsId, int mSection)
//{
//    n[section[mNewsId]][mNewsId] -= 10;
//    section[mNewsId] = mSection;
//    n[mSection][mNewsId] += 10;
//}
//
//int getList(int mUserId, int mList[])
//{
//    register int* my_n;
//    for (register int i = 0; i < 10; i++)
//        mList[i] = 0;
//    my_n = n[u[mUserId].prefer];
//
//    register int end = 10;
//
//    if (end > ncnt - delcnt)
//        end = ncnt - delcnt;
//
//    for (register int i = 1; i <= ncnt; i++)
//    {
//        if (del[i])continue;
//        if (my_n[mList[9]] > my_n[i])continue;
//
//        register int j;
//        for (j = 9; j > 0; j--)
//        {
//            if (my_n[mList[j - 1]] > my_n[i])break;
//            mList[j] = mList[j - 1];
//        }
//        mList[j] = i;
//    }
//    return end;
//}