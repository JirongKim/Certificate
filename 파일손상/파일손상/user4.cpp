//#define MAX_DIR 10001
//#define MAX_TABLE 50007
//#define ROOT 10000
//#define NULL 0
//
//#define hash(h) (h % MAX_TABLE)
//
//struct DIR
//{
//	int id;
//	int num_descendant;
//	int childNum;
//	int fileSize;
//	int virus;
//	DIR* child;
//	DIR* parent;
//	DIR* prev;
//} dir[MAX_DIR];
//int arr_idx = 0;
//DIR* myalloc(void) { return &dir[arr_idx++]; }
//
//DIR* dirTable[MAX_TABLE];
//
//void init() {
//	for (int i = 0; i < arr_idx; i++)
//	{
//		dir[i].id = 0;
//		dir[i].num_descendant = 0;
//		dir[i].childNum = 0;
//		dir[i].fileSize = 0;
//		dir[i].virus = 0;
//		dir[i].child = NULL;
//		dir[i].parent = NULL;
//		dir[i].prev = NULL;
//	}
//	for (int i = 0; i < MAX_TABLE; i++)
//	{
//		dirTable[i] = NULL;
//	}
//	arr_idx = 0;
//	DIR* root = myalloc();
//	root->id = ROOT;
//	dirTable[ROOT] = root;
//}
//
//DIR* find(int id)
//{
//	int key = hash(id);
//
//	while (1)
//	{
//		if (dirTable[key] != NULL && dirTable[key]->id == id)
//		{
//			break;
//		}
//		key = key + 1;
//		key = hash(key);
//	}
//	return dirTable[key];
//}
//
//DIR* make(int id, int fs)
//{
//	int key = hash(id);
//
//	while (1)
//	{
//		if (dirTable[key] == NULL)
//		{
//			DIR* newDir = myalloc();
//			newDir->id = id;
//			newDir->fileSize = fs;
//			dirTable[key] = newDir;
//			break;
//		}
//		key = key + 1;
//		key = hash(key);
//	}
//	return dirTable[key];
//}
//
//void addChild(DIR* par, DIR* chi)
//{
//	chi->parent = par;
//	chi->prev = par->child;
//	par->child = chi;
//}
//
//void countDiscendant(DIR* cur, int adder, int childAdder, int virusAdder)
//{
//	if (cur == NULL) { return; }
//	cur->num_descendant += adder;
//	cur->childNum += childAdder;
//	cur->virus += virusAdder;
//	countDiscendant(cur->parent, adder, childAdder, virusAdder);
//}
//
//int cmdAdd(int newID, int pID, int fileSize) {
//	DIR* parDir = find(pID);
//	DIR* newDir = make(newID, fileSize);
//
//	addChild(parDir, newDir);
//	countDiscendant(newDir, fileSize, (fileSize ? 1 : 0), 0);
//	return parDir->num_descendant;
//}
//
//void deleteDir(DIR* par, DIR* cur)
//{
//	if (par == NULL) { return; }
//	DIR* temp = NULL;
//	for (DIR* p = par->child; p != NULL; temp = p, p = p->prev)
//	{
//		if (p->id == cur->id)
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
//int cmdMove(int tID, int pID) {
//	DIR* srcDir = find(tID);
//	DIR* dstDir = find(pID);
//
//	deleteDir(srcDir->parent, srcDir);
//	countDiscendant(srcDir->parent, -srcDir->num_descendant, -srcDir->childNum, -srcDir->virus);
//
//	addChild(dstDir, srcDir);
//	countDiscendant(dstDir, srcDir->num_descendant, srcDir->childNum, srcDir->virus);
//	return dstDir->num_descendant;
//}
//
//void loopInfect(DIR* cur, int v)
//{
//	if (cur == NULL) { return; }
//	cur->num_descendant += v * cur->childNum;
//	cur->virus += v * cur->childNum;
//	for (DIR* p = cur->child; p != NULL; p = p->prev)
//	{
//		loopInfect(p, v);
//	}
//}
//
//int cmdInfect(int tID) {
//	if (dir[0].childNum == 0) { return 0; }
//	int v = (dir[0].num_descendant / dir[0].childNum);
//	DIR* curDir = find(tID);
//
//	loopInfect(curDir, v);
//	countDiscendant(curDir->parent, v * curDir->childNum, 0, v * curDir->childNum);
//	return curDir->num_descendant;
//}
//
//void loopRecover(DIR* cur)
//{
//	if (cur == NULL) { return; }
//	cur->num_descendant -= cur->virus;
//	cur->virus = 0;
//	for (DIR* p = cur->child; p != NULL; p = p->prev)
//	{
//		loopRecover(p);
//	}
//}
//
//int cmdRecover(int tID) {
//	DIR* curDir = find(tID);
//	int virusTemp = curDir->virus;
//
//	loopRecover(curDir);
//	countDiscendant(curDir->parent, -virusTemp, 0, -virusTemp);
//	return curDir->num_descendant;
//}
//
//int cmdRemove(int tID) {
//	DIR* curDir = find(tID);
//
//	deleteDir(curDir->parent, curDir);
//	countDiscendant(curDir->parent, -curDir->num_descendant, -curDir->childNum, -curDir->virus);
//
//	return curDir->num_descendant;
//}