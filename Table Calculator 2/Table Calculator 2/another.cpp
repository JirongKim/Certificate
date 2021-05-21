#define MAXR 99
#define MAXC 26
#define INV 1e8
#define MAX_CELL MAXR*MAXC*2
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define MAX 4
#define MIN 5
#define SUM 6
#define CNS 7
#define rint register int
#define fi(i,a,b) for(rint i=a;i<b;++i)

int mC, mR, mCell, nVirt;
bool firstUp;
int cell_v[MAX_CELL], cell_f[MAX_CELL], cell_t[MAX_CELL], cell_p[MAX_CELL];
char cell_tp[MAX_CELL], cell_s[MAX_CELL];
int changed[MAX_CELL], mChanged;

void init(int C, int R) {
    mC = C; mR = R;
    nVirt = mCell = mC * mR;
    firstUp = true;
    fi(i, 0, mCell) {
        cell_v[i] = 0;
        cell_tp[i] = CNS;
        cell_p[i] = -1;
    }
    mChanged = 0;
}

void set(int col, int row, char input[]) {
    rint cid = (row - 1) * mC + col - 1;
    if (cell_tp[cid] != CNS) {
        if (cell_tp[cid] < MAX) {
            cell_p[cell_f[cid]] = cell_p[cell_t[cid]] = -1;
        }
        else {
            for (rint c = cell_f[cid]; c <= cell_t[cid]; c += cell_s[cid])
                cell_p[c] = -1;
        }
    }
    rint u = cid;
    while (u != -1 && cell_v[u] != INV) {
        changed[mChanged++] = u;
        cell_v[u] = INV;
        u = cell_p[u];
    }

    register char* p = input;
    if (*p <= '9') {
        bool neg = false;
        if (*p == '-') neg = true, ++p;
        rint v = 0;
        while (*p) v = v * 10 + *p++ - '0';
        if (neg) v = -v;
        cell_v[cid] = v;
        cell_tp[cid] = CNS;
        return;
    }

    p += 4;
    register int op1, op2;
    register char c;
    c = *p++ - 'A';
    if (p[1] != ',') {
        op1 = (p[0] * 10 + p[1] - '0' * 11 - 1) * mC + c; p += 3;
    }
    else {
        op1 = (p[0] - '0' - 1) * mC + c; p += 2;
    }
    c = *p++ - 'A';
    if (p[1] != ')') {
        op2 = (p[0] * 10 + p[1] - '0' * 11 - 1) * mC + c; p += 3;
    }
    else {
        op2 = (p[0] - '0' - 1) * mC + c; p += 2;
    }
    cell_f[cid] = op1; cell_t[cid] = op2;

    switch (input[2]) {
    case 'D':
        cell_tp[cid] = ADD; break;
    case 'B':
        cell_tp[cid] = SUB; break;
    case 'L':
        cell_tp[cid] = MUL; break;
    case 'V':
        cell_tp[cid] = DIV; break;
    case 'X':
        cell_tp[cid] = MAX; cell_s[cid] = (op2 - op1 < mC) ? 1 : mC; break;
    case 'N':
        cell_tp[cid] = MIN; cell_s[cid] = (op2 - op1 < mC) ? 1 : mC; break;
    case 'M':
        cell_tp[cid] = SUM; cell_s[cid] = (op2 - op1 < mC) ? 1 : mC; break;
    }
    if (cell_tp[cid] < MAX) {
        cell_p[op1] = cell_p[op2] = cid;
    }
    else {
        rint s = cell_s[cid];
        rint steps = (op2 - op1) / s;
        if (steps < 10) {
            for (rint c = op1; c <= op2; c += s) cell_p[c] = cid;
        }
        else {
            rint m = op1 + (steps / 2) * s;
            cell_tp[nVirt] = cell_tp[cid];
            cell_p[nVirt] = cid;
            cell_v[nVirt] = INV;
            cell_s[nVirt] = cell_s[cid];
            cell_f[nVirt] = op1;
            cell_t[nVirt] = m;
            for (rint c = cell_f[nVirt]; c <= cell_t[nVirt]; c += s)
                cell_p[c] = nVirt;
            ++nVirt;

            cell_tp[nVirt] = cell_tp[cid];
            cell_p[nVirt] = cid;
            cell_v[nVirt] = INV;
            cell_s[nVirt] = cell_s[cid];
            cell_f[nVirt] = m + s;
            cell_t[nVirt] = op2;
            for (rint c = cell_f[nVirt]; c <= cell_t[nVirt]; c += s)
                cell_p[c] = nVirt;
            ++nVirt;
            cell_f[cid] = nVirt - 2;
            cell_t[cid] = nVirt - 1;
            cell_s[cid] = 1;
        }
    }
}

int calc(int cid) {
    if (cell_v[cid] != INV)
        return cell_v[cid];
    rint v, t, ff, tt, ss;
    ff = cell_f[cid];
    tt = cell_t[cid];
    ss = cell_s[cid];
    switch (cell_tp[cid]) {
    case ADD:
        return (cell_v[cid] = (calc(cell_f[cid]) + calc(cell_t[cid])));
    case SUB:
        return (cell_v[cid] = (calc(cell_f[cid]) - calc(cell_t[cid])));
    case MUL:
        return (cell_v[cid] = (calc(cell_f[cid]) * calc(cell_t[cid])));
    case DIV:
        return (cell_v[cid] = (calc(cell_f[cid]) / calc(cell_t[cid])));
    case MAX:
        v = -INV;
        for (rint c = ff; c <= tt; c += ss) {
            t = calc(c);
            if (t > v)
                v = t;
        }
        return (cell_v[cid] = v);
    case MIN: v = INV;
        for (rint c = ff; c <= tt; c += ss) {
            t = calc(c);
            if (t < v)
                v = t;
        }
        return (cell_v[cid] = v);
    case SUM: v = 0;
        for (rint c = ff; c <= tt; c += ss)
            v += calc(c);
        return (cell_v[cid] = v);
    }
}

void update(int value[MAXR][MAXC]) {
    if (firstUp) {
        firstUp = false;
        fi(i, 0, mR)
            fi(j, 0, mC)
            value[i][j] = 0;
    }
    fi(it, 0, mChanged) {
        rint cid = changed[it];
        if (cid >= mCell)
            calc(cid);
        else
            value[cid / mC][cid % mC] = calc(cid);
    }
    mChanged = 0;
}