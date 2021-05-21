#include <stdio.h>

#define MAXC 26
#define MAXR 99

struct TABLE
{
	int value;
	char function[10];
};

TABLE table[MAXC + 1][MAXR + 1];

int CLEN;
int RLEN;

void initStr(int i, int j)
{
	table[i][j].function[0] = '\0';
}

void init(int C, int R) {
	for (register int i = 1; i <= C; i++)
	{
		for (register int j = 1; j <= R; j++)
		{
			table[i][j].value = 0;
			initStr(i, j);
		}
	}
	CLEN = C;
	RLEN = R;
}

int strToInt(char input[], int start)
{
	int result = 0;

	register int i = start;
	while (input[i] >= '0' && input[i] <= '9')
	{
		result = (result * 10) + (input[i] - '0');
		i++;
	}

	return result;
}

void getCR(char input[], int* c1, int* c2, int* r1, int* r2)
{
	//D(A13,B13)
	int i;
	*c1 = input[2] - 'A' + 1;
	*r1 = strToInt(input, 3);

	if (*r1 >= 10) { i = 6; }
	else { i = 5; }
	*c2 = input[i] - 'A' + 1;
	*r2 = strToInt(input, i + 1);
}

void strCopy(char* input, char* arr2)
{
	for (register int i = 2; input[i] != '\0'; i++)
	{
		arr2[i - 2] = input[i];
	}
}


void set(int col, int row, char input[]) {
	if (input[0] >= '0' && input[0] <= '9')
	{ 
		table[col][row].value = strToInt(input, 0); // 상수를 받아옴
		initStr(col, row); // col,row가 다시 호출될 때 기존에 들어있던 함수를 없앰.
		/*printf("숫자%d\n", table[col][row].value);*/
	} //숫자로 바꾸기
	else if (input[0] == '-')
	{
		table[col][row].value = strToInt(input, 1) * -1; // 음수를 받아옴
		initStr(col, row); // col,row가 다시 호출될 때 기존에 들어있던 함수를 없앰.
		/*printf("숫자%d\n", table[col][row].value);*/
	}
	else
	{
		strCopy(input, table[col][row].function); // 문자의 2번째 자리부터(함수의 마지막 글자) col, row의 function에 넣음.
		table[col][row].value = 0; // 기존에 들어있던 값 초기화
		/*printf("%s\n", table[col][row].function);*/
	}
}

void df(int i, int j)
{
	int maxValue = -10001; // 제약사항이 -10000 ~ +10000 까지라서. max를 찾으려면 -10001
	int minValue = 10001; // 제약사항이 -10000 ~ +10000 까지라서. min를 찾으려면 +10001
	int sumValue = 0; // sum을 담당할 변수
	int c1, c2, r1, r2;
	getCR(table[i][j].function, &c1, &c2, &r1, &r2); // i, j를 이용해서 C,R을 받아옴
	//printf("c1 %d, c2 %d, r1 %d, r2 %d\n", c1, c2, r1, r2);
	if (table[c1][r1].function[0] != '\0') { df(c1, r1); } // 만약 c1,r1가 함수라면? 현재는 계산할 수 없으니 깊이 우선탐색.
	if (table[c2][r2].function[0] != '\0') { df(c2, r2); } // 만약 c2,r2가 함수라면? 현재는 계산할 수 없으니 깊이 우선탐색.

	//(c1,r1),(c2,r2)가 함수가 아니라면? 이제 계산할 수 있음.

	char mode = table[i][j].function[0]; // 현재의 좌표가 어떤 함수인지 판단.
	// i,j가 상수일 수는 없음. 왜냐하면 df함수를 오기전에 상수인것들은 걸렀기 때문.
	// 따라서 아래는 무조건 함수가 나옴.

	switch (mode)
	{
	case 'D':
		//printf("MODE : ADD\n");
		table[i][j].value = table[c1][r1].value + table[c2][r2].value;
		//initStr(i, j); //이걸 해주면, 함수가 사라지게 되버림.
		break;
	case 'B':
		//printf("MODE : SUB\n");
		table[i][j].value = table[c1][r1].value - table[c2][r2].value;
		//initStr(i, j);
		break;
	case 'L':
		//printf("MODE : MUL\n");
		table[i][j].value = table[c1][r1].value * table[c2][r2].value;
		//initStr(i, j);
		break;
	case 'V':
		//printf("MODE : DIV\n");
		table[i][j].value = table[c1][r1].value / table[c2][r2].value;
		//initStr(i, j);
		break;
	case 'X':
		//printf("MODE : MAX\n");
		if (c1 == c2) // c1과 c2가 같으면?
		{
			for (register int tempR1 = r1; tempR1 <= r2; tempR1++) // 세로를 탐색
			{
				if (table[c1][tempR1].function[0] != '\0') // 만약 탐색 중에 셀이 함수라면?
				{
					df(c1, tempR1); // 함수 탐색
				}
				if (maxValue < table[c1][tempR1].value) { maxValue = table[c1][tempR1].value; }
			}
		}
		else if (r1 == r2) // r1과 r2가 같으면?
		{
			for (register int tempC1 = c1; tempC1 <= c2; tempC1++) // 가로를 탐색
			{
				if (table[tempC1][r1].function[0] != '\0') // 만약 탐색 중에 셀이 함수라면?
				{
					df(tempC1, r1); // 함수 탐색
				}
				if (maxValue < table[tempC1][r1].value) { maxValue = table[tempC1][r1].value; }
			}
		}
		table[i][j].value = maxValue; // 결과값을 i,j에 넣음.
		//initStr(i, j);
		break;
	case 'N':
		//printf("MODE : MIN\n");
		if (c1 == c2)
		{
			for (register int tempR1 = r1; tempR1 <= r2; tempR1++)
			{
				if (table[c1][tempR1].function[0] != '\0')
				{
					df(c1, tempR1);
				}
				if (minValue > table[c1][tempR1].value) { minValue = table[c1][tempR1].value; }
			}
		}
		else if (r1 == r2)
		{
			for (register int tempC1 = c1; tempC1 <= c2; tempC1++)
			{
				if (table[tempC1][r1].function[0] != '\0')
				{
					df(tempC1, r1);
				}
				if (minValue > table[tempC1][r1].value) { minValue = table[tempC1][r1].value; }
			}
		}
		table[i][j].value = minValue; // 결과값을 i,j에 넣음.
		//initStr(i, j);
		break;
	case 'M':
		//printf("MODE : SUM\n");
		if (c1 == c2)
		{
			for (register int tempR1 = r1; tempR1 <= r2; tempR1++)
			{
				if (table[c1][tempR1].function[0] != '\0')
				{
					df(c1, tempR1);
				}
				sumValue += table[c1][tempR1].value;
			}
		}
		else if (r1 == r2)
		{
			for (register int tempC1 = c1; tempC1 <= c2; tempC1++)
			{
				if (table[tempC1][r1].function[0] != '\0')
				{
					df(tempC1, r1);
				}
				sumValue += table[tempC1][r1].value;
			}
		}
		table[i][j].value = sumValue;
		//initStr(i, j);
		break;
	default:
		//printf("여기는 들어오면 안되는 곳인디?\n");
		break;
	}
	return;
}

void update(int value[MAXR][MAXC]) {  // col, row로 들어오다가 갑자기 row, col로 들어옴.

	/*for (int i = 0; i < MAXR; i++)
	{
		for (int j = 0; j < MAXC; j++)
		{
			value[i][j] = 0;
		}
	}*/

	for (register int i = 1; i <= CLEN; i++)
	{
		for (register int j = 1; j <= RLEN; j++)
		{
			if (table[i][j].function[0] != '\0')
			{
				df(i, j);
			}
		}
	}

	for (register int i = 1; i <= RLEN; i++) // col, row로 작성했는데, row col로 달라고 해서 바꿔주는 작업.
	{
		for (register int j = 1; j <= CLEN; j++)
		{
			//printf("%7d", table[j][i].value);
			value[i - 1][j - 1] = table[j][i].value;
		}
		//printf("\n");
	}
}