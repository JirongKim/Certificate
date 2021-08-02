#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define NULL 0

struct DIR {
	int name;
	int num_descendant;
	DIR* prev;
	DIR* child;
	DIR* parent;
} dir[50000];
int arr_idx = 0;
DIR* myalloc(void) { return &dir[arr_idx++]; }

DIR* find(char* path)
{
	DIR* cur = &dir[0];
	int st = 0;
	int strToint = 0;
	while (1)
	{
		if (path[st] == '/')
		{
			for (DIR* p = cur->child; p != NULL; p = p->prev)
			{
				if (p->name == strToint)
				{
					cur = p;
					break;
				}
			}
			if (path[st + 1] == '\0')
			{
				break;
			}
			st++;
			strToint = 0;
		}
		strToint = strToint << 5;
		strToint = strToint + (path[st] - 'a' + 1);
		st++;
	}
	return cur;
}

int strToint(char* name)
{
	int n = 0;
	for (int i = 0; name[i] != NULL; i++)
	{
		n = n << 5;
		n = n + (name[i] - 'a' + 1);
	}
	return n;
}

void countDesendant(DIR* cur, int adder)
{
	if (cur == NULL)
	{
		return;
	}
	while (1)
	{
		cur->num_descendant += adder;
		if (cur->parent == NULL)
		{
			break;
		}
		cur = cur->parent;
	}
}

void addChild(DIR* par, DIR* ch)
{
	ch->parent = par;
	ch->prev = par->child;
	par->child = ch;
}

void init(int n) {
	for (int i = 0; i < arr_idx; i++)
	{
		dir[i].name = 0;
		dir[i].num_descendant = 0;
		dir[i].child = NULL;
		dir[i].parent = NULL;
		dir[i].prev = NULL;
	}
	arr_idx = 0;
	DIR* root = myalloc();
	root->name = 0;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	DIR* parPath = find(path);
	DIR* newDir = myalloc();

	newDir->name = strToint(name);
	addChild(parPath, newDir);
	countDesendant(parPath, 1);
}

void deleteDir(DIR* par, DIR* ch)
{
	if (par == NULL)
	{
		return;
	}
	DIR* temp = NULL;
	for (DIR* p = par->child; p != NULL; temp = p, p = p->prev)
	{
		if (p->name == ch->name)
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
	ch->parent = NULL;
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	DIR* curPath = find(path);
	DIR* parPath = curPath->parent;

	countDesendant(parPath, -(curPath->num_descendant + 1));
	deleteDir(parPath, curPath);
}

void copyDir(DIR* sPath, DIR* dPath)
{
	DIR* nDir = myalloc();
	nDir->name = sPath->name;
	nDir->num_descendant = sPath->num_descendant;
	addChild(dPath, nDir);

	for (DIR* p = sPath->child; p != NULL; p = p->prev)
	{
		copyDir(p, nDir);
	}
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	DIR* sPath = find(srcPath);
	DIR* dPath = find(dstPath);
	countDesendant(dPath, sPath->num_descendant + 1);

	copyDir(sPath, dPath);
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	DIR* sPath = find(srcPath);
	DIR* dPath = find(dstPath);
	countDesendant(dPath, sPath->num_descendant + 1);
	countDesendant(sPath->parent, -(sPath->num_descendant + 1));

	deleteDir(sPath->parent, sPath);
	addChild(dPath, sPath);
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	DIR* nPath = find(path);
	return nPath->num_descendant;
}
