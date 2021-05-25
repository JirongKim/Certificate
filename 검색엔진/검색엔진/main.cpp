#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include<stdio.h>
#include<string.h>

#define MAXPAGES 50000
#define MAXWORDS 10000
#define MAXBLOCK 10000

#define REMOVERATE 5
#define BLOCKRATE 10
#define RECOVERRATE 15
#define ADDRATE 60


extern void init(int n);
extern void addPage(int mId, int m, char word[][11]);
extern void removePage(int mId);
extern void blockWord(char word[]);
extern void recoverWord(char word[]);
extern int search(char word[2][11], int mode);

static int blockWords[MAXBLOCK];
static char dummy1[11];
static bool pageChk[MAXPAGES];
static char dummy2[11];
static bool blockChk[MAXWORDS];
static char dummy3[11];
static int pageN, blockN, blockCnt;

static int seed = 3;
static int N, M, addN;
static char words[MAXWORDS][11];

static int pseudo_rand(void)
{
	seed = seed * 431345 + 2531999;
	return seed & 0x7FFFFFFF;
}

static void makeWords() {
	int len;

	for (register int i = 0; i < MAXWORDS; ++i) {
		len = pseudo_rand() % 6 + 4;

		for (register int j = 0; j < len; ++j) {
			words[i][j] = pseudo_rand() % 26 + 'a';
		}
		words[i][len] = 0;
	}
}

static void addFunc() {
	char temp[4][11] = { 0 };
	int wordsN = pseudo_rand() % 4 + 1;

	for (int i = 0; i < wordsN; ++i) {

		bool sameChk = false;
		int randIdx = pseudo_rand() % (N < MAXWORDS ? N : MAXWORDS);

		for (int j = 0; j < i && !sameChk; ++j) {
			if (!strcmp(words[randIdx], temp[j])) {
				sameChk = true;
			}
		}

		if (!sameChk) {
			strcpy(temp[i], words[randIdx]);
		}
		else {
			--i;
		}
	}

	addPage(pageN, wordsN, temp);

	pageChk[pageN] = true;
	++pageN;
}

static void removeFunc() {
	int randIdx = pseudo_rand() % pageN;

	while (!pageChk[randIdx]) {
		++randIdx;

		if (randIdx == pageN) {
			randIdx = 0;
		}
	}

	removePage(randIdx);

	pageChk[randIdx] = false;
}

static void blockFunc() {
	char temp[11] = { 0 };
	int randIdx = pseudo_rand() % (N < MAXWORDS ? N : MAXWORDS);

	while (blockChk[randIdx]) {
		++randIdx;

		if (randIdx == (N < MAXWORDS ? N : MAXWORDS)) {
			randIdx = 0;
		}
	}

	strcpy(temp, words[randIdx]);

	blockWord(temp);

	blockChk[randIdx] = true;
	blockWords[blockN] = randIdx;
	++blockN;
	++blockCnt;
}

static void recoverFunc() {
	char temp[11] = { 0 };
	int randIdx = pseudo_rand() % blockN;

	while (blockWords[randIdx] == -1) {
		++randIdx;

		if (randIdx == blockN) {
			randIdx = 0;
		}
	}

	strcpy(temp, words[blockWords[randIdx]]);

	recoverWord(temp);

	blockChk[blockWords[randIdx]] = false;
	blockWords[randIdx] = -1;
	--blockCnt;
}

static int searchFunc() {
	char temp[2][11] = { 0 };
	int mode = pseudo_rand() % 3;
	int randIdx = pseudo_rand() % (N < MAXWORDS ? N : MAXWORDS);

	while (blockChk[randIdx]) {
		++randIdx;

		if (randIdx == (N < MAXWORDS ? N : MAXWORDS)) {
			randIdx = 0;
		}
	}

	strcpy(temp[0], words[randIdx]);

	if (mode >= 1) {
		do {
			randIdx = pseudo_rand() % (N < MAXWORDS ? N : MAXWORDS);

			while (blockChk[randIdx]) {
				++randIdx;

				if (randIdx == (N < MAXWORDS ? N : MAXWORDS)) {
					randIdx = 0;
				}
			}
		} while (!strcmp(words[randIdx], temp[0]));

		strcpy(temp[1], words[randIdx]);
	}

	return search(temp, mode);
}

static int run(int test_case) {

	int accepted = 0;

	pageN = blockN = blockCnt = 0;

	for (int i = 0; i < addN; ++i) {
		addFunc();
	}

	for (int i = 0; i < M; ++i) {

		int command = pseudo_rand() % 100;

		if (command < REMOVERATE) {
			removeFunc();
		}
		else if (command < BLOCKRATE) {
			blockFunc();
		}
		else if (command < RECOVERRATE && blockCnt > 0) {
			recoverFunc();
		}
		else if (pageN == 0 || (command < ADDRATE && pageN < N)) {
			addFunc();
		}
		else {
			int correct;
			int answer = searchFunc();

			if (test_case <= 5) {
				scanf("%d", &correct);

				if (correct == answer) {
					++accepted;
				}
			}
			else {
				accepted += answer;
			}
		}
	}

	for (int i = 0; i < blockN; ++i) {
		if (blockWords[i] != -1) {
			blockChk[blockWords[i]] = false;
		}
	}

	return accepted;
}

int main(void) {

	int correct, totalScore = 0;
	int T;

	freopen("sample_input.txt", "r", stdin);

	scanf("%d", &T);

	setbuf(stdout, NULL);

	makeWords();

	for (int test_case = 1; test_case <= T; ++test_case) {

		scanf("%d%d%d%d%d", &seed, &N, &M, &addN, &correct);

		init(N);

		if (run(test_case) == correct) {
			printf("#%d 100\n", test_case);
			totalScore += 100;
		}
		else {
			printf("#%d 0\n", test_case);
		}
	}

	printf("Total Score = %d\n", totalScore / T);

	return 0;
}
