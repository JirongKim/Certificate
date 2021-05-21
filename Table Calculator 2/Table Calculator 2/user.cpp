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
		table[col][row].value = strToInt(input, 0); // ����� �޾ƿ�
		initStr(col, row); // col,row�� �ٽ� ȣ��� �� ������ ����ִ� �Լ��� ����.
		/*printf("����%d\n", table[col][row].value);*/
	} //���ڷ� �ٲٱ�
	else if (input[0] == '-')
	{
		table[col][row].value = strToInt(input, 1) * -1; // ������ �޾ƿ�
		initStr(col, row); // col,row�� �ٽ� ȣ��� �� ������ ����ִ� �Լ��� ����.
		/*printf("����%d\n", table[col][row].value);*/
	}
	else
	{
		strCopy(input, table[col][row].function); // ������ 2��° �ڸ�����(�Լ��� ������ ����) col, row�� function�� ����.
		table[col][row].value = 0; // ������ ����ִ� �� �ʱ�ȭ
		/*printf("%s\n", table[col][row].function);*/
	}
}

void df(int i, int j)
{
	int maxValue = -10001; // ��������� -10000 ~ +10000 ������. max�� ã������ -10001
	int minValue = 10001; // ��������� -10000 ~ +10000 ������. min�� ã������ +10001
	int sumValue = 0; // sum�� ����� ����
	int c1, c2, r1, r2;
	getCR(table[i][j].function, &c1, &c2, &r1, &r2); // i, j�� �̿��ؼ� C,R�� �޾ƿ�
	//printf("c1 %d, c2 %d, r1 %d, r2 %d\n", c1, c2, r1, r2);
	if (table[c1][r1].function[0] != '\0') { df(c1, r1); } // ���� c1,r1�� �Լ����? ����� ����� �� ������ ���� �켱Ž��.
	if (table[c2][r2].function[0] != '\0') { df(c2, r2); } // ���� c2,r2�� �Լ����? ����� ����� �� ������ ���� �켱Ž��.

	//(c1,r1),(c2,r2)�� �Լ��� �ƴ϶��? ���� ����� �� ����.

	char mode = table[i][j].function[0]; // ������ ��ǥ�� � �Լ����� �Ǵ�.
	// i,j�� ����� ���� ����. �ֳ��ϸ� df�Լ��� �������� ����ΰ͵��� �ɷ��� ����.
	// ���� �Ʒ��� ������ �Լ��� ����.

	switch (mode)
	{
	case 'D':
		//printf("MODE : ADD\n");
		table[i][j].value = table[c1][r1].value + table[c2][r2].value;
		//initStr(i, j); //�̰� ���ָ�, �Լ��� ������� �ǹ���.
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
		if (c1 == c2) // c1�� c2�� ������?
		{
			for (register int tempR1 = r1; tempR1 <= r2; tempR1++) // ���θ� Ž��
			{
				if (table[c1][tempR1].function[0] != '\0') // ���� Ž�� �߿� ���� �Լ����?
				{
					df(c1, tempR1); // �Լ� Ž��
				}
				if (maxValue < table[c1][tempR1].value) { maxValue = table[c1][tempR1].value; }
			}
		}
		else if (r1 == r2) // r1�� r2�� ������?
		{
			for (register int tempC1 = c1; tempC1 <= c2; tempC1++) // ���θ� Ž��
			{
				if (table[tempC1][r1].function[0] != '\0') // ���� Ž�� �߿� ���� �Լ����?
				{
					df(tempC1, r1); // �Լ� Ž��
				}
				if (maxValue < table[tempC1][r1].value) { maxValue = table[tempC1][r1].value; }
			}
		}
		table[i][j].value = maxValue; // ������� i,j�� ����.
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
		table[i][j].value = minValue; // ������� i,j�� ����.
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
		//printf("����� ������ �ȵǴ� ���ε�?\n");
		break;
	}
	return;
}

void update(int value[MAXR][MAXC]) {  // col, row�� �����ٰ� ���ڱ� row, col�� ����.

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

	for (register int i = 1; i <= RLEN; i++) // col, row�� �ۼ��ߴµ�, row col�� �޶�� �ؼ� �ٲ��ִ� �۾�.
	{
		for (register int j = 1; j <= CLEN; j++)
		{
			//printf("%7d", table[j][i].value);
			value[i - 1][j - 1] = table[j][i].value;
		}
		//printf("\n");
	}
}