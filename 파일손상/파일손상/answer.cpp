//#define MAX_CALL    10021
//#define MAX_TABLE   30011
//#define ID_ROOT     10000
//
//typedef struct _file
//{
//    int id;
//    //int isFile;
//    int initSize;
//    int increasedSize;
//    int fileNum;
//    struct _file* parent;
//    struct _file* child;
//    struct _file* childNext;
//} FILE;
//
//FILE sFile[MAX_CALL];
//int fileNum;
//FILE* pFileHashTable[MAX_TABLE];
//
//void init() {
//    for (register int i = 0; i < MAX_TABLE; i++)
//        pFileHashTable[i] = 0;
//
//    sFile[0].id = ID_ROOT;
//    sFile[0].initSize = 0;
//    sFile[0].increasedSize = 0;
//    sFile[0].fileNum = 0;
//    sFile[0].child = 0;
//
//    fileNum = 1;
//}
//
//FILE* hashGetFile(register int id) {
//    if (id == ID_ROOT)
//        return &sFile[0];
//
//    register int h = id % MAX_TABLE;
//    for (register int i = h; i < h + MAX_TABLE; i++)
//        if (pFileHashTable[i]->id == id)
//            return pFileHashTable[i];
//
//    return 0;
//}
//
//void updateParentInfo(register FILE* pFile, register int fileNum, register int initSize, register int increasedSize) {
//    while (pFile) {
//        pFile->fileNum += fileNum;
//        pFile->initSize += initSize;
//        pFile->increasedSize += increasedSize;
//        pFile = pFile->parent;
//    }
//}
//
//int cmdAdd(int newID, int pID, int fileSize) {
//    register FILE* pParent = hashGetFile(pID);
//    register FILE* pFile = &sFile[fileNum++];
//
//    pFile->id = newID;
//    pFile->fileNum = (fileSize ? 1 : 0);
//    pFile->initSize = pFile->increasedSize = fileSize;
//
//    pFile->parent = pParent;
//    pFile->child = 0;
//
//    pFile->childNext = pParent->child;
//    pParent->child = pFile;
//
//    register int h = newID % MAX_TABLE;
//    for (register int i = h; i < h + MAX_TABLE; i++) {
//        if (pFileHashTable[i % MAX_TABLE] == 0) {
//            pFileHashTable[i % MAX_TABLE] = pFile;
//            break;
//        }
//    }
//
//    updateParentInfo(pFile->parent, pFile->fileNum, fileSize, fileSize);
//
//    return pParent->increasedSize; //initSize와 increasedSize의 차이를 아직 모르겠음.
//    //위의 함수로만봐서는 완전 동일한듯.
//    //바이러스의 총합까지 포함된걸로 추정됨.
//}
//
//int cmdMove(int tID, int pID) {
//    register FILE* pFile = hashGetFile(tID);
//    register FILE* pParent = pFile->parent;
//    register FILE* pTmp = pParent->child;
//
//    if (pTmp == pFile) //linked List 이어붙이는 과정.
//        pParent->child = pFile->childNext;
//    else {
//        for (; ; pTmp = pTmp->childNext) {
//            if (pTmp->childNext == pFile) {
//                pTmp->childNext = pFile->childNext;
//                break;
//            }
//        }
//    }
//
//    updateParentInfo(pFile->parent, -(pFile->fileNum), -(pFile->initSize), -(pFile->increasedSize));
//
//    pParent = hashGetFile(pID);
//    pFile->parent = pParent;
//
//    pFile->childNext = pParent->child;
//    pParent->child = pFile;
//
//    updateParentInfo(pParent, pFile->fileNum, pFile->initSize, pFile->increasedSize);
//
//    return pParent->increasedSize;
//}
//
//void infectChild(register FILE* pFile, register int increasFileSize) {
//
//    register FILE* pChild = pFile->child;
//    pFile->increasedSize += (pFile->fileNum * increasFileSize);
//
//    while (pChild) {
//        infectChild(pChild, increasFileSize);
//        pChild = pChild->childNext;
//    }
//}
//
//int cmdInfect(int tID) {
//    register FILE* pFile = hashGetFile(tID);
//    if (sFile[0].fileNum == 0)
//        return 0;
//
//    register int increasFileSize = sFile[0].increasedSize / sFile[0].fileNum;
//
//    int updateIncreasedFileSize = pFile->fileNum * increasFileSize;
//    pFile->increasedSize += updateIncreasedFileSize;
//
//    register FILE* pChild = pFile->child;
//    while (pChild) {
//        infectChild(pChild, increasFileSize);
//        pChild = pChild->childNext;
//    }
//
//    updateParentInfo(pFile->parent, 0, 0, updateIncreasedFileSize);
//    return pFile->increasedSize;
//}
//
//
//void recoverChild(register FILE* pFile) {
//    pFile->increasedSize = pFile->initSize;
//
//    register FILE* pChild = pFile->child;
//    while (pChild) {
//        recoverChild(pChild);
//        pChild = pChild->childNext;
//    }
//}
//
//int cmdRecover(register int tID) {
//    register FILE* pFile = hashGetFile(tID);
//    register int updateDecreasFileSize = -(pFile->increasedSize - pFile->initSize);
//
//    recoverChild(pFile);
//
//    updateParentInfo(pFile->parent, 0, 0, updateDecreasFileSize);
//    return pFile->increasedSize;
//}
//
//int cmdRemove(int tID) {
//    if (tID == ID_ROOT) {
//        register int ret = sFile[0].increasedSize;
//        sFile[0].child = 0;
//        sFile[0].fileNum = 0;
//        sFile[0].increasedSize = 0;
//        sFile[0].initSize = 0;
//        return ret;
//    }
//    register FILE* pFile = hashGetFile(tID);
//    register FILE* pParent = pFile->parent;
//    register FILE* pTmp = pParent->child;
//
//    if (pTmp == pFile)
//        pParent->child = pFile->childNext;
//    else {
//        for (; ; pTmp = pTmp->childNext) {
//            if (pTmp->childNext == pFile) {
//                pTmp->childNext = pFile->childNext;
//                break;
//            }
//        }
//    }
//
//    updateParentInfo(pFile->parent, -(pFile->fileNum), -(pFile->initSize), -(pFile->increasedSize));
//
//    return pFile->increasedSize;
//}