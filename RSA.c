#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int coprime(int p_temp, int q_temp);
int RSA_e_maker(int p, int q);
int RSA_d_maker(int e, int pi);

int main(int argc, char *argv[])
{
	int p = 0;
	int q = 0;
	int e = 0;
	int d = 0;
	int pi = 0;

	int temp = 0;

	int accept = 0;

	FILE *OK;
	errno_t err_OK;

	err_OK = fopen_s(&OK, "RSA.txt", "w");

	if (err_OK != 0)
	{
		return -1;
	}

	while (1)
	{
		srand(time(NULL));

		p = (rand() % 60) + 40;
		q = (rand() % 60) + 40;

		if (p < q)
		{
			temp = p;
			p = q;
			q = temp;
		}
		else if (p == q)
		{
			Sleep(1000);
			continue;
		}

		accept = coprime(p, q);

		if (accept == 1)
		{
			break;
		}
		Sleep(1000);
	}

	pi = (p - 1) * (q - 1);
	e = RSA_e_maker(p, q);
	d = RSA_d_maker(e, pi);

	fprintf(OK, "P,Q,E,D,PI \n", p, q, e, d, pi);
	fprintf(OK, "%d,%d,%d,%d,%d", p, q, e, d, pi);

	fclose(OK);

	return 0;
}

int coprime(int p_temp, int q_temp)
{
	int p = 0;
	int q = 0;

	int Q = 0;
	int R = 0;

	p = p_temp;
	q = q_temp;

	while (1)
	{
		Q = p / q;
		R = p % q;

		if (R == 0)
		{
			break;
		}

		p = q;
		q = R;
	}

	if (q == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int RSA_e_maker(int p, int q)
{
	int n = 0;
	int pi = 0;
	int e = 0;
	int accept = 0;

	n = p * q;
	pi = (p - 1) * (q - 1);

	while (1)
	{
		srand(time(NULL));

		e = (rand() % (n - 1)) + 1;

		if (e < pi)
		{
			accept = coprime(pi, e);
		}
		else
		{
			Sleep(1000);
			continue;
		}

		if (accept == 1)
		{
			return e;
		}

	}
}

int RSA_d_maker(int e, int pi)
{
	int d = 2;
	int calc = 0;

	while (1)
	{
		calc = (d*e) % pi;

		if (calc == 1)
		{
			break;
		}

		d++;
	}
	return d;
}