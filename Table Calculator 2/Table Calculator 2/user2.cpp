#include <stdio.h>

#define MAXC 26
#define MAXR 99

#define NULL 0

struct NODE
{
	char isFunc;
	int val;
	int sr, sc;
	int er, ec;
} table[MAXR + 1][MAXC + 1];

int mR, mC;

void init(int C, int R)
{
	for (int i = 1; i <= R; i++)
	{
		for (int j = 1; j <= C; j++)
		{
			table[i][j].isFunc = NULL;
			table[i][j].val = 0;
		}
	}
	mR = R;
	mC = C;
}

void getRC(int row, int col, char input[])
{
	int idx;
	table[row][col].sr = input[4] - 'A' + 1;
	if (input[6] != ',')
	{
		table[row][col].sc = (input[5] - '1' + 1) * 10 + (input[6] - '1' + 1);
		idx = 8;
	}
	else
	{
		table[row][col].sc = input[5] - '1' + 1;
		idx = 7;
	}

	table[row][col].er = input[idx] - 'A' + 1;
	if (input[idx + 2] != ')')
	{
		table[row][col].ec = (input[idx + 1] - '1' + 1) * 10 + (input[idx + 2] - '1' + 1);
	}
	else
	{
		table[row][col].ec = input[idx + 1] - '1' + 1;
	}
	return;
}

void set(int col, int row, char input[]) {
	if (input[0] == '-' || (input[0] >= '0' && input[0] <= '9'))
	{
		int idx = 0;
		if (input[idx] == '-') { table[row][col].val = (input[++idx] - '1' + 1) * -1; }
		else { table[row][col].val = input[idx] - '1' + 1; }

		idx++;
		for (int i = idx; input[i] != NULL; i++)
		{
			table[row][col].val = table[row][col].val * 10 + (input[i] - '1' + 1);
		}
		printf("R : %d, C : %d, Val : %d\n", row, col, table[row][col].val);
	}
	else
	{
		//함수
		table[row][col].isFunc = input[2];
		getRC(row, col, input);
	}
}

int dfs(int r, int c)
{
	int sr = table[r][c].sr;
	int sc = table[r][c].sc;
	int er = table[r][c].er;
	int ec = table[r][c].ec;

	if (table[r][c].isFunc == 'D')
	{
		return dfs(sr, sc) + dfs(er, ec);
	}
	else if (table[r][c].isFunc == 'B')
	{
		return dfs(sr, sc) - dfs(er, ec);
	}
	else if (table[r][c].isFunc == 'L')
	{
		return dfs(sr, sc) * dfs(er, ec);
	}
	else if (table[r][c].isFunc == 'V')
	{
		return dfs(sr, sc) / dfs(er, ec);
	}
	else if (table[r][c].isFunc == 'X')
	{
		int max = -10e9;
		if (sr == er) // 세로일 때
		{
			for (int i = sc; i <= ec; i++)
			{
				int temp = dfs(sr, i);
				if (temp > max)
				{
					max = temp;
				}
			}
		}
		else // 가로일 대
		{
			for (int i = sr; i <= er; i++)
			{
				int temp = dfs(i, sc);
				if (temp > max)
				{
					max = temp;
				}
			}
		}
		return max;
	}
	else if (table[r][c].isFunc == 'N')
	{
		int min = 10e9;
		if (sr == er) // 세로일 때
		{
			for (int i = sc; i <= ec; i++)
			{
				int temp = dfs(sr, i);
				if (temp < min)
				{
					min = temp;
				}
			}
		}
		else // 가로일 대
		{
			for (int i = sr; i <= er; i++)
			{
				int temp = dfs(i, sc);
				if (temp < min)
				{
					min = temp;
				}
			}
		}
		return min;
	}
	else if (table[r][c].isFunc == 'M')
	{
		int sum = 0;
		if (sr == er) // 세로일 때
		{
			for (int i = sc; i <= ec; i++)
			{
				sum += dfs(sr, i);
			}
		}
		else // 가로일 대
		{
			for (int i = sr; i <= er; i++)
			{
				sum += dfs(i, sc);
			}
		}
		return sum;
	}
	else
	{
		return table[r][c].val;
	}
}

void update(int value[MAXR][MAXC]) {
	for (int i = 1; i <= mR; i++)
	{
		for (int j = 1; j <= mC; j++)
		{
			value[i - 1][j - 1] = dfs(i, j);
			printf("%d ", value[i - 1][j - 1]);
		}
		printf("\n");
	}
}