//deepblue���� �ڵ带 ����, �м��ؼ� ���� ���� �ۼ��Ͽ����ϴ�.
//deepblue�� �����մϴ� ����

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define NULL 0
#define nullptr 0
#define rint register int


struct NODE
{
	NODE* parent;
	NODE* children;
	NODE* next;
	int name;
	int num_descendant;
}nodes[50000];

int arr_idx = 0;
NODE* myalloc(void)
{
	nodes[arr_idx].parent = nodes[arr_idx].children = nodes[arr_idx].next = NULL;
	nodes[arr_idx].name = nodes[arr_idx].num_descendant = 0;
	return &nodes[arr_idx++];
}

void init(int n) {
	arr_idx = 0;
	register NODE* first = myalloc();
}

int getName(char temp[7])
{
	rint name = 0;
	for (rint i = 0; temp[i] != '\0'; i++)
	{
		name <<= 5;
		name |= temp[i] - 'a' + 1;
	}
	return name;
}

NODE* findPath(char path[PATH_MAXLEN + 1], int adder)
{
	NODE* root = &nodes[0];
	rint sp = 1;
	rint name = 0;

	while (1)
	{
		root->num_descendant += adder;

		if (path[sp] == '\0')
		{
			break;
		}

		register char temp[7];
		rint tNum = 0;
		for (; path[sp] != '/'; sp++)
		{
			temp[tNum++] = path[sp];
		}
		temp[tNum] = '\0';
		name = getName(temp);

		for (register NODE* pp = root->children; pp != NULL; pp = pp->next) //���� root����� children�ּҸ� linked list�� Ž����.
		{
			if (pp->name == name)
			{
				sp += 1;
				root = pp;
				break;
			}
		}
	}

	return root;
}

void addChild(NODE* parent, NODE* child)
{
	child->parent = parent;
	child->next = parent->children;
	parent->children = child;
	return;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	register NODE* parent = findPath(path, 1);
	register NODE* child = myalloc();
	child->name = getName(name);

	addChild(parent, child);
}

void removeNode(NODE* parent, NODE* child)
{
	register NODE* prev = NULL;
	for (register NODE* pp = parent->children; pp != NULL; prev = pp, pp = pp->next) //���� parent����� children�ּҸ� linked list�� Ž����.
	{
		if (pp->name == child->name)
		{
			if (prev == NULL) // linked list�� ���� ù��°��.
			{
				parent->children = pp->next; // �� ���� pp�� next�� �ٲ���.
			}
			else // prev��, next�� ������.
			{
				prev->next = pp->next; // ����Ÿ� ����.
			}
			break;
		}
	}
}

void discountDescendant(NODE* parent, int adder)
{
	register NODE* root = parent;

	while (1)
	{
		root->num_descendant += adder;

		if (root->name == 0)
		{
			break;
		}

		root = root->parent;
	}
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	register NODE* child = findPath(path, 0);
	register NODE* parent = child->parent;

	discountDescendant(parent, -(child->num_descendant + 1));
	removeNode(parent, child);
}

void copyChild(NODE* parent, NODE* child)
{
	if (child == NULL)
	{
		return;
	}
	for (register NODE* pp = child; pp != NULL; pp = pp->next)
	{
		register NODE* newChild = myalloc(); // child�� �ڽ��� �Ѱ��� �ƴ� �� �����ϱ� linked list�� Ž���� �ϸ鼭 copy�ؾ���.
		//*newChild = *pp;
		newChild->name = pp->name;
		newChild->num_descendant = pp->num_descendant;
		addChild(parent, newChild);
		copyChild(newChild, pp->children);
	}
	return;
}


void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	register NODE* srcParent = findPath(srcPath, 0);
	register NODE* dstParent = findPath(dstPath, srcParent->num_descendant + 1);
	register NODE* newChild = myalloc();
	//*newChild = *srcParent;
	newChild->name = srcParent->name;
	newChild->num_descendant = srcParent->num_descendant;

	addChild(dstParent, newChild);
	copyChild(newChild, srcParent->children);
}


void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	register NODE* srcChild = findPath(srcPath, 0);
	register NODE* dstParent = findPath(dstPath, srcChild->num_descendant + 1);
	register NODE* srcParent = srcChild->parent;

	removeNode(srcParent, srcChild);
	discountDescendant(srcParent, -(srcChild->num_descendant + 1));
	addChild(dstParent, srcChild);
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	return findPath(path, 0)->num_descendant;
}