#include <stdio.h>

#define NULL 0
#define MAX_TABLE 30007
#define hash(id) (id % MAX_TABLE)
#define ROOT 10000
#define R register

struct DIR
{
	int id;
	int num_descendant;
	int virus;
	int fileSize;
	int childNum;
	int isVirus;
	DIR* parent;
	DIR* child;
	DIR* prev;
} dir[10002];

int arr_idx;
DIR* myalloc(void) {
	dir[arr_idx].id = 0;
	dir[arr_idx].num_descendant = 0;
	dir[arr_idx].virus = 0;
	dir[arr_idx].fileSize = 0;
	dir[arr_idx].childNum = 0;
	dir[arr_idx].isVirus = 0;
	dir[arr_idx].parent = NULL;
	dir[arr_idx].child = NULL;
	dir[arr_idx].prev = NULL;
	return &dir[arr_idx++];
}

DIR* dirTable[MAX_TABLE];

int fileCount;
int v;

void init() {
	v = 0;
	arr_idx = 0;
	fileCount = 0;

	for (R int i = 0; i < MAX_TABLE; i++)
	{
		dirTable[i] = NULL;
	}

	R DIR* root = myalloc();
	root->id = ROOT;

	dirTable[ROOT] = root;
}

DIR* findPath(int ID)
{
	R int key = hash(ID);

	while (1)
	{
		if (dirTable[key]->id == ID)
		{
			break;
		}
		key++;
		key = hash(key);
	}

	return dirTable[key];
}

DIR* makePath(int ID)
{
	R int key = hash(ID);

	while (1)
	{
		if (dirTable[key] == NULL)
		{
			R DIR* newDir = myalloc();
			newDir->id = ID;
			dirTable[key] = newDir;
			break;
		}
		key++;
		key = hash(key);
	}

	return dirTable[key];
}

void addChild(DIR* par, DIR* ch)
{
	ch->parent = par;
	ch->prev = par->child;
	par->child = ch;
	if (ch->fileSize != 0) { par->childNum++; }
	return;
}

void countDescendant(DIR* cur, int adder)
{
	cur->num_descendant += adder;
	if (cur->id == ROOT) { return; }

	countDescendant(cur->parent, adder);
}

int cmdAdd(int newID, int pID, int fileSize) {
	if (fileSize != 0) { fileCount++; }

	R DIR* newDir = makePath(newID);
	R DIR* pDir = findPath(pID);
	newDir->fileSize = fileSize;

	addChild(pDir, newDir);
	countDescendant(newDir, fileSize);
	return pDir->num_descendant;
}

void deleteDir(DIR* par, DIR* chi)
{
	R DIR* temp = NULL;
	for (R DIR* p = par->child; p != NULL; temp = p, p = p->prev)
	{
		if (p->id == chi->id)
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
	par->childNum--;
	chi->parent = NULL;
	countDescendant(par, -chi->num_descendant);
}

int cmdMove(int tID, int pID) {
	R DIR* tDir = findPath(tID);
	R DIR* pDir = findPath(pID);

	deleteDir(tDir->parent, tDir);
	addChild(pDir, tDir);
	countDescendant(pDir, tDir->num_descendant);
	return pDir->num_descendant;
}

int cnt;
void getFileCount(DIR* tDir)
{
	if (tDir->fileSize != 0)
	{
		cnt++;
	}
	for (R DIR* p = tDir->child; p != NULL; p = p->prev)
	{
		getFileCount(p);
	}
}

void loopInfect(DIR* tDir)
{
	if (tDir->fileSize == 0)
	{
		for (R DIR* p = tDir->child; p != NULL; p = p->prev)
		{
			loopInfect(p);
		}
	}
	tDir->virus += v * tDir->childNum;
	return;
}

int cmdInfect(int tID) {
	if (fileCount == 0) { return 0; }
	if (fileCount) { v = (dir[0].num_descendant / fileCount); }

	DIR* tDir = findPath(tID);
	loopInfect(tDir);
	//1. 각 파일에 접근하면, 하위 파일(전부)이 몇개인지 알아야함
	// 현재는 바로 하위파일의 개수만 알고있음.
	//2. 그렇게 하위파일의 개수를 전부 알 수 있으면,
	// virus를 걸릴 때 각각 하위파일 X v 만큼만 virus를 더하면 됨.
	// virus만 따로 더하려면 countDescendant를 바꿔야할듯.
	countDescendant(tDir->parent, tDir->virus);
	return tDir->num_descendant;
}

int loopRecover(DIR* tDir)
{
	if (tDir->fileSize != 0)
	{
		tDir->isVirus = 0;
		countDescendant(tDir, -tDir->virus);
		tDir->virus = 0;
	}
	else
	{
		for (R DIR* p = tDir->child; p != NULL; p = p->prev)
		{
			loopRecover(p);
		}
	}

	return tDir->num_descendant;
}

int cmdRecover(int tID) {
	R DIR* tDir = findPath(tID);

	loopRecover(tDir);

	return tDir->num_descendant;
}

int cmdRemove(int tID) {
	if (tID == ROOT)
	{
		dir[0].id = 0;
		dir[0].num_descendant = 0;
		dir[0].virus = 0;
		dir[0].fileSize = 0;
		dir[0].childNum = 0;
		dir[0].isVirus = 0;
		dir[0].parent = NULL;
		dir[0].child = NULL;
		dir[0].prev = NULL;
		return 0;
	}
	R DIR* tDir = findPath(tID);

	deleteDir(tDir->parent, tDir);
	cnt = 0;
	getFileCount(tDir);

	fileCount -= cnt;

	return tDir->num_descendant;
}