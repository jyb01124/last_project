#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int p = 0;
	int q = 0;
	int p_temp = 0;
	int q_temp = 0;

	int temp = 0;

	int Q = 0;
	int R = 0;

	FILE *OK;
	errno_t err_OK;

	err_OK = fopen_s(&OK, "P&Q.txt", "w");

	if (err_OK == 0)
		puts("파일오픈 성공!\n");
	else {
		puts("파일 오픈 실패\n");
		return -1;
	}

	while (1)
	{
		srand(time(NULL));

		p = (rand() % 60) + 40;
		q = (rand() % 60) + 40;

		if (p < q)
		{
			p = temp;
			p = q;
			q = temp;
		}
		else if (p == q)
		{
			Sleep(1000);
			continue;
		}

		p_temp = p;
		q_temp = q;

		while (1)
		{
			Q = p_temp / q_temp;
			R = p_temp % q_temp;

			if (R == 0)
			{
				break;
			}

			p_temp = q_temp;
			q_temp = R;
		}

		if (q_temp == 1)
		{
			break;
		}
		Sleep(1000);
	}
	fprintf(OK, "P : %d  Q : %d", p, q);
	fclose(OK);
	return 0;
}