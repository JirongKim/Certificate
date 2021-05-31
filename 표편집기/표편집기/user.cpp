#define NULL 0
#define nullptr 0
#define MAX_RC 1001

struct CELL
{
	short R, C;
	short eR, eC;
	CELL* head;
} tb[MAX_RC][MAX_RC];

bool CHECKDIV(int r, int c) //r,c의 Cell이 개별적인(병합되어있지 않은 Cell인지 판단하는 함수)
{
	if (tb[r][c].head->eR == tb[r][c].head->R)
	{
		if (tb[r][c].head->eC == tb[r][c].head->C)
		{
			return 1;
		}
	}
	return 0;
}

void merge(short minR, short minC, short maxR, short maxC)
{
	for (int i = minR; i <= maxR; i++)
	{
		for (int j = minC; j <= maxC; j++)
		{
			tb[i][j].eR = tb[i][j].R;
			tb[i][j].eC = tb[i][j].C;
			tb[i][j].head = &tb[minR][minC];
		}
	}
	tb[minR][minC].eR = maxR;
	tb[minR][minC].eC = maxC;
	tb[minR][minC].head = NULL;
}

void init(int R, int C)
{
	for (int i = 0; i <= R; i++)
	{
		for (int j = 0; j <= C; j++)
		{
			tb[i][j].eC = tb[i][j].C = i;
			tb[i][j].eR = tb[i][j].R = j;
			tb[i][j].head = NULL;
		}
	}
}

void getRect(int r, int c, int rect[])
{
	if (tb[r][c].head == NULL) { rect[0] = tb[r][c].R; rect[1] = tb[r][c].C; rect[2] = tb[r][c].eR; rect[3] = tb[r][c].eC; return; }
	if (CHECKDIV(r, c)) { rect[0] = tb[r][c].R; rect[1] = tb[r][c].C; rect[2] = tb[r][c].eR; rect[3] = tb[r][c].eC; return; }

	rect[0] = tb[r][c].head->R;
	rect[1] = tb[r][c].head->C;
	rect[2] = tb[r][c].head->eR;
	rect[3] = tb[r][c].head->eC;
	return;
}

int mergeCells(int cnt, int rs[], int cs[], int rect[])
{
	short minR, minC;
	short maxR, maxC;
	minR = minC = MAX_RC;
	maxR = maxC = -1;

	for (int i = 0; i < cnt; i++)
	{
		if (minR > rs[i]) { minR = rs[i]; }
		if (maxR < rs[i]) { maxR = rs[i]; }
		if (minC > cs[i]) { minC = cs[i]; }
		if (maxC < cs[i]) { maxC = cs[i]; }
	}

	if (!checkRectangle(minR, minC, maxR, maxC))
	{
		merge(minR, minC, maxR, maxC);

		rect[0] = minR;
		rect[1] = minC;
		rect[2] = maxR;
		rect[3] = maxC;
		return 1;
	}
	return 0;
}

int splitCell(int r, int c, int rect[])
{
	if (tb[r][c].head == NULL) { return 0; }
	if (CHECKDIV(r, c)) { return 0; }

	return 1;
}

void undo()
{
}

int checkRectangle(int r1, int c1, int r2, int c2)
{
	return 0;
}
