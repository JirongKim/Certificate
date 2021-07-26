#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <time.h>

time_t addTime = 0;
time_t moveTime = 0;
time_t infectTime = 0;
time_t recoverTime = 0;
time_t removeTime = 0;
time_t start = 0;

enum COMMAND {
	CMD_ADD = 1,
	CMD_MOVE,
	CMD_INFECT,
	CMD_RECOVER,
	CMD_REMOVE
};

extern void init();
extern int cmdAdd(int, int, int);
extern int cmdMove(int, int);
extern int cmdInfect(int);
extern int cmdRecover(int);
extern int cmdRemove(int);

static int run(int score) {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int cmd;
		int ret = 0;
		scanf("%d", &cmd);

		switch (cmd) {
		case CMD_ADD: {
			start = clock();
			int id, pid, fileSize;
			scanf("%d%d%d", &id, &pid, &fileSize);
			ret = cmdAdd(id, pid, fileSize);
			addTime += (clock() - start);
			break;
		}
		case CMD_MOVE: {
			start = clock();
			int id, pid;
			scanf("%d%d", &id, &pid);
			ret = cmdMove(id, pid);
			moveTime += (clock() - start);
			break;
		}
		case CMD_INFECT: {
			start = clock();
			int id;
			scanf("%d", &id);
			ret = cmdInfect(id);
			infectTime += (clock() - start);
			break;
		}
		case CMD_RECOVER: {
			start = clock();
			int id;
			scanf("%d", &id);
			ret = cmdRecover(id);
			recoverTime += (clock() - start);
			break;
		}
		case CMD_REMOVE: {
			start = clock();
			int id;
			scanf("%d", &id);
			ret = cmdRemove(id);
			removeTime += (clock() - start);
			break;
		}
		}

		int checkSum;
		scanf("%d", &checkSum);
		if (ret != checkSum)
			score = 0;
	}
	return score;
}

int main() {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int TC, score;
	scanf("%d%d", &TC, &score);
	for (int t = 1; t <= TC; t++) {
		init();
		int ret = run(score);
		printf("#%d %d\n", t, ret);
	}

	printf("addTime : %d\n", addTime);
	printf("moveTime : %d\n", moveTime);
	printf("infectTime : %d\n", infectTime);
	printf("recoverTime : %d\n", recoverTime);
	printf("removeTime : %d\n", removeTime);
	printf("total : %d\n", addTime + moveTime + infectTime + recoverTime + removeTime);
	return 0;
}
