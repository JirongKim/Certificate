#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT			1
#define CMD_OPENACCOUNT		2
#define CMD_CLOSEACCOUNT	3
#define CMD_SENDBYNUMBER	4
#define CMD_SENDBYNAME		5
#define CMD_SENDBONUS		6

#define MAX_NAME_LEN (4+1)


extern void init();
extern void openAccount(int mTime, char mName[MAX_NAME_LEN], char mGroup[MAX_NAME_LEN], int mNumber, int mAsset);
extern int closeAccount(int mTime, int mNumber);
extern int sendByNumber(int mTime, int mNumber, int mReceiveNumber, int mValue);
extern int sendByName(int mTime, int mNumber, char mReceiveName[MAX_NAME_LEN], int mValue);
extern void sendBonus(int mTime, char mGroup[MAX_NAME_LEN], int mValue);

static bool run()
{
	int Q;
	int cmd, mNumber, mAsset, mReceiveNumber, mValue;
	char mName[MAX_NAME_LEN], mReceiveName[MAX_NAME_LEN], mGroup[MAX_NAME_LEN];

	int ret = 0;
	int ans = 0;
	scanf("%d", &Q);
	bool okay = false;

	for (int mTime = 0; mTime < Q; ++mTime)
	{
		scanf("%d", &cmd);

		switch (cmd)
		{
		case CMD_INIT:
			init();
			okay = true;
			break;
		case CMD_OPENACCOUNT:
			scanf("%s %s %d %d", mName, mGroup, &mNumber, &mAsset);
			if (okay)
				openAccount(mTime, mName, mGroup, mNumber, mAsset);
			break;
		case CMD_CLOSEACCOUNT:
			scanf("%d", &mNumber);
			if (okay)
				ret = closeAccount(mTime, mNumber);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CMD_SENDBYNUMBER:
			scanf("%d %d %d", &mNumber, &mReceiveNumber, &mValue);
			if (okay)
				ret = sendByNumber(mTime, mNumber, mReceiveNumber, mValue);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CMD_SENDBYNAME:
			scanf("%d %s %d", &mNumber, mReceiveName, &mValue);
			if (okay)
				ret = sendByName(mTime, mNumber, mReceiveName, mValue);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CMD_SENDBONUS:
			scanf("%s %d", mGroup, &mValue);
			if (okay)
				sendBonus(mTime, mGroup, mValue);
			break;
		}
	}
	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	return 0;
}
