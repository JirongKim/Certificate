#define _CRT_SECURE_NO_WARNINGS
#define rint register int

#include <stdio.h>

int arr[12][12];
int N;

int cntUP(int i, int j);
int cntDOWN(int i, int j);
int cntLEFT(int i, int j);
int cntRIGHT(int i, int j);
int upMark(int i, int j);
int downMark(int i, int j);
int leftMark(int i, int j);
int rightMark(int i, int j);

int main(void)
{
	int rot_x[144];
	int rot_y[144];
	int countX = 0;
	int countY = 0;

	int T;
	scanf(" %d", &T);
	for (rint test_case = 0; test_case < T; test_case++)
	{
		countX = countY = 0;

		scanf(" %d", &N);
		for (rint i = 0; i < N; i++)
		{
			for (rint j = 0; j < N; j++)
			{
				scanf(" %d", &arr[i][j]);
				if (arr[i][j] == 1 && i > 0 && i < N - 1 && j > 0 && j < N - 1)
				{
					rot_x[countX++] = i;
					rot_y[countY++] = j;
				}
			}
		}

		int cnt = 0;
		for (rint num = 1; num <= 4; num++)
		{
			for (rint i = 0; i < countX; i++)
			{
				int tempCnt = 0;
				if (rot_x[i] == 0) { continue; }
				int temp[4] = { 0,0,0,0 };
				temp[0] = cntUP(rot_x[i], rot_y[i]);
				temp[1] = cntDOWN(rot_x[i], rot_y[i]);
				temp[2] = cntLEFT(rot_x[i], rot_y[i]);
				temp[3] = cntRIGHT(rot_x[i], rot_y[i]);

				for (rint j = 0; j < 4; j++)
				{
					if (temp[j] != 0)
						tempCnt++;
					if (temp[j] == 0)
						temp[j] = 100;
				}

				//printf("x : %d, y = %d, up : %d, down : %d, left : %d, right : %d\n", rot_x[i], rot_y[i], up, down, left, right);
				if (tempCnt != num) { continue; }

				int minJ = 0;
				for (rint j = 0; j < 4; j++)
				{
					if (temp[minJ] > temp[j])
						minJ = j;
				}

				switch (minJ)
				{
				case 0:
					cnt += upMark(rot_x[i], rot_y[i]);
					break;
				case 1:
					cnt += downMark(rot_x[i], rot_y[i]);
					break;
				case 2:
					cnt += leftMark(rot_x[i], rot_y[i]);
					break;
				case 3:
					cnt += rightMark(rot_x[i], rot_y[i]);
					break;
				default:
					break;
				}
				i = -1;
			}
		}
		printf("#%d %d\n", test_case + 1, cnt);
	}

	return 0;
}

int cntUP(int i, int j)
{
	int cnt = 0;
	for (rint k = i - 1; k >= 0; k--)
	{
		if (arr[k][j] == 1)
		{
			return 0;
		}
		cnt++;
	}
	return cnt;
}

int upMark(int i, int j)
{
	int cnt = 0;
	for (rint k = i - 1; k >= 0; k--)
	{
		arr[k][j] = 1;
		cnt++;
	}
	return cnt;
}

int cntDOWN(int i, int j)
{
	int cnt = 0;
	for (rint k = i + 1; k <= N - 1; k++)
	{
		if (arr[k][j] == 1)
		{
			return 0;
		}
		cnt++;
	}
	return cnt;
}

int downMark(int i, int j)
{
	int cnt = 0;
	for (rint k = i + 1; k <= N - 1; k++)
	{
		arr[k][j] = 1;
		cnt++;
	}
	return cnt;
}

int cntLEFT(int i, int j)
{
	int cnt = 0;
	for (rint k = j - 1; k >= 0; k--)
	{
		if (arr[i][k] == 1)
		{
			return 0;
		}
		cnt++;
	}
	return cnt;
}

int leftMark(int i, int j)
{
	int cnt = 0;
	for (rint k = j - 1; k >= 0; k--)
	{
		arr[i][k] = 1;
		cnt++;
	}
	return cnt;
}

int cntRIGHT(int i, int j)
{
	int cnt = 0;
	for (rint k = j + 1; k <= N - 1; k++)
	{
		if (arr[i][k] == 1)
		{
			return 0;
		}
		cnt++;
	}
	return cnt;
}

int rightMark(int i, int j)
{
	int cnt = 0;
	for (rint k = j + 1; k <= N - 1; k++)
	{
		arr[i][k] = 1;
		cnt++;
	}
	return cnt;
}