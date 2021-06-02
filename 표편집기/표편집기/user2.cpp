//#define NULL 0
//#define nullptr 0
//#define MAX_RC 1001
//
//struct CELL
//{
//	short R, C;
//	short eR, eC;
//	CELL* head;
//} tb[MAX_RC][MAX_RC];
//
//CELL ud[MAX_RC][MAX_RC];
//int lR, leR, lC, leC;
//
//void rangeClear(short minR, short minC, short maxR, short maxC, bool isClear) // isClear가 1이면 clear만.
//{
//	for (register int i = minR; i <= maxR; i++)
//	{
//		for (register int j = minC; j <= maxC; j++)
//		{
//			ud[i][j] = tb[i][j];
//			tb[i][j].eR = tb[i][j].R;
//			tb[i][j].eC = tb[i][j].C;
//			if (!isClear)
//			{
//				tb[i][j].head = &tb[minR][minC];
//			}
//			else
//			{
//				tb[i][j].head = NULL;
//			}
//		}
//	}
//	if (!isClear)
//	{
//		//ud[minR][minC] = tb[minR][minC];
//		tb[minR][minC].eR = maxR;
//		tb[minR][minC].eC = maxC;
//		tb[minR][minC].head = NULL;
//	}
//	lR = minR;
//	leR = maxR;
//	lC = minC;
//	leC = maxC;
//	return;
//}
//
//void init(int R, int C)
//{
//	lR = leR = lC = leC = 0;
//	for (register int i = 0; i <= R; i++)
//	{
//		for (register int j = 0; j <= C; j++)
//		{
//			tb[i][j].eR = tb[i][j].R = i;
//			tb[i][j].eC = tb[i][j].C = j;
//			tb[i][j].head = NULL;
//		}
//	}
//}
//
//void getRect(int r, int c, int rect[])
//{
//	if (tb[r][c].head == NULL) { rect[0] = tb[r][c].R; rect[1] = tb[r][c].C; rect[2] = tb[r][c].eR; rect[3] = tb[r][c].eC; return; }
//
//	rect[0] = tb[r][c].head->R;
//	rect[1] = tb[r][c].head->C;
//	rect[2] = tb[r][c].head->eR;
//	rect[3] = tb[r][c].head->eC;
//	return;
//}
//
//int mergeCells(int cnt, int rs[], int cs[], int rect[])
//{
//	short minR, minC;
//	short maxR, maxC;
//	minR = minC = MAX_RC;
//	maxR = maxC = -1;
//
//	//for (register int i = 0; i < cnt; i++)
//	//{
//	//	register int r = rs[i];
//	//	register int c = cs[i];
//	//	if (tb[r][c].head != NULL)
//	//	{
//	//		if (!CHECKDIV(r, c)) // 병합이 되어있으면?
//	//		{
//	//			if (minR > tb[r][c].head->R) { minR = tb[r][c].head->R; }
//	//			if (maxR < tb[r][c].head->eR) { maxR = tb[r][c].head->eR; }
//	//			if (minC > tb[r][c].head->C) { minC = tb[r][c].head->C; }
//	//			if (maxC < tb[r][c].head->eC) { maxC = tb[r][c].head->eC; }
//	//			continue;
//	//		}
//	//	}
//	//	if (minR > tb[r][c].R) { minR = tb[r][c].R; }
//	//	if (maxR < tb[r][c].eR) { maxR = tb[r][c].eR; }
//	//	if (minC > tb[r][c].C) { minC = tb[r][c].C; }
//	//	if (maxC < tb[r][c].eC) { maxC = tb[r][c].eC; }
//	//}
//
//	bool temp[MAX_RC][MAX_RC] = { 0, };
//	/*for (register int i = 0; i < MAX_RC; i++)
//	{
//		for (register int j = 0; j < MAX_RC; j++)
//		{
//			temp[i][j] = 0;
//		}
//	}*/
//
//	for (int i = 0; i < cnt; i++)
//	{
//		register int r = rs[i];
//		register int c = cs[i];
//		if (tb[r][c].head != NULL)
//		{
//			if (minR > tb[r][c].head->R) { minR = tb[r][c].head->R; }
//			if (maxR < tb[r][c].head->eR) { maxR = tb[r][c].head->eR; }
//			if (minC > tb[r][c].head->C) { minC = tb[r][c].head->C; }
//			if (maxC < tb[r][c].head->eC) { maxC = tb[r][c].head->eC; }
//
//			for (register int k = tb[r][c].head->R; k <= tb[r][c].head->eR; k++)
//			{
//				for (register int l = tb[r][c].head->C; l <= tb[r][c].head->eC; l++)
//				{
//					temp[k][l] = !temp[k][l];
//				}
//			}
//			continue;
//		}
//		for (register int k = tb[r][c].R; k <= tb[r][c].eR; k++)
//		{
//			for (register int l = tb[r][c].C; l <= tb[r][c].eC; l++)
//			{
//				temp[k][l] = !temp[k][l];
//			}
//		}
//		if (minR > tb[r][c].R) { minR = tb[r][c].R; }
//		if (maxR < tb[r][c].eR) { maxR = tb[r][c].eR; }
//		if (minC > tb[r][c].C) { minC = tb[r][c].C; }
//		if (maxC < tb[r][c].eC) { maxC = tb[r][c].eC; }
//	}
//
//	int flag = 0;
//	for (register int i = minR; i <= maxR; i++)
//	{
//		for (register int j = minC; j <= maxC; j++)
//		{
//			if (temp[i][j] == 0) { flag = 1; break; }
//		}
//	}
//
//	if (flag == 1) { return 0; } // 4각형이 아닌것.
//
//	rangeClear(minR, minC, maxR, maxC, 0);
//
//	rect[0] = minR;
//	rect[1] = minC;
//	rect[2] = maxR;
//	rect[3] = maxC;
//	return 1;
//}
//
//int splitCell(int r, int c, int rect[])
//{
//	if (tb[r][c].R == tb[r][c].eR && tb[r][c].C == tb[r][c].eC)
//	{
//		if (tb[r][c].head == NULL) { return 0; }
//		else
//		{
//			rect[0] = tb[r][c].head->R;
//			rect[1] = tb[r][c].head->C;
//			rect[2] = tb[r][c].head->eR;
//			rect[3] = tb[r][c].head->eC;
//			rangeClear(tb[r][c].head->R, tb[r][c].head->C, tb[r][c].head->eR, tb[r][c].head->eC, 1);
//			return 1;
//		}
//	}
//	else
//	{
//		rect[0] = tb[r][c].R;
//		rect[1] = tb[r][c].C;
//		rect[2] = tb[r][c].eR;
//		rect[3] = tb[r][c].eC;
//		rangeClear(tb[r][c].R, tb[r][c].C, tb[r][c].eR, tb[r][c].eC, 1);
//		return 1;
//	}
//	return 0;
//}
//
//void undo()
//{
//	for (register int i = lR; i <= leR; i++)
//	{
//		for (register int j = lC; j <= leC; j++)
//		{
//			CELL temp = ud[i][j];
//			ud[i][j] = tb[i][j];
//			tb[i][j] = temp;
//		}
//	}
//}
//
//int checkRectangle(int r1, int c1, int r2, int c2)
//{
//	for (register int i = r1; i <= r2; i++)
//	{
//		for (register int j = c1; j <= c2; j++)
//		{
//			if (tb[i][j].R != tb[i][j].eR || tb[i][j].C != tb[i][j].eC)
//			{
//				if (r1 > tb[i][j].eR || tb[i][j].eR > r2) { return 1; }
//				if (c1 > tb[i][j].eC || tb[i][j].eC > c2) { return 1; }
//			}
//			if (tb[i][j].head != NULL) {
//				if (r1 > tb[i][j].head->R || tb[i][j].head->R > r2) { return 1; }
//				if (r1 > tb[i][j].head->eR || tb[i][j].head->eR > r2) { return 1; }
//				if (c1 > tb[i][j].head->C || tb[i][j].head->C > c2) { return 1; }
//				if (c1 > tb[i][j].head->eC || tb[i][j].head->eC > c2) { return 1; }
//			}
//		}
//	}
//	return 0;
//}
