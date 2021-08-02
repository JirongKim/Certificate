////#include <stdio.h>
//
//#define NAME_MAXLEN 6
//#define PATH_MAXLEN 1999
//#define NULL 0
//#define rint register int
//#define RDIR register DIR
//
//struct DIR
//{
//	int name;
//	int num;
//	DIR* parent;
//	DIR* child;
//	DIR* prev;
//} dir[50000];
//
//int arr_idx = 0;
//DIR* myalloc(void)
//{
//	dir[arr_idx].name = 0;
//	dir[arr_idx].num = 0;
//	dir[arr_idx].parent = NULL;
//	dir[arr_idx].child = NULL;
//	dir[arr_idx].prev = NULL;
//	return &dir[arr_idx++];
//}
//
//DIR* findPath(char* path, int adder)
//{
//	//printf("%s\n", path);
//	rint sp = 1;
//	RDIR* cur = &dir[0];
//
//	while (1)
//	{
//		cur->num += adder;
//		if (path[sp] == '\0')
//		{
//			break;
//		}
//
//		rint n = 0;
//		for (; path[sp] != '/'; sp++)
//		{
//			n = n << 5;
//			n = n + (path[sp] - 'a' + 1);
//		}
//
//		for (RDIR* p = cur->child; p != NULL; p = p->prev)
//		{
//			if (p->name == n)
//			{
//				cur = p;
//				sp++;
//				break;
//			}
//		}
//	}
//	return cur;
//}
//
//void addDir(DIR* par, DIR* chi)
//{
//	chi->parent = par;
//	chi->prev = par->child;
//	par->child = chi;
//}
//
//void disCountNum(DIR* cur, int adder)
//{
//	cur->num += adder;
//	if (cur->name == 0) { return; }
//	disCountNum(cur->parent, adder);
//}
//
//void dirDelete(DIR* par, DIR* chi)
//{
//	RDIR* temp = NULL;
//	for (RDIR* p = par->child; p != NULL; temp = p, p = p->prev)
//	{
//		if (p->name == chi->name)
//		{
//			if (temp == NULL)
//			{
//				par->child = p->prev;
//			}
//			else
//			{
//				temp->prev = p->prev;
//			}
//			break;
//		}
//	}
//}
//
//void copyDir(DIR* srcDir, DIR* dstDir)
//{
//		if (srcDir == NULL) { return; }
//		for (RDIR* p = srcDir; p != NULL; p = p->prev)
//		{
//			RDIR* newDir = myalloc();
//			newDir->name = p->name;
//			newDir->num = p->num;
//
//			addDir(dstDir, newDir);
//			copyDir(p->child, dstDir->child);
//		}
//}
//
//void init(int n) {
//	arr_idx = 0;
//	myalloc();
//}
//
//void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
//	//printf("M");
//	RDIR* curDir = findPath(path, 1);
//	RDIR* newDir = myalloc();
//
//	rint n = 0;
//	for (rint i = 0; name[i] != '\0'; i++)
//	{
//		n = n << 5;
//		n = n + ((name[i] - 'a') + 1);
//	} 
//	newDir->name = n;
//
//	addDir(curDir, newDir);
//	//printf("");
//}
//
//void cmd_rm(char path[PATH_MAXLEN + 1]) {
//	//printf("R");
//	RDIR* curDir = findPath(path, 0);
//	disCountNum(curDir->parent, -(curDir->num + 1));
//	dirDelete(curDir->parent, curDir);
//}
//
//void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
//	//printf("C");
//	RDIR* srcDir = findPath(srcPath, 0);
//	RDIR* dstDir = findPath(dstPath, srcDir->num + 1);
//
//	RDIR* newDir = myalloc();
//	newDir->name = srcDir->name;
//	newDir->num = srcDir->num;
//	addDir(dstDir, newDir);
//
//	copyDir(srcDir->child, newDir);
//}
//
//void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
//	//printf("MO");
//	RDIR* srcDir = findPath(srcPath, 0);
//	RDIR* dstDir = findPath(dstPath, srcDir->num + 1);
//	
//	disCountNum(srcDir->parent, -(srcDir->num + 1));
//	dirDelete(srcDir->parent, srcDir);
//	addDir(dstDir, srcDir);
//	//printf("");
//}
//
//int cmd_find(char path[PATH_MAXLEN + 1]) {
//	//printf("F");
//	RDIR* curDir = findPath(path, 0);
//	//printf("");
//	return curDir->num;
//}