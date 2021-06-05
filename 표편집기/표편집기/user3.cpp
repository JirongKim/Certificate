#define MAX_RC 1001
#define MNUM 2400
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) > (y) ? (y) : (x))

#define NONE 100
#define MERGE 200
#define SPLIT 300
#define UNDO 400

struct CELL
{
	int sr, er, sc, ec;
	int idx;
} cells[MNUM];
int ncell;

int tc = 0;
int chkM[MNUM];
int chk[MAX_RC][MAX_RC];

int mergedCells[MNUM];
int mlen;

int undoType;

void init(int R, int C)
{
	tc += MNUM;
	ncell = mlen = 0;
	undoType = NONE;
}

void getRect(int r, int c, int rect[])
{
	for (int i = 0; i < mlen; i++)
	{
		CELL t = cells[mergedCells[i]];
		if (t.sr <= r && r <= t.er && t.sc <= c && c <= t.ec)
		{
			rect[0] = t.sr;
			rect[1] = t.sc;
			rect[2] = t.er;
			rect[3] = t.ec;
			return;
		}
	}
	rect[0] = r;
	rect[1] = c;
	rect[2] = r;
	rect[3] = c;
}

int newInfo[MNUM];
int infoLen = 0;
int stored = 0;
int mergeCells(int cnt, int rs[], int cs[], int rect[])
{
	tc++;
	int msr, mer, msc, mec;
	msr = msc = 10e9;
	mer = mec = -1;
	int mergeCnt = 0;
	int id[15];
	int ilen = 0;
	int r, c;

	for (int i = 0; i < cnt; i++)
	{
		r = rs[i];
		c = cs[i];

		int j = 0;
		CELL t;
		for (; j < mlen; j++)
		{
			t = cells[mergedCells[j]];
			if (t.sr <= r && r <= t.er && t.sc <= c && c <= t.ec) //만약 r,c가 Merge 된 Cell이라면?
			{
				if (chkM[mergedCells[j]] == tc) { return 0; }
				chkM[mergedCells[j]] = tc;
				mergeCnt += (t.er - t.sr + 1) * (t.ec - t.sc + 1);
				id[ilen++] = mergedCells[j];
				break;
			}
		}
		if (j == mlen) // r,c가 Merge되지 않은 Cell 이라면?
		{
			if (chk[r][c] == tc) { return 0; }
			chk[r][c] = tc;
			mergeCnt++;
			msr = MIN(msr, r);
			mer = MAX(mer, r);
			msc = MIN(msc, c);
			mec = MAX(mec, c);
			continue;
		}
		msr = MIN(msr, t.sr);
		mer = MAX(mer, t.er);
		msc = MIN(msc, t.sc);
		mec = MAX(mec, t.ec);
	}

	if (mergeCnt != (mer - msr + 1) * (mec - msc + 1)) { return 0; }

	for (int i = 0; i < ilen; i++)
	{
		CELL& t = cells[id[i]];
		mergedCells[t.idx] = mergedCells[--mlen];
		cells[mergedCells[t.idx]].idx = t.idx;
		newInfo[i] = id[i];
	}
	infoLen = ilen;

	stored = ncell;
	CELL& cur = cells[ncell];
	cur.sr = rect[0] = msr;
	cur.sc = rect[1] = msc;
	cur.er = rect[2] = mer;
	cur.ec = rect[3] = mec;
	cur.idx = mlen;
	mergedCells[mlen++] = ncell++;

	undoType = MERGE;

	return 1;
}

int splitCell(int r, int c, int rect[])
{
	int i = 0;
	for (; i < mlen; i++)
	{
		CELL t = cells[mergedCells[i]];
		if (t.sr <= r && r <= t.er && t.sc <= c && c <= t.ec)
		{
			stored = mergedCells[i];
			break;
		}
	}
	if (i == mlen) { return 0; }

	infoLen = 0;

	CELL& t = cells[mergedCells[i]];
	mergedCells[t.idx] = mergedCells[--mlen];
	cells[mergedCells[t.idx]].idx = t.idx;

	rect[0] = t.sr;
	rect[1] = t.sc;
	rect[2] = t.er;
	rect[3] = t.ec;

	undoType = SPLIT;

	return 1;
}

void undo()
{
	if (undoType == NONE) { return; }
	if (undoType == MERGE)
	{
		CELL& t = cells[stored];
		mergedCells[t.idx] = mergedCells[--mlen];
		cells[mergedCells[t.idx]].idx = t.idx;
		
		for (int i = 0; i < infoLen; i++)
		{
			mergedCells[mlen] = newInfo[i];
			cells[newInfo[i]].idx = mlen;
			mlen++;
		}

		undoType = SPLIT;
	}
	else
	{
		for (int i = 0; i < infoLen; i++)
		{
			CELL& t = cells[newInfo[i]];
			mergedCells[t.idx] = mergedCells[--mlen];
			cells[mergedCells[t.idx]].idx = t.idx;
		}

		mergedCells[mlen] = stored;
		cells[stored].idx = mlen;
		mlen++;

		undoType = MERGE;
	}
}

int checkRectangle(int r1, int c1, int r2, int c2)
{
	int msr, mer, msc, mec;
	for (int i = 0; i < mlen; i++)
	{
		CELL& t = cells[mergedCells[i]]; 

		msr = MAX(t.sr, r1);
		mer = MIN(t.er, r2);
		msc = MAX(t.sc, c1);
		mec = MIN(t.ec, c2);
		
		if (msr > mer || msc > mec)
		{
			continue;
		}
		if (t.sr == msr && t.sc == msc && t.er == mer && t.ec == mec) { continue; }
		return 1;
	}
	return 0;
}