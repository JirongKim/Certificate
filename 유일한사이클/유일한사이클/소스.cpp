#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define nullptr 0

struct NODE
{
	int y;
	struct NODE* prev;
} a[10000];

int arr_idx = 0;
struct NODE* myalloc(void) {
	return &a[arr_idx++];
}

struct NODE* p;
struct NODE* hashList[1010];

int main(void)
{
	int cnt[1001];
	int test_case;
	int T;

	scanf("%d", &T);

	for (test_case = 0; test_case < T; test_case++)
	{
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			hashList[i] = nullptr;
			cnt[i] = 0;
		}

		for (int i = 1; i <= n; i++)
		{
			int x, y;
			scanf("%d %d", &x, &y);
			cnt[x]++;
			cnt[y]++;
			p = myalloc();
			p->y = y;
			p->prev = hashList[x];
			hashList[x] = p;
		}

		for (int i = 1; i <= n; i++)
		{
			if (cnt[i] == 1)
			{
				for (NODE* pp = hashList[i]; pp != NULL; pp = pp->prev)
				{
					cnt[pp->y]--;
				}
				cnt[i]--;
				i = 1; 
			}
		}

		int count = 0;
		for (int i = 1; i <= n; i++)
		{
			if (cnt[i] > 1) { count++; }
		}

		printf("#%d %d\n", test_case + 1, count);
	}
	return 0;
}