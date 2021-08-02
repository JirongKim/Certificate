#define ROOT 10000
#define MAX_TABLE 50000
#define NULL 0
#define R register

#define hash(h) (h % MAX_TABLE)

struct DIR
{
	int id;
	int num_descendant;
	int childNum;
	int fileSize;
	int virus;
	DIR* child;
	DIR* parent;
	DIR* prev;
} dir[MAX_TABLE];
int arr_idx = 0;
DIR* myalloc(void) { return &dir[arr_idx++]; }
DIR* dirTable[MAX_TABLE];

void init() {
	for (R int i = 0; i < arr_idx; i++)
	{
		dir[i].id = 0;
		dir[i].num_descendant = 0;
		dir[i].childNum = 0;
		dir[i].fileSize = 0;
		dir[i].virus = 0;
		dir[i].child = NULL;
		dir[i].parent = NULL;
		dir[i].prev = NULL;
	}
	arr_idx = 0;

	for (R int i = 0; i < MAX_TABLE; i++)
	{
		dirTable[i] = NULL;
	}

	DIR* root = myalloc();
	root->id = ROOT;

	dirTable[ROOT] = root;
}

inline DIR* find(int uid)
{
	R int key = hash(uid);
	while (1)
	{
		if (dirTable[key] != NULL && dirTable[key]->id == uid)
		{
			break;
		}
		key = key + 1;
		key = hash(key);
	}
	return dirTable[key];
}

inline void addChild(DIR* par, DIR* ch)
{
	ch->parent = par;
	ch->prev = par->child;
	par->child = ch;
}

inline void countDescendant(DIR* cur, int adder, int childAdder, int virusAdder)
{
	if (cur == NULL) { return; }
	while (1)
	{
		if (cur == NULL) { break; }
		cur->num_descendant += adder;
		cur->childNum += childAdder;
		cur->virus += virusAdder;
		cur = cur->parent;
	}
}

inline DIR* add(int newID, int fileSize)
{
	R DIR* newDir = myalloc();
	newDir->id = newID;
	newDir->fileSize = fileSize;

	R int key = hash(newID);
	while (1)
	{
		if (dirTable[key] == NULL)
		{
			dirTable[key] = newDir;
			break;
		}
		key = key + 1;
		key = hash(key);
	}
	return dirTable[key];
}

int cmdAdd(int newID, int pID, int fileSize) {
	R DIR* parDir = find(pID);
	R DIR* newDir = add(newID, fileSize);

	addChild(parDir, newDir);
	countDescendant(newDir, fileSize, (fileSize ? 1 : 0), 0);

	return parDir->num_descendant;
}

inline void deleteChild(DIR* par, DIR* ch)
{
	R DIR* temp = NULL;
	for (R DIR* p = par->child; p != NULL; temp = p, p = p->prev)
	{
		if (p->id == ch->id)
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

int cmdMove(int tID, int pID) {
	R DIR* tDir = find(tID);
	R DIR* pDir = find(pID);

	deleteChild(tDir->parent, tDir);
	countDescendant(tDir->parent, -tDir->num_descendant, -tDir->childNum, -tDir->virus);

	addChild(pDir, tDir);
	countDescendant(pDir, tDir->num_descendant, tDir->childNum, tDir->virus);

	return pDir->num_descendant;
}

inline void loopInfect(DIR* cur, int v)
{
	if (cur == NULL) { return; }
	cur->virus += cur->childNum * v;
	cur->num_descendant += cur->childNum * v;
	for (R DIR* p = cur->child; p != NULL; p = p->prev)
	{
		loopInfect(p, v);
	}
}

int cmdInfect(int tID) {
	if (dir[0].childNum == 0) { return 0; }
	R int v = (dir[0].num_descendant / dir[0].childNum);

	R DIR* tDir = find(tID);
	loopInfect(tDir, v);
	countDescendant(tDir->parent, tDir->childNum * v, 0, tDir->childNum * v);

	return tDir->num_descendant;
}

inline void loopRecover(DIR* cur)
{
	if (cur == NULL) { return; }
	cur->num_descendant -= cur->virus;
	cur->virus = 0;
	for (R DIR* p = cur->child; p != NULL; p = p->prev)
	{
		loopRecover(p);
	}
}

int cmdRecover(int tID) {
	R DIR* tDir = find(tID);

	R int virusTemp = tDir->virus;
	loopRecover(tDir);
	countDescendant(tDir->parent, -virusTemp, 0, -virusTemp);

	return tDir->num_descendant;
}

int cmdRemove(int tID) {
	R DIR* tDir = find(tID);

	deleteChild(tDir->parent, tDir);
	countDescendant(tDir->parent, -tDir->num_descendant, -tDir->childNum, -tDir->virus);

	return tDir->num_descendant;
}