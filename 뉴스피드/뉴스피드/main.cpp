#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define ADDNEWS (100)
#define ERASENEWS (200)
#define READNEWS (300)
#define CHANGESECTION (400)
#define GETLIST (500)

extern void init();
extern void addNews(int mSection, int mNewsId);
extern void eraseNews(int mNewsId);
extern void readNews(int mUserId, int mNewsId);
extern void changeSection(int mNewsId, int mSection);
extern int getList(int mUserId, int mList[]);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int run()
{
	int N;
	int cmd;
	int mSection, mUserId;
	int mNewsId;
	int res[10];

	init();

	int retVal = 1;

	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &cmd);
		switch (cmd)
		{
		case ADDNEWS:
			scanf("%d %d", &mSection, &mNewsId);
			addNews(mSection, mNewsId);
			break;
		case ERASENEWS:
			scanf("%d", &mNewsId);
			eraseNews(mNewsId);
			break;
		case READNEWS:
			scanf("%d %d", &mUserId, &mNewsId);
			readNews(mUserId, mNewsId);
			break;
		case CHANGESECTION:
			scanf("%d %d", &mNewsId, &mSection);
			changeSection(mNewsId, mSection);
			break;
		case GETLIST:
			scanf("%d", &mUserId);
			int num = getList(mUserId, res);
			int numans;
			scanf("%d", &numans);
			if (numans != num)
				retVal = 0;

			for (int j = 0; j < numans; j++) {
				int ans;
				scanf("%d", &ans);
				if (ans != res[j])
					retVal = 0;
			}
			break;
		}
	}

	return retVal;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;

	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}
