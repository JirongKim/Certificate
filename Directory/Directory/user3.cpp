#include <stdio.h>

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define NULL 0

struct DIR
{
	int name;
	int num;
	DIR* parent;
	DIR* child;
	DIR* prev;
} dir[50000];

int arr_idx = 0;
DIR* myalloc(void)
{
	dir[arr_idx].name = dir[arr_idx].num = 0;
	return &dir[arr_idx++];
}

DIR* findPath(char* path, int adder)
{
	int sp = 1;
	DIR* cur = &dir[0];

	while (1)
	{
		cur->num += adder;
		if (path[sp] == '\0')
		{
			break;
		}

		int n = 0;
		for (; path[sp] != '/'; sp++)
		{
			n = n << 5;
			n = n + (path[sp] - 'A' + 1);
		}

		for (DIR* p = cur->child; p != NULL; p = p->prev)
		{
 			if (p->name == n)
			{
				cur = p;
				sp++;
				break;
			}
		}
	}
	return cur;
}

void addDir(DIR* cur, char* name)
{
	int n = 0;
	for (int i = 0; name[i] != '\0'; i++)
	{
		n = n << 5;
		n = n + (name[i] - 'A' + 1);
	}

	DIR* newDir = myalloc();
	newDir->name = n;
	newDir->parent = cur;

	newDir->prev = cur->child;
	cur->child = newDir;
}

void disCountNum(DIR* cur, int adder)
{
	if (cur->name == 0) { return; }
	cur->num -= adder;
	disCountNum(cur->parent, adder);
}

void dirDelete(DIR* par, DIR* chi)
{
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
		}
	}
}

void copyDir(DIR* srcDir, DIR* dstDir)
{
		if (srcDir == NULL) { return; }
		for (DIR* p = srcDir; p != NULL; p = p->prev)
		{
			DIR* newDir = myalloc();
			newDir->name = p->name;
			newDir->num = p->num;

			newDir->parent = dstDir;
			newDir->prev = dstDir;
			dstDir->child = newDir;
			copyDir(newDir, p->child);
		}
}

void init(int n) {
	arr_idx = 0;
	DIR* initial = myalloc();
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	DIR* curDir = findPath(path, 1);
	addDir(curDir, name);
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	DIR* curDir = findPath(path, 0);
	curDir->child = NULL;
	disCountNum(curDir->parent, -(curDir->num + 1));
	dirDelete(curDir->parent, curDir);
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	DIR* srcDir = findPath(srcPath, 0);
	DIR* dstDir = findPath(dstPath, srcDir->num + 1);
	copyDir(srcDir, dstDir);
	printf("hi");
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	DIR* srcDir = findPath(srcPath, 0);
	DIR* dstDir = findPath(dstPath, srcDir->num + 1);
	disCo
		
		untNum(srcDir->parent, -(srcDir->num + 1));
	srcDir->prev = dstDir->child;
	dstDir->child = srcDir;

	srcDir->parent = dstDir;
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	DIR* curDir = findPath(path, 0);
	return curDir->num;
}