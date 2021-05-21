//#define NAME_MAXLEN 6
//#define PATH_MAXLEN 1999
//#define NULL 0
//
//const int MAX_N = 50000;
//const int MAX_CHILDREN = 30;
//const int OFFSET = 5;
//
//struct Node {
//    Node* parent;
//    Node* children;
//    Node* next;
//
//    int num_descendant;
//    int name;
//};
//
//Node nodes[MAX_N];
//int num_nodes;
//int N;
//
//int getInt(const char* src)
//{
//    register int name = 0;
//    register int i = 0;
//    for (; src[i]; i++)
//    {
//        name <<= OFFSET;
//        name |= src[i] - 'a' + 1;
//    }
//
//    return name;
//}
//
//Node* getNode()
//{
//    register Node* node = &nodes[num_nodes++];
//    node->parent = node->next = node->children = NULL;
//    node->num_descendant = 0;
//    return node;
//}
//
//void addChild(Node* parent, Node* child)
//{
//    child->next = parent->children; // linked list
//    parent->children = child;
//    child->parent = parent;
//}
//
//void init(int n)
//{
//    N = n;
//    num_nodes = 0;
//    Node* node = getNode();
//    node->name = 0;
//    //num_nodes++;
//}
//
//
//Node* findPath(char path[], int adder)
//{
//    register Node* root = &nodes[0];
//    register Node* child;
//    register int sp = 1;
//    register int ep;
//    register int name;
//
//    while (true)
//    {
//        root->num_descendant += adder;
//
//        if (path[sp] == NULL)
//        {
//            break;
//        }
//
//        name = 0;
//        for (ep = sp; path[ep] != '/'; ep++)
//        {
//            name <<= OFFSET;
//            name |= path[ep] - 'a' + 1;
//        }
//
//
//        for (child = root->children; ; child = child->next)
//        {
//            if (child->name == name)
//            {
//                root = child;
//                sp = ep + 1;
//                break;
//            }
//        }
//    }
//
//    return root;
//}
//
//void modifyDescendants(Node* parent, int adder)
//{
//    while (parent != NULL)
//    {
//        parent->num_descendant += adder;
//        parent = parent->parent;
//    }
//}
//
//
//void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
//    Node* parent = findPath(path, 1);
//    Node* child = getNode();
//    child->name = getInt(name);
//
//    addChild(parent, child);
//}
//
//void removeChild(Node* parent, Node* child)
//{
//    register Node* cur = parent->children;
//    register Node* prev = NULL;
//    for (; cur != NULL; prev = cur, cur = cur->next)
//    {
//        if (cur == child)
//        {
//            if (prev)
//            {
//                prev->next = cur->next; // prev�� ���ο� ���� linked list�� �ٸ��� �̾���.
//                // prev�� ������, prev�� ������, ������� �����ּҷ�. ����Ŵ� �����Ұű� ������.
//            }
//            else
//            {
//                parent->children = cur->next; // prev�� ���ο� ���� linked list�� �ٸ��� �̾���.
//                // prev�� ������, ����ŵ� �����ּҰ� linked list �����ּ�.
//            }
//
//            break;
//        }
//    }
//}
//
//void cmd_rm(char path[PATH_MAXLEN + 1]) {
//    Node* child = findPath(path, 0);
//    Node* parent = child->parent;
//
//    removeChild(parent, child);
//    modifyDescendants(parent, -child->num_descendant - 1); // child�� ���� ���� + �ڽ��� �θ���� ���鼭 ����.
//}
//
//void copyNode(Node* oldNode, Node* newNode)
//{
//    //name already copied by parent's function
//    newNode->num_descendant = oldNode->num_descendant;
//
//    for (register Node* child = oldNode->children; child; child = child->next)
//    {
//        Node* newChild = getNode();
//        newChild->name = child->name;
//        addChild(newNode, newChild);
//
//        copyNode(child, newChild); // �ڽ��� �ڽ��� �ڽı��� ���� ���縦 ������ϱ� ������ ����Լ�.
//    }
//}
//
//
//void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
//
//    Node* srcChild = findPath(srcPath, 0);
//    Node* dstParent = findPath(dstPath, srcChild->num_descendant + 1);
//
//    Node* newChild = getNode();
//    newChild->name = srcChild->name;
//
//    addChild(dstParent, newChild);
//    copyNode(srcChild, newChild);
//}
//
//void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
//
//    Node* child = findPath(srcPath, 0);
//    Node* srcParent = child->parent;
//    Node* dstParent = findPath(dstPath, child->num_descendant + 1);
//
//    removeChild(srcParent, child);
//    modifyDescendants(srcParent, -child->num_descendant - 1);
//
//    addChild(dstParent, child);
//}
//
//int cmd_find(char path[PATH_MAXLEN + 1]) {
//
//    return findPath(path, 0)->num_descendant;
//}