#include <stdio.h>
int main(void)
{
    int test_case;
    int T;

    setbuf(stdout, NULL);
    scanf("%d", &T);

    int arr[100];
    for (int i = 0; i < 100; i++) { arr[i] = 0; }
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
            arr[i * j] = 1;
    }

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int a;
        scanf("%d", &a);
        if (arr[a] == 1) { printf("#%d Yes\n", test_case); }
        else { printf("#%d No\n", test_case); }
    }
    return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}