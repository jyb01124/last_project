#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char change(char a);
int unchange(char a);
int RSA_encrypt(int value, int e, int n);
int RSA_decrypt(int value, int d, int n);

int main(int argc, char *argv[])
{

	FILE *in;
	FILE *out;

	int count = 0;
	int cnt = 0;
	int value = 0;
	int Out = 0;
	char bin2hex[2] = { 0 };
	char hex_str[8] = { 0 };
	char ch = 0;

	errno_t err_in;
	errno_t err_out;

	int e = argv[2];
	int n = argv[3];

	err_in = fopen_s(&in, argv[1], "rb");
	err_out = fopen_s(&out,"BIN2RSA.txt", "w");

	if (err_in == 0)
		puts("파일오픈 성공!\n");
	else {
		puts("파일 오픈 실패\n");
		return -1;
	}

	if (err_out == 0)
		puts("파일오픈 성공!\n");
	else {
		puts("파일 오픈 실패\n");
		return -1;
	}

	while(1)
	{
		ch = fgetc(in); 
		if (ch == EOF)
		{
			break;
		}

		if (count == 8)
		{
			count = 0;
			value = 0;
			cnt = 0;
			Out = 0;

			while (cnt<8)
			{
				value += unchange(hex_str[cnt])*(int)(pow((double)16, (double)(7 - cnt)));
				cnt++;
			}

			Out = RSA(value, e, n);
			fprintf(out, "%d\n", Out);
		}

		bin2hex[0] = ch / 16;
		hex_str[count] = change(bin2hex[0]);
		count++;

		bin2hex[1] = ch % 16;
		hex_str[count] = change(bin2hex[1]);
		count++;

	}

	fclose(in);
	fclose(out);
	return 0;

}


char change(char a)
{
	switch (a)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		return a + 48;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		return a + 55;
	}
}

int unchange(char a)
{
	switch (a)
	{
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return a - 48;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
		return a - 55;
	}
}

int RSA_encrypt(int value, int e, int n)
{
	int P_M = 0;
	int mod = 0;
	
	P_M = (int)(pow((double)value, (double)e));
	mod = P_M % e;

	return mod;
}

int RSA_decrypt(int value, int d, int n)
{
	int Q_M = 0;
	int M = 0;

	Q_M = (int)(pow((double)value, (double)d));
	M = Q_M % n;

	return M;
}