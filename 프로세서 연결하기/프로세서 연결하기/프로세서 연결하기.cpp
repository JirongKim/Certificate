#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int arr_idx = 0;

struct NODE
{
	int x;
	int y;
	int num;
	int able[4];
	NODE* prev;
} a[10000];

NODE* myalloc(void)
{
	return &a[arr_idx++];
}

int main(void)
{
	int test_case;
	int T;
	setbuf(stdout, NULL);
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int arr[12][12];
		int max_cell;
		scanf("%d", &max_cell);

		for (int i = 0; i < max_cell; i++)
		{
			for (int j = 0; j < max_cell; j++)
			{
				scanf("%d", &arr[i][j]);
			}
		}

		NODE* p;
		NODE* pList = NULL;

		arr_idx = 0;

		for (int i = 1; i < max_cell - 1; i++)
		{
			for (int j = 1; j < max_cell - 1; j++)
			{
				if (arr[i][j] == 1)
				{
					p = myalloc();
					p->x = i;
					p->y = j;
					p->num = 4;
					p->able[0] = 0;
					p->able[1] = 0;
					p->able[2] = 0;
					p->able[3] = 0;

					int temp = i - 1;
					while (temp != -1)
					{
						if (arr[temp][j] != 0)
						{
							p->able[0] = 0;
							p->num--;
							break;
						}
						p->able[0]++; // ��
						temp--;
					}

					temp = i + 1;
					while (temp != max_cell)
					{
						if (arr[temp][j] != 0)
						{
							p->able[1] = 0;
							p->num--;
							break;
						}
						p->able[1]++; // ��
						temp++;
					}

					temp = j - 1;
					while (temp != -1)
					{
						if (arr[i][temp] != 0)
						{
							p->able[2] = 0;
							p->num--;
							break;
						}
						p->able[2]++; // ��
						temp--;
					}

					temp = j + 1;
					while (temp != max_cell)
					{
						if (arr[i][temp] != 0)
						{
							p->able[3] = 0;
							p->num--;
							break;
						}
						p->able[3]++; // ��
						temp++;
					}

					p->prev = pList;
					pList = p;
				}
			}
		}

		for (int idx = 1; idx <= 4; idx++)
		{
			for (NODE* pp = pList; pp != NULL; pp = pp->prev)
			{
				if (pp->num == idx)
				{
					// ���� �� Ŭ ��
					// ���� �� Ŭ ��
					// ���� �� Ŭ ��
					// ���� �� Ŭ ��
					continue;
				}
			}
		}
	}
	return 0; //��������� �ݵ�� 0�� �����ؾ� �մϴ�.
}