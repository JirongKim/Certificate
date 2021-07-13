//#define MAX_USER        1001 //user�� max�� 1000
//#define MAX_FUNC_CALL   50001 // �Լ��� �� ȣ��Ƚ���� 50000
//#define MAX_HASH        5381 // hash Table�� max�� 5381
//
//struct Msg // msg ����ü ����
//{
//	int msgID; // ����ü���� ID��
//	int priority; // �켱������ �������.(score)
//};
//
//struct Hash // hash����ü�� ����.
//{
//	unsigned long long value; // �浹������ ���ؼ� ���� ���� value�� �־����.
//	Msg* pstMsg[5]; // top5�� ���� ������ �ϱ����� MSG �迭
//} tb[MAX_HASH]; // tb�� ����.
//
//int msgCount;
//Msg astMSG[MAX_FUNC_CALL];
//Msg* pstUsersMsg[MAX_USER][5];
//#define Msg() (&astMSG[msgCount++]) // myalloc �� ��������.
//
//int follow[MAX_USER][MAX_USER]; // following �� ������ ��Ÿ��
//int followCount[MAX_USER]; // following �� ������ ��Ÿ��
//
//void insert(Msg* msgArray[], Msg* msg) // insertion Sort(����ü�� �޾Ƽ�)
//{
//	register int i = 0; // �� �տ������� Ž��
//	while (i < 5 && msgArray[i] != 0) // i�� 5���� �۰�, i�� 0�� �ƴϸ� ����.
//	{
//		if (msgArray[i]->priority < msg->priority) // ���� ���� �켱������ i���� ������ change. �� ��������.
//		{
//			for (register int j = 4; j > i; j--) msgArray[j] = msgArray[j - 1]; // �� �ڿ��� ���� �� ĭ�� ���.
//			break; // ������
//		}
//		i++; // ���ǿ� ���� ������ i++
//	}
//	if (i < 5) msgArray[i] = msg; // ������ �ִ� �迭���� ��� ������ i�� 5�� �Ǽ� while������ ����. �׷��� �װŴ� �������� �ʰ� ����.
//}
//
//void init()
//{
//	register int i, j;
//	msgCount = 0;
//	for (i = 0; i < MAX_USER; i++) // 1000��ŭ �ݺ�
//	{
//		followCount[i] = j = 0; // userFollowing�� �ʱ�ȭ
//		while (pstUsersMsg[i][j] != 0 && j < 5) // top 5�� �ʱ�ȭ
//			pstUsersMsg[i][j++] = 0; // top 5�� �ʱ�ȭ
//	}
//	for (i = 0; i < MAX_HASH; i++) // ���Table�� �ʱ�ȭ
//	{
//		tb[i].value = 0; // hashTag���� �ʱ�ȭ
//		for (j = 0; j < 5; j++)
//			tb[i].pstMsg[j] = 0; // top5�� �ʱ�ȭ
//	}
//}
//
//void createMessage(int msgID, int userID, char msgData[])
//{
//	int time = (msgData[0] - '0') << 18 | (msgData[1] - '0') << 14 |    // hour
//		(msgData[3] - '0') << 11 | (msgData[4] - '0') << 7 |    // min
//		(msgData[6] - '0') << 4 | (msgData[7] - '0');         // sec
//	int priority = (time << 10) - userID; // score�� ���ϴµ�, ���� maxUser- userID�� �ߴµ� �� ���� �׳� - userID�� �ع��ȳ�. ������ ��������.
//	register unsigned long long hash = 0; // key�� ���ϱ�
//	register Msg* pstMsg = Msg(); // msg �Ҵ�ޱ�
//	pstMsg->msgID = msgID, pstMsg->priority = priority; // msgID�� score�� �ֱ�.
//
//	register char* str = &msgData[9]; // 1st hashtag
//	while (1)
//	{
//		if (*str == '#') hash = 0; //#�̸� 0���� ������.
//		else if (*str == ' ' || *str == '\0') // space�� null �̸�
//		{
//			register int index = hash % MAX_HASH; // open addressing ���� ã��.
//			while (1)
//			{
//				if (tb[index].pstMsg[0] == 0 || tb[index].value == hash) // �ش� hashTag�� ���ų�, ��ġ�ϸ�
//				{
//					tb[index].value = hash; // �ű⿡ hash���� �ְ�
//					insert(tb[index].pstMsg, pstMsg);  // ����Ÿ� �����ſ� insertion sort�� ��.
//					break;
//				}
//				else index = (index + 1) % MAX_HASH; // �ƴϸ� open addressing���� 1 ����.
//			}
//			if (*str == '\0') break; // null�̸� while���� ����, space�� hashTag�� ��� ã�ƾ��ϱ� ������ str++�� ��.
//		}
//		else hash = (hash << 5) + *str;   // or (hash * 27 + *str) => unique value (hashing �ϴ°���.)
//		// �� ���� ��쿡�� else hash = (hash << 5) + (*str - 'a' + 1); �̷��� ���� ��.
//		str++; // ���ڿ� hashing ++;
//	}
//	insert(pstUsersMsg[userID], pstMsg);// ������ ���� ��쿡�� hashTag�� top5�� ���ߴٸ�, �� ������ userID�� top5�� ����.
//}
//
//void followUser(int userID1, int userID2)
//{
//	follow[userID1][followCount[userID1]] = userID2; //  following �߰�
//	followCount[userID1]++; // following �߰�
//}
//
//int searchByHashtag(char tagName[], int retIDs[])
//{
//	register int i = 0; // i=0
//	register unsigned long long hash = 0; // key
//	for (i = 1; tagName[i] != 0; i++) hash = (hash << 5) + tagName[i]; // ���ڿ� hashing
//	register int index = hash % MAX_HASH; // hashing
//	while (1)
//	{
//		if (tb[index].pstMsg[0] != 0 && tb[index].value == hash) break; // value�� hash�� ��ġ�ϸ� break
//		else if (tb[index].pstMsg[0] == 0) return 0; // index�� ������ 0�� return ��.(���� hashTag�̱� ������)
//		index = (index + 1) % MAX_HASH; // open addressing
//	}
//	i = 0; // i ����
//	while (i < 5 && tb[index].pstMsg[i] != 0) // ��� pstMsg�� ������.
//	{
//		retIDs[i] = tb[index].pstMsg[i]->msgID; // �װ� �ٷ� retID�� ����. �ֳ��ϸ� �̹� ������ �Ǿ��ֱ� ������
//		i++; // i�� ����
//	}
//	return i; // i�� return
//}
//
//int getMessages(int userID, int retIDs[])
//{
//	register int i, k = 0;
//	register Msg* pstTempMsg[5] = { 0, }; // userID�� following �ϴ� �͵� �� �ִ�� score�� ū 5���� �����ϴ� �迭.
//	int followID, retCount = 0, fCount = followCount[userID]; // �ʱ�ȭ
//
//	for (i = 0; i < 5; i++) pstTempMsg[i] = pstUsersMsg[userID][i]; // �ϴ� ������ follow �ϴϱ� ���� �־����.
//
//	for (i = 0; i < fCount; i++) // following �ϴ� �� ��ŭ �ݺ�
//	{
//		followID = follow[userID][i]; // followID��� ������ follow�ϴ� ����� ����.
//		k = 0; // k=0
//		while (k < 5 && pstUsersMsg[followID][k] != 0) // ��� top5�迭�� ������ ��.
//		{
//			insert(pstTempMsg, pstUsersMsg[followID][k]); // �װ� pstTempMsg�� insertion Sort�� ��.
//			k++; // k�� ����
//		}
//	}
//
//	while (retCount < 5 && pstTempMsg[retCount] != 0) // pstTempMSg�� ���ĵȰ�
//	{
//		retIDs[retCount] = pstTempMsg[retCount]->msgID; // retID�� �־��ְ�
//		retCount++; // retCount�� ������Ŵ.
//	}
//	return retCount; // retCount�� return
//}