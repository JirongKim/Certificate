#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define MAX_DIR (50001 * 3)
#define NULL 0

struct DIR
{
    int name;
    int num_descendant;
    DIR* parent;
    DIR* child;
    DIR* prev;
} dir[MAX_DIR];
int arr_idx = 0;
DIR* myalloc(void) { return &dir[arr_idx++]; }

DIR* ROOT;


void init(int n) {
    for (int i = 0; i < arr_idx; i++)
    {
        dir[i].name = 0;
        dir[i].num_descendant = 0;
        dir[i].parent = NULL;
        dir[i].child = NULL;
        dir[i].prev = NULL;
    }
    arr_idx = 0;
    ROOT = myalloc();
}

int strToint(char* n)
{
    int r = 0;
    for (int i = 0; n[i] != NULL; i++)
    {
        r = r << 5;
        r = r + (n[i] - 'a' + 1);
    }
    return r;
}

DIR* find(char* path)
{
    DIR* cur = ROOT;
    int st = 0;
    int h = 0;
    while (1)
    {
        if (path[st] == '/')
        {
            for (DIR* p = cur->child; p != NULL; p = p->prev)
            {
                if (p->name == h)
                {
                    cur = p;
                    break;
                }
            }
            if (path[st + 1] == '\0')
            {
                break;
            }
            h = 0;
        }
        else
        {
            h = h << 5;
            h = h + (path[st] - 'a' + 1);
        }
        st++;
    }
    return cur;
}

void addChild(DIR* par, DIR* chi)
{
    chi->parent = par;
    chi->prev = par->child;
    par->child = chi;
}

void countDescendant(DIR* cur, int adder)
{
    if (cur == NULL)
    {
        return;
    }
    cur->num_descendant += adder;
    countDescendant(cur->parent, adder);
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
    DIR* parDir = find(path);
    DIR* newDir = myalloc();
    newDir->name = strToint(name);

    addChild(parDir, newDir);
    countDescendant(parDir, 1);
}

void deleteDir(DIR* par, DIR* chi)
{
    if (par == NULL) { return; }
    DIR* temp = NULL;
    for (DIR* p = par->child; p != NULL; temp = p, p = p->prev)
    {
        if (p->name == chi->name)
        {
            if (temp == NULL)
            {
                par->child = p->prev;
            }
            else
            {
                temp->prev = p->prev;
            }
            break;
        }
    }
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
    DIR* curDir = find(path);

    deleteDir(curDir->parent, curDir);
    countDescendant(curDir->parent, -(curDir->num_descendant + 1));
}

void copyDir(DIR* src, DIR* dst)
{
    if (src == NULL)
    {
        return;
    }
    DIR* nDir = myalloc();
    nDir->name = src->name;
    nDir->num_descendant = src->num_descendant;
    addChild(dst, nDir);
    for (DIR* p = src->child; p != NULL; p = p->prev)
    {
        copyDir(p, nDir);
    }
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    DIR* srcDir = find(srcPath);
    DIR* dstDir = find(dstPath);

    copyDir(srcDir, dstDir);
    countDescendant(dstDir, srcDir->num_descendant + 1);
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    DIR* srcDir = find(srcPath);
    DIR* dstDir = find(dstPath);

    deleteDir(srcDir->parent, srcDir);
    countDescendant(srcDir->parent, -(srcDir->num_descendant + 1));

    addChild(dstDir, srcDir);
    countDescendant(dstDir, srcDir->num_descendant + 1);
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
    DIR* curDir = find(path);

    return curDir->num_descendant;
}