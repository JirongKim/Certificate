//#define MAXD 10001
//#define ROOT_ID 10000
//#define HASH 30007
//#define rint register unsigned int
//
//struct DIR {
//    int idx;
//    int id;
//    int size;
//    int ori_size;
//    int num_files;
//    bool is_file;
//    DIR* parent;
//    DIR* next;
//    DIR* prev;
//}dir[MAXD];
//
//int num_dir;
//DIR& root = dir[0];
//
//struct HashInfo {
//    int id;
//    DIR* data;
//}table[HASH];
//
//DIR child_head[MAXD];
//DIR child_tail[MAXD];
//
//void add_list(DIR* cur, DIR* newnode)
//{
//    newnode->next = cur->next;
//    newnode->prev = cur;
//    cur->next->prev = newnode;
//    cur->next = newnode;
//}
//
//void del_list(DIR* cur)
//{
//    cur->next->prev = cur->prev;
//    cur->prev->next = cur->next;
//}
//
//
//DIR* find(int Id)
//{
//    int h = Id % HASH;
//    int cnt = HASH;
//
//    for (; cnt; h = (h + 1) % HASH)
//    {
//        if (table[h].id != -1 && table[h].id == Id) {
//            return table[h].data;
//        }
//        cnt--;
//    }
//    return nullptr;
//}
//
//int add(DIR* cur, int Id)
//{
//    int h = Id % HASH;
//
//    for (;; h = (h + 1) % HASH) {
//        if (table[h].id != -1 && table[h].id != Id) continue;
//        table[h].id = Id;
//        table[h].data = cur;
//        return 1;
//    }
//
//    return 0;
//}
//
//
//void init() {
//    root.idx = 0;
//    root.id = ROOT_ID;
//    root.size = 0;
//    root.ori_size = 0;
//    root.num_files = 0;
//    root.is_file = false;
//    root.prev = root.next = root.parent = nullptr;
//    num_dir = 1;
//
//    for (rint i = 0; i < HASH; i++)
//        table[i].id = -1;
//
//    for (rint i = 0; i < MAXD; i++) {
//        child_head[i].next = &child_tail[i];
//        child_tail[i].prev = &child_head[i];
//    }
//    add(&root, root.id);
//}
//
//void update_parents(register DIR* parent, int size, int num_files)
//{
//    for (; parent != &root; parent = parent->parent) {
//        parent->size += size;
//        parent->num_files += num_files;
//    }
//    root.size += size;
//    root.num_files += num_files;
//}
//
//int cmdAdd(int newID, int pID, int fileSize) {
//    DIR& n = dir[num_dir];
//    DIR* parent = find(pID);
//
//    n.idx = num_dir;
//    n.id = newID;
//    n.ori_size = n.size = fileSize;
//    n.parent = parent;
//    n.next = n.prev = nullptr;
//    add_list(&child_head[parent->idx], &n);
//    add(&n, n.id);
//    if (fileSize > 0) {
//        n.num_files = 1;
//        n.is_file = true;
//        update_parents(parent, fileSize, 1);
//    }
//    else {
//        n.is_file = false;
//        n.num_files = 0;
//    }
//    num_dir++;
//    return parent->size;
//}
//
//int update_child(register DIR* cur, int infectSize)
//{
//    if (cur->is_file) {
//        cur->size += infectSize;
//        return cur->size;
//    }
//    else {
//        cur->size = 0;
//
//        for (register DIR* temp = child_head[cur->idx].next; temp != &child_tail[cur->idx]; temp = temp->next) {
//            cur->size += update_child(temp, infectSize);
//        }
//        return cur->size;
//    }
//}
//
//int recover_child(register DIR* cur)
//{
//    if (cur->is_file) {
//        cur->size = cur->ori_size;
//        return cur->size;
//    }
//    else {
//        cur->size = 0;
//        for (register DIR* temp = child_head[cur->idx].next; temp != &child_tail[cur->idx]; temp = temp->next) {
//            cur->size += recover_child(temp);
//        }
//        return cur->size;
//    }
//}
//
//int cmdInfect(int tID) {
//    register DIR* temp = find(tID);
//    register int infectSize;
//
//    if (root.num_files == 0)
//        return 0;
//    infectSize = root.size / root.num_files;
//    if (temp->is_file == true) {
//        temp->size += infectSize;
//        if (tID != ROOT_ID)
//            update_parents(temp->parent, infectSize, 0);
//    }
//    else {
//        int increased = temp->size;
//        temp->size = update_child(temp, infectSize);
//        increased = temp->size - increased;
//        if (tID != ROOT_ID)
//            update_parents(temp->parent, increased, 0);
//    }
//    return temp->size;
//}
//
//int cmdRecover(int tID) {
//    register DIR* temp = find(tID);
//    if (temp->is_file == true) {
//        int increased = temp->ori_size - temp->size;
//        temp->size = temp->ori_size;
//        if (tID != ROOT_ID)
//            update_parents(temp->parent, increased, 0);
//    }
//    else {
//        int increased = temp->size;
//        temp->size = recover_child(temp);
//        increased = temp->size - increased;
//        if (tID != ROOT_ID)
//            update_parents(temp->parent, increased, 0);
//    }
//    return temp->size;
//}
//
//int cmdRemove(int tID) {
//    DIR* temp = find(tID);
//
//    if (tID == ROOT_ID) {
//        int total = root.size;
//        init();
//        return total;
//    }
//    update_parents(temp->parent, -temp->size, -temp->num_files);
//    del_list(temp);
//    return temp->size;
//}
//
//int cmdMove(int tID, int pID) {
//    DIR* temp = find(tID);
//    DIR* parent = find(pID);
//
//    update_parents(temp->parent, -temp->size, -temp->num_files);
//    del_list(temp);
//
//    temp->parent = parent;
//    add_list(&child_head[parent->idx], temp);
//    update_parents(temp->parent, temp->size, temp->num_files);
//    return parent->size;
//}