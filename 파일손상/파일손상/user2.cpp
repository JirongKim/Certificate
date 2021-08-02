//#include <stdio.h>
//
//#define NULL 0
//#define MAX_TABLE 30007
//#define hash(id) (id % MAX_TABLE)
//#define ROOT 10000
//#define R register
//
//struct DIR
//{
//	int id;
//	int num_descendant;
//	int virus;
//	int fileSize;
//	int childNum;
//	DIR* parent;
//	DIR* child;
//	DIR* prev;
//} dir[10002];
//
//int arr_idx;
//DIR* myalloc(void) {
//	dir[arr_idx].id = 0;
//	dir[arr_idx].num_descendant = 0;
//	dir[arr_idx].virus = 0;
//	dir[arr_idx].fileSize = 0;
//	dir[arr_idx].childNum = 0;
//	dir[arr_idx].parent = NULL;
//	dir[arr_idx].child = NULL;
//	dir[arr_idx].prev = NULL;
//	return &dir[arr_idx++];
//}
//
//DIR* dirTable[MAX_TABLE];
//
//int v;
//
//void init() {
//	v = 0;
//	arr_idx = 0;
//
//	for (R int i = 0; i < MAX_TABLE; i++)
//	{
//		dirTable[i] = NULL;
//	}
//
//	R DIR* root = myalloc();
//	root->id = ROOT;
//
//	dirTable[ROOT] = root;
//}
//
//DIR* findPath(int ID)
//{
//	R int key = hash(ID);
//
//	while (1)
//	{
//		if (dirTable[key]->id == ID)
//		{
//			break;
//		}
//		key++;
//		key = hash(key);
//	}
//
//	return dirTable[key];
//}
//
//DIR* makePath(int ID)
//{
//	R int key = hash(ID);
//
//	while (1)
//	{
//		if (dirTable[key] == NULL)
//		{
//			R DIR* newDir = myalloc();
//			newDir->id = ID;
//			dirTable[key] = newDir;
//			break;
//		}
//		key++;
//		key = hash(key);
//	}
//
//	return dirTable[key];
//}
//
//void addChild(DIR* par, DIR* ch)
//{
//	ch->parent = par;
//	ch->prev = par->child;
//	par->child = ch;
//	return;
//}
//
//void countDescendant(DIR* cur, int adder, int childAdder, int virusAdder)
//{
//	if (cur == NULL) { return; }
//	if (adder) { cur->num_descendant += adder; }
//	if (childAdder) { cur->childNum += childAdder; }
//	if (virusAdder) { cur->virus += virusAdder; }
//	if (cur->id == ROOT) { return; }
//
//	countDescendant(cur->parent, adder, childAdder, virusAdder);
//}
//
//int cmdAdd(int newID, int pID, int fileSize) {
//	R DIR* newDir = makePath(newID);
//	R DIR* pDir = findPath(pID);
//	newDir->fileSize = fileSize;
//
//	addChild(pDir, newDir);
//	countDescendant(newDir, fileSize, fileSize ? 1 : 0, 0);
//	return pDir->num_descendant;
//}
//
//void deleteDir(DIR* par, DIR* chi)
//{
//	R DIR* temp = NULL;
//	for (R DIR* p = par->child; p != NULL; temp = p, p = p->prev)
//	{
//		if (p->id == chi->id)
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
//	chi->parent = NULL;
//	countDescendant(par, -chi->num_descendant, -chi->childNum, -chi->virus);
//}
//
//int cmdMove(int tID, int pID) {
//	R DIR* tDir = findPath(tID);
//	R DIR* pDir = findPath(pID);
//
//	deleteDir(tDir->parent, tDir);
//	addChild(pDir, tDir);
//	countDescendant(pDir, tDir->num_descendant, tDir->childNum, tDir->virus);
//	return pDir->num_descendant;
//}
//
//void loopInfect(DIR* tDir)
//{
//	if (tDir->fileSize == 0)
//	{
//		for (R DIR* p = tDir->child; p != NULL; p = p->prev)
//		{
//			loopInfect(p);
//		}
//	}
//	tDir->virus += v * tDir->childNum;
//	tDir->num_descendant += v * tDir->childNum;
//	return;
//}
//
//int cmdInfect(int tID) {
//	if (dir[0].childNum == 0) { return 0; }
//	else { v = (dir[0].num_descendant / dir[0].childNum); }
//
//	DIR* tDir = findPath(tID);
//	loopInfect(tDir);
//	countDescendant(tDir->parent, tDir->childNum * v, 0, tDir->childNum * v);
//	return tDir->num_descendant;
//}
//
//int loopRecover(DIR* tDir)
//{
//	if (tDir->fileSize == 0)
//	{
//		for (R DIR* p = tDir->child; p != NULL; p = p->prev)
//		{
//			loopRecover(p);
//		}
//	}
//	tDir->num_descendant -= tDir->virus;
//	tDir->virus = 0;
//
//	return tDir->num_descendant;
//}
//
//int cmdRecover(int tID) {
//	R DIR* tDir = findPath(tID);
//
//	int totalVirus = tDir->virus;
//	loopRecover(tDir);
//	countDescendant(tDir->parent, -totalVirus, 0, -totalVirus);
//
//	return tDir->num_descendant;
//}
//
//int cmdRemove(int tID) {
//	if (tID == ROOT)
//	{
//		dir[0].id = 0;
//		dir[0].num_descendant = 0;
//		dir[0].virus = 0;
//		dir[0].fileSize = 0;
//		dir[0].childNum = 0;
//		dir[0].parent = NULL;
//		dir[0].child = NULL;
//		dir[0].prev = NULL;
//		return 0;
//	}
//	R DIR* tDir = findPath(tID);
//
//	deleteDir(tDir->parent, tDir);
//
//	return tDir->num_descendant;
//}