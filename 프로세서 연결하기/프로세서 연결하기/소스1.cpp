//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//
//#pragma once
//#define false 0
//#define true 1
//#define bool int
//
//int N;
//int arr[12][12];
//
//bool availCheckUp(int i, int j)
//{
//	while (i--)
//	{
//		if (arr[i][j] != 0)
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//bool availCheckDown(int i, int j)
//{
//	i++;
//	while (i < N)
//	{
//		if (arr[i][j] != 0)
//		{
//			return false;
//		}
//		i++;
//	}
//	return true;
//}
//
//bool availCheckLeft(int i, int j)
//{
//	while (j--)
//	{
//		if (arr[i][j] != 0)
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//bool availCheckRight(int i, int j)
//{
//	j++;
//	while (j < N)
//	{
//		if (arr[i][j] != 0)
//		{
//			return false;
//		}
//		j++;
//	}
//	return true;
//}
//
//void putUp(int i, int j)
//{
//	while (i--)
//	{
//		arr[i][j] = 2;
//	}
//	return;
//}
//
//void putDown(int i, int j)
//{
//	i++;
//	while (i < N)
//	{
//		arr[i][j] = 2;
//		i++;
//	}
//	return;
//}
//
//void putLeft(int i, int j)
//{
//	while (j--)
//	{
//		arr[i][j] = 2;
//	}
//	return;
//}
//
//void putRight(int i, int j)
//{
//	j++;
//	while (j < N)
//	{
//		arr[i][j] = 2;
//		j++;
//	}
//	return;
//}
//
//int main(void)
//{
//	int T;
//	scanf("%d", &T);
//	for (int test_case = 0; test_case < T; test_case++)
//	{
//		for (int i = 0; i < 12; i++)
//			for (int j = 0; j < 12; j++)
//				arr[i][j] = 10;
//
//		scanf("%d", &N);
//		for (int i = 0; i < N; i++)
//			for (int j = 0; j < N; j++)
//				scanf("%d", &arr[i][j]);
//		for (int kk = 0; kk < 2; kk++)
//		{
//			for (int k = 3; k > -1; k--)
//			{
//				for (int i = 1; i < N - 1; i++)
//				{
//					for (int j = 1; j < N - 1; j++)
//					{
//						if (arr[i][j] != 1)
//							continue;
//
//						int cnt = 0;
//						(availCheckUp(i, j)) ? cnt : cnt++;
//						(availCheckDown(i, j)) ? cnt : cnt++;
//						(availCheckLeft(i, j)) ? cnt : cnt++;
//						(availCheckRight(i, j)) ? cnt : cnt++;
//
//						if (cnt == k)
//						{
//							//printf("%d %d %d\n", i, j, k);
//							int temp[4] = { 0,0,0,0 };
//							if (availCheckUp(i, j)) { temp[0] = i; }
//							if (availCheckDown(i, j)) { temp[1] = N - i - 1; }
//							if (availCheckLeft(i, j)) { temp[2] = j; }
//							if (availCheckRight(i, j)) { temp[3] = N - j - 1; }
//							int min = 1e9;
//							for (int a = 0; a < 4; a++)
//								if (min > temp[a] && temp[a] != 0)
//									min = temp[a];
//							if (min == temp[0]) { putUp(i, j); arr[i][j] = 3; }
//							else if (min == temp[1]) { putDown(i, j); arr[i][j] = 3; }
//							else if (min == temp[2]) { putLeft(i, j); arr[i][j] = 3; }
//							else if (min == temp[3]) { putRight(i, j); arr[i][j] = 3; }
//							/*for (int a = 0; a < N; a++)
//							{
//								for (int b = 0; b < N; b++)
//								{
//									printf("%d ", arr[a][b]);
//								}
//								printf("\n");
//							}*/
//							i = 1;
//							j = 0;
//						}
//					}
//				}
//			}
//		}
//		int cnt = 0;
//		for (int i = 0; i < N; i++)
//		{
//			for (int j = 0; j < N; j++)
//			{
//				if (arr[i][j] == 2)
//				{
//					cnt++;
//				}
//			}
//		}
//		printf("#%d %d\n", test_case + 1, cnt);
//	}
//	return 0;
//}