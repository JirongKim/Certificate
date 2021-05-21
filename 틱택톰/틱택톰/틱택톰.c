#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	int test_case;
	int T;
	// freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	scanf("%d", &T); // test case의 개수를 받음.
	
	for (test_case = 1; test_case <= T; ++test_case) // T번 반복
	{
		unsigned int col_flag[4] = { 0,0,0,0 };
		unsigned int row_flag[4] = { 0,0,0,0 };
		/*
			 0,0  0,1  0,2  0,3  col0
			 1,0  1,1  1,2  1,3  col1
			 2,0  2,1  2,2  2,3  col2
			 3,0  3,1  3,2  3,3  col3
			row0 row1 row2 row3
		*/
		unsigned char arr[4][4] = { 0, }; // 16개의 변수
		unsigned int col_T = -1; // col_T변수 -1로 초기화
		unsigned int row_T = -1; // row_T변수 -1로 초기화
		unsigned int draw_flag = 1;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				scanf(" %c", &arr[i][j]);
				switch (arr[i][j])
				{
				case 'X':
					col_flag[i]--; row_flag[j]--; break; // x는 flag--
				case 'O':
					col_flag[i]++; row_flag[j]++; break; // o는 flag++
				case 'T':
					col_T = i; row_T = j; break; // T는 일단 위치 저장
				default:
					col_flag[i] = 0; row_flag[j] = 0; draw_flag = 0; break; // .은 flag 초기화
				}
			}
		}

		unsigned int endFlag = 0;

		// 대각선도 아닌경우 T에다가 임의의 값을 넣어줘야함.
		// 경우의 수는 세가지.
		// T에 X를 넣었을 때 되는경우, O를 넣었을 때 되는경우, T가 없는경우


		if (col_T != -1)  // T가 없는 경우를 먼저 짜름.
		{
			arr[col_T][row_T] = 'X'; // X를 먼저 넣어봄.
			col_flag[col_T]--;
			row_flag[row_T]--;
		}

		for (int i = 0; i < 4; i++)
		{
			if (col_flag[i] == -4 || row_flag[i] == -4) // x가 한줄에 4개면
			{
				printf("#%d X won\n", test_case);
				endFlag = 1;
				break;
			}
			if (col_flag[i] == 4 || row_flag[i] == 4) // o가 한줄에 4개면
			{
				printf("#%d O won\n", test_case);
				endFlag = 1;
				break;
			}
		}

		if (!(endFlag)) // 대각선확인하는 곳. 이미 끝난것들은 continue.
		{
			if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[2][2] == arr[3][3])
			{
				if (!(arr[0][0] == '.')) // 대각선 일치하고 '.'이 아닌경우
				{
					printf("#%d %c won\n", test_case, arr[0][0]);
					endFlag = 1;
					continue;
				}
			}
			if (arr[3][0] == arr[2][1] && arr[2][1] == arr[1][2] && arr[1][2] == arr[0][3])
			{
				if (!(arr[3][0] == '.')) // 대각선 일치하고 '.'이 아닌경우
				{
					printf("#%d %c won\n", test_case, arr[3][0]);
					endFlag = 1;
					continue;
				}
			}
		}
		else
			continue;


		///////////////////////////////////
		
		if (col_T != -1)  // T가 없는 경우를 먼저 짜름.
		{
			arr[col_T][row_T] = 'O'; // 다음은 T에 O를 넣어봄
			col_flag[col_T] += 2; // 위에서 T에 X를 넣어서 관련 Flag에 --를 해줬기 때문에 +2를 해줌.
			row_flag[row_T] += 2;
		}

		for (int i = 0; i < 4; i++)
		{
			if (col_flag[i] == -4 || row_flag[i] == -4) // x가 한줄에 4개면
			{
				printf("#%d X won\n", test_case);
				endFlag = 1;
				break;
			}
			if (col_flag[i] == 4 || row_flag[i] == 4) // o가 한줄에 4개면
			{
				printf("#%d O won\n", test_case);
				endFlag = 1;
				break;
			}
		}

		if (!(endFlag)) // 대각선확인 이미 끝난것들은 continue.
		{
			if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[2][2] == arr[3][3])
			{
				if (!(arr[0][0] == '.')) // 대각선 일치하고 '.'이 아닌경우
				{
					printf("#%d %c won\n", test_case, arr[0][0]);
					endFlag = 1;
					continue;
				}
			}
			if (arr[3][0] == arr[2][1] && arr[2][1] == arr[1][2] && arr[1][2] == arr[0][3])
			{
				if (!(arr[3][0] == '.')) // 대각선 일치하고 '.'이 아닌경우
				{
					printf("#%d %c won\n", test_case, arr[3][0]);
					endFlag = 1;
					continue;
				}
			}
		}
		else
			continue;


		


		if(draw_flag)
			printf("#%d Draw\n", test_case);
		else
			printf("#%d Game has not completed\n", test_case);

	}
	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}