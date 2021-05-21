#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	int T;
	scanf("%d", &T);

	for (int test_case = 0; test_case < T; test_case++)
	{
		char arr[4][4] = { 0, };
		int draw_flag = 1;
		int endflag = 0;
		int sum = 0;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				scanf(" %c", &arr[i][j]);
				if (arr[i][j] == '.') draw_flag = 0;
			}
		}

		for (int i = 0; i < 4; i++)  // 가로 check
		{
			sum = arr[i][0] + arr[i][1] + arr[i][2] + arr[i][3];
			if (sum == 'X' * 4 || sum == 'X' * 3 + 'T')
			{
				printf("#%d X won\n", test_case + 1);
				endflag = 1;
				break;
			}
			if (sum == 'O' * 4 || sum == 'O' * 3 + 'T')
			{
				printf("#%d O won\n", test_case + 1);
				endflag = 1;
				break;
			}
		}
		
		if (endflag) continue;

		for (int i = 0; i < 4; i++)  // 세로 check
		{
			sum = arr[0][i] + arr[1][i] + arr[2][i] + arr[3][i];
			if (sum == 'X' * 4 || sum == 'X' * 3 + 'T')
			{
				printf("#%d X won\n", test_case + 1);
				endflag = 1;
				break;
			}
			if (sum == 'O' * 4 || sum == 'O' * 3 + 'T')
			{
				printf("#%d O won\n", test_case + 1);
				endflag = 1;
				break;
			}
		}

		if (endflag) continue;

		sum = arr[0][0] + arr[1][1] + arr[2][2] + arr[3][3]; // 대각 Check
		if (sum == 'X' * 4 || sum == 'X' * 3 + 'T')
		{
			printf("#%d X won\n", test_case + 1);
			endflag = 1;
		}
		if (sum == 'O' * 4 || sum == 'O' * 3 + 'T')
		{
			printf("#%d O won\n", test_case + 1);
			endflag = 1;
		}

		if (endflag) continue;

		sum = arr[0][3] + arr[1][2] + arr[2][1] + arr[3][0]; // 대각 Check
		if (sum == 'X' * 4 || sum == 'X' * 3 + 'T')
		{
			printf("#%d X won\n", test_case + 1);
			endflag = 1;
		}
		if (sum == 'O' * 4 || sum == 'O' * 3 + 'T')
		{
			printf("#%d O won\n", test_case + 1);
			endflag = 1;
		}

		if (endflag) continue;

		if (draw_flag) printf("#%d Draw\n", test_case + 1);
		else printf("#%d Game has not completed\n", test_case + 1);

	}

	return 0;
}