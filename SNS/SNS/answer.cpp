//#define MAX_USER        1001 //user의 max는 1000
//#define MAX_FUNC_CALL   50001 // 함수의 총 호출횟수는 50000
//#define MAX_HASH        5381 // hash Table의 max는 5381
//
//struct Msg // msg 구조체 생성
//{
//	int msgID; // 구조체에는 ID와
//	int priority; // 우선순위만 들어있음.(score)
//};
//
//struct Hash // hash구조체를 생성.
//{
//	unsigned long long value; // 충돌방지를 위해서 실제 값을 value로 넣어놓음.
//	Msg* pstMsg[5]; // top5의 값만 저장을 하기위한 MSG 배열
//} tb[MAX_HASH]; // tb로 정의.
//
//int msgCount;
//Msg astMSG[MAX_FUNC_CALL];
//Msg* pstUsersMsg[MAX_USER][5];
//#define Msg() (&astMSG[msgCount++]) // myalloc 과 같은역할.
//
//int follow[MAX_USER][MAX_USER]; // following 의 정보를 나타냄
//int followCount[MAX_USER]; // following 의 정보를 나타냄
//
//void insert(Msg* msgArray[], Msg* msg) // insertion Sort(구조체를 받아서)
//{
//	register int i = 0; // 맨 앞에서부터 탐색
//	while (i < 5 && msgArray[i] != 0) // i가 5보다 작고, i가 0이 아니면 동작.
//	{
//		if (msgArray[i]->priority < msg->priority) // 새로 들어온 우선순위가 i보다 높으면 change. 즉 내림차순.
//		{
//			for (register int j = 4; j > i; j--) msgArray[j] = msgArray[j - 1]; // 맨 뒤에서 부터 한 칸식 당김.
//			break; // 나가기
//		}
//		i++; // 조건에 맞지 않으면 i++
//	}
//	if (i < 5) msgArray[i] = msg; // 기존에 있던 배열보다 모두 작으면 i가 5가 되서 while문에서 나옴. 그러면 그거는 저장하지 않고 버림.
//}
//
//void init()
//{
//	register int i, j;
//	msgCount = 0;
//	for (i = 0; i < MAX_USER; i++) // 1000만큼 반복
//	{
//		followCount[i] = j = 0; // userFollowing을 초기화
//		while (pstUsersMsg[i][j] != 0 && j < 5) // top 5를 초기화
//			pstUsersMsg[i][j++] = 0; // top 5를 초기화
//	}
//	for (i = 0; i < MAX_HASH; i++) // 모든Table을 초기화
//	{
//		tb[i].value = 0; // hashTag값을 초기화
//		for (j = 0; j < 5; j++)
//			tb[i].pstMsg[j] = 0; // top5를 초기화
//	}
//}
//
//void createMessage(int msgID, int userID, char msgData[])
//{
//	int time = (msgData[0] - '0') << 18 | (msgData[1] - '0') << 14 |    // hour
//		(msgData[3] - '0') << 11 | (msgData[4] - '0') << 7 |    // min
//		(msgData[6] - '0') << 4 | (msgData[7] - '0');         // sec
//	int priority = (time << 10) - userID; // score를 구하는데, 나는 maxUser- userID를 했는데 이 분은 그냥 - userID를 해버렸네. 괜찮으 ㄴ생각임.
//	register unsigned long long hash = 0; // key값 구하기
//	register Msg* pstMsg = Msg(); // msg 할당받기
//	pstMsg->msgID = msgID, pstMsg->priority = priority; // msgID와 score를 넣기.
//
//	register char* str = &msgData[9]; // 1st hashtag
//	while (1)
//	{
//		if (*str == '#') hash = 0; //#이면 0으로 시작함.
//		else if (*str == ' ' || *str == '\0') // space나 null 이면
//		{
//			register int index = hash % MAX_HASH; // open addressing 으로 찾기.
//			while (1)
//			{
//				if (tb[index].pstMsg[0] == 0 || tb[index].value == hash) // 해당 hashTag가 없거나, 일치하면
//				{
//					tb[index].value = hash; // 거기에 hash값을 넣고
//					insert(tb[index].pstMsg, pstMsg);  // 현재거를 기존거에 insertion sort를 함.
//					break;
//				}
//				else index = (index + 1) % MAX_HASH; // 아니면 open addressing으로 1 증가.
//			}
//			if (*str == '\0') break; // null이면 while문을 종료, space면 hashTag를 계속 찾아야하기 때문에 str++로 감.
//		}
//		else hash = (hash << 5) + *str;   // or (hash * 27 + *str) => unique value (hashing 하는거임.)
//		// 나 같은 경우에는 else hash = (hash << 5) + (*str - 'a' + 1); 이렇게 했을 듯.
//		str++; // 문자열 hashing ++;
//	}
//	insert(pstUsersMsg[userID], pstMsg);// 위에것 같은 경우에는 hashTag의 top5를 구했다면, 이 문장은 userID의 top5를 구함.
//}
//
//void followUser(int userID1, int userID2)
//{
//	follow[userID1][followCount[userID1]] = userID2; //  following 추가
//	followCount[userID1]++; // following 추가
//}
//
//int searchByHashtag(char tagName[], int retIDs[])
//{
//	register int i = 0; // i=0
//	register unsigned long long hash = 0; // key
//	for (i = 1; tagName[i] != 0; i++) hash = (hash << 5) + tagName[i]; // 문자열 hashing
//	register int index = hash % MAX_HASH; // hashing
//	while (1)
//	{
//		if (tb[index].pstMsg[0] != 0 && tb[index].value == hash) break; // value와 hash가 일치하면 break
//		else if (tb[index].pstMsg[0] == 0) return 0; // index가 없으면 0을 return 함.(없는 hashTag이기 때문에)
//		index = (index + 1) % MAX_HASH; // open addressing
//	}
//	i = 0; // i 재사용
//	while (i < 5 && tb[index].pstMsg[i] != 0) // 모든 pstMsg를 가져옴.
//	{
//		retIDs[i] = tb[index].pstMsg[i]->msgID; // 그걸 바로 retID에 넣음. 왜냐하면 이미 정렬이 되어있기 때문에
//		i++; // i를 증가
//	}
//	return i; // i를 return
//}
//
//int getMessages(int userID, int retIDs[])
//{
//	register int i, k = 0;
//	register Msg* pstTempMsg[5] = { 0, }; // userID의 following 하는 것들 중 최대로 score가 큰 5개를 저장하는 배열.
//	int followID, retCount = 0, fCount = followCount[userID]; // 초기화
//
//	for (i = 0; i < 5; i++) pstTempMsg[i] = pstUsersMsg[userID][i]; // 일단 본인을 follow 하니까 먼저 넣어놓음.
//
//	for (i = 0; i < fCount; i++) // following 하는 수 만큼 반복
//	{
//		followID = follow[userID][i]; // followID라는 변수에 follow하는 목록을 저장.
//		k = 0; // k=0
//		while (k < 5 && pstUsersMsg[followID][k] != 0) // 모든 top5배열을 가지고 옴.
//		{
//			insert(pstTempMsg, pstUsersMsg[followID][k]); // 그걸 pstTempMsg에 insertion Sort를 함.
//			k++; // k를 증가
//		}
//	}
//
//	while (retCount < 5 && pstTempMsg[retCount] != 0) // pstTempMSg에 정렬된걸
//	{
//		retIDs[retCount] = pstTempMsg[retCount]->msgID; // retID에 넣어주고
//		retCount++; // retCount를 증가시킴.
//	}
//	return retCount; // retCount를 return
//}