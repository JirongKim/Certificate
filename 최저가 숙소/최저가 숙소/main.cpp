#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int M);
extern void add_bnb(int bid, int y, int x, int price, int rating);
extern int reserve(int bid, int cday, int night);
extern int cancel(int bid, int cday);
extern int search(int opt, int y, int x, int cday, int night, int top5_bid[5]);

static int score;
static int result, top5[5];

int main() {
	freopen("eval_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	int tc = 0;
	scanf("%d", &tc);
	for (int t = 1; t <= tc; t++) {
		int map_size;
		scanf("%d", &map_size);
		init(map_size);

		score = 100;

		int i;
		int bid, y, x, price, rating, cday, night, opt;
		int user_res, user_top5[5];

		char cmd = ' ';
		while (cmd != 'E') {
			scanf(" %c", &cmd);
			switch (cmd) {
			case 'B':
				scanf("%d %d %d %d %d %d", &bid, &y, &x, &price, &rating, &result);
				add_bnb(bid, y, x, price, rating);
				break;

			case 'R':
				scanf("%d %d %d", &bid, &cday, &night);
				user_res = reserve(bid, cday, night);

				scanf("%d", &result);
				if (result != user_res)
					score = 0;
				break;

			case 'C':
				scanf("%d %d", &bid, &cday);
				user_res = cancel(bid, cday);

				scanf("%d", &result);
				if (result != user_res)
					score = 0;
				break;

			case 'S':
				scanf("%d %d %d %d %d", &opt, &y, &x, &cday, &night);
				for (i = 0; i < 5; i++) {
					user_top5[i] = 0;
				}
				user_res = search(opt, y, x, cday, night, user_top5);

				scanf("%d", &result);
				for (i = 0; i < result; i++) {
					scanf("%d", top5 + i);
				}
				if (result != user_res)
					score = 0;
				else {
					for (i = 0; i < result; i++)
						if (top5[i] != user_top5[i])
							score = 0;
				}
				break;
			case 'E':
				printf("#%d %d\n", t, score);
			}
		}
	}
	return 0;
}