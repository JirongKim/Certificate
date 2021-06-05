//#define R register
//#define MAX(x,y) ((x) > (y) ? (x) : (y))
//#define MIN(x,y) ((x) > (y) ? (y) : (x))
//
//int tc;
//int chk[1001][1001];
//int cellChk[2400];
//int undoType;
//typedef enum CMD { NONE, MERGE, SPLIT, UNDO };
//struct CELL {
//    int sr, sc, er, ec;
//    int idx;
//}cells[2400];
//int ncell;
//int mergedCells[2400];
//int mlen;
//
//void init(int r, int c)
//{
//    mlen = 0;
//    ncell = 0;
//    tc += 2400;
//    undoType = NONE;
//}
//
//void getRect(int r, int c, int rect[])
//{
//    for (R int i = 0; i < mlen; ++i) {
//        CELL& cc = cells[mergedCells[i]];
//        if (cc.sr <= r && r <= cc.er && cc.sc <= c && c <= cc.ec) {
//            rect[0] = cc.sr;
//            rect[1] = cc.sc;
//            rect[2] = cc.er;
//            rect[3] = cc.ec;
//            return;
//        }
//    }
//    rect[0] = r;
//    rect[1] = c;
//    rect[2] = r;
//    rect[3] = c;
//}
//
//int newInfo[2400];
//int infolen;
//int stored;
//int mergeCells(int cnt, int rs[], int cs[], int rect[])
//{
//    tc++;
//    R int msr = 0x3f3f3f3f;
//    R int mer = -1;
//    R int msc = 0x3f3f3f3f;
//    R int mec = -1;
//    R int mergeCnt = 0;
//    int r, c;
//    int id[15];
//    int ilen = 0;
//    for (R int k = 0; k < cnt; ++k) {
//        int sr, sc, er, ec;
//        r = rs[k], c = cs[k];
//        R int i = 0;
//        for (; i < mlen; ++i) {
//            int cid = mergedCells[i];
//            R CELL& cc = cells[cid];
//            if (cc.sr <= r && r <= cc.er && cc.sc <= c && c <= cc.ec) {
//                if (cellChk[cid] == tc) return 0;
//                cellChk[cid] = tc;
//                mergeCnt += (cc.er + 1 - cc.sr) * (cc.ec + 1 - cc.sc);
//                er = cc.er;
//                sr = cc.sr;
//                sc = cc.sc;
//                ec = cc.ec;
//                id[ilen++] = cid;
//                break;
//            }
//        }
//        if (i == mlen) {
//            if (chk[r][c] == tc) return 0;
//            sr = er = r;
//            sc = ec = c;
//            chk[r][c] = tc;
//            mergeCnt++;
//        }
//        msr = MIN(sr, msr);
//        mer = MAX(mer, er);
//        msc = MIN(sc, msc);
//        mec = MAX(ec, mec);
//    }
//    if (mergeCnt != (mer + 1 - msr) * (mec + 1 - msc)) return 0;
//    CELL& cell = cells[ncell];
//    stored = ncell;
//    cells[ncell].idx = mlen;
//    undoType = MERGE;
//    mergedCells[mlen++] = ncell++;
//
//    for (R int i = 0; i < ilen; ++i) {
//        int cid = newInfo[i] = id[i];
//        int p = cells[cid].idx;
//        mergedCells[p] = mergedCells[--mlen];
//        cells[mergedCells[p]].idx = p;
//    }
//    infolen = ilen;
//    cell.sr = rect[0] = msr;
//    cell.sc = rect[1] = msc;
//    cell.er = rect[2] = mer;
//    cell.ec = rect[3] = mec;
//    return 1;
//}
//
//int splitCell(int r, int c, int rect[])
//{
//    R int i = 0, cid;
//    for (; i < mlen; ++i) {
//        cid = mergedCells[i];
//        R CELL& cc = cells[cid];
//        if (cc.sr <= r && r <= cc.er && cc.sc <= c && c <= cc.ec) break;
//    }
//    if (i == mlen) return 0;
//    infolen = 0;
//    stored = cid;
//    R CELL& cc = cells[cid];
//    int p = cc.idx;
//    mergedCells[p] = mergedCells[--mlen];
//    cells[mergedCells[p]].idx = p;
//
//    rect[0] = cc.sr;
//    rect[1] = cc.sc;
//    rect[2] = cc.er;
//    rect[3] = cc.ec;
//    undoType = SPLIT;
//    return 1;
//}
//
//void undo()
//{
//    int p, cid;
//    if (undoType == NONE) return;
//    if (undoType == MERGE) {
//        CELL& c = cells[stored];
//        p = c.idx;
//        mergedCells[p] = mergedCells[--mlen];
//        cells[mergedCells[p]].idx = p;
//
//        for (R int i = 0; i < infolen; ++i) {
//            cid = newInfo[i];
//            CELL& nc = cells[cid];
//            nc.idx = mlen;
//
//            mergedCells[mlen++] = cid;
//        }
//        undoType = SPLIT;
//    }
//    else {
//        CELL& c = cells[stored];
//        c.idx = mlen;
//        mergedCells[mlen++] = stored;
//
//        for (R int i = 0; i < infolen; ++i) {
//            CELL& dc = cells[newInfo[i]];
//            p = dc.idx;
//            mergedCells[p] = mergedCells[--mlen];
//            cells[mergedCells[p]].idx = p;
//        }
//        undoType = MERGE;
//    }
//}
//
//int checkRectangle(int r1, int c1, int r2, int c2)
//{
//    for (R int i = 0; i < mlen; ++i) {
//        R CELL& cur = cells[mergedCells[i]];
//        int sr = MAX(cur.sr, r1);
//        int er = MIN(cur.er, r2);
//        int sc = MAX(cur.sc, c1);
//        int ec = MIN(cur.ec, c2);
//        if (er < sr || ec < sc) continue;
//        int s1 = (er + 1 - sr) * (ec + 1 - sc);
//        if (s1 && s1 != (cur.er + 1 - cur.sr) * (cur.ec + 1 - cur.sc)) return 1;
//    }
//    return 0;
//}