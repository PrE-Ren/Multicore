#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int banolim(int *a, int b, int c)
{
	int carry = 1;
	for (int i = b; i >= c; i--)
	{
		a[i] = a[i] + carry;
		if (a[i] == 2)
		{
			a[i] = 0;
			carry = 1;
		}
		else carry = 0;
	}
	return carry;
}

int div10by2(int *a, int belowzero)
{
	int carry = 0;
	int i = 0;
	while (a[i] == -2 || a[i] == 0) i++;
	int k = i;
	while (a[i] != -1)
	{
		int tmp = carry;
		carry = (a[i] + tmp * 10) % 2;
		//printf("%d carry", carry);
		a[i] = (a[i] + tmp * 10) / 2;
		i++;
	}
	if (a[k] == 0 && i < belowzero) a[k] = -2;
	if (carry == 1) a[i] = 5;
}


int mul2to10(int *a, int x)
{
	int carry = x;
	int i = 0;
	while (a[i] != -1)
	{
		a[i] = a[i] * 2 + carry;
		if (a[i] >= 10)
		{
			carry = 1;
			a[i] -= 10;
		}
		else carry = 0;
		i++;
	}
	if (carry == 1) a[i] = carry;
}

int strdiv2(int* a)
{
	int i = 0, rem = 0;
	while (a[i] != -1)
	{
		a[i] += rem * 10;
		rem = a[i] % 2;
		a[i] = a[i] / 2;
		i++;
	}
	return rem;
}

int strmul2(int* a)
{
	int i = 0, carry = 0;
	int max;

	while (a[i] != -1)
	{
		i++;
	}

	max = i - 1;
	//printf("%d max", max);
	while (i > 0)
	{
		i--;
		a[i] = 2 * a[i] + carry;
		if (a[i] >= 10)
		{
			a[i] -= 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
	}
	//printf("%d curr", a[max]);
	if (a[max] == 0) a[max] = -1;
	return carry;
}

void main(void)
{

	float f = 0;
	char *c = (char*)malloc(1600 * sizeof(char));
	int *re = (int*)malloc(1600 * sizeof(int));
	int *de = (int*)malloc(1600 * sizeof(int));
	int *tmp = (int*)malloc(1024 * sizeof(int));
	int *tmp2 = (int*)malloc(1600 * sizeof(int));
	float y = 1;
	int exp = -1;
	int exp2 = 0;
	int fl[64];
	int i = 0;
	int j = 0;
	int k = 0;

	for (int i = 0; i < 64; i++) fl[i] = 0;
	for (int i = 0; i < 1600; i++) re[i] = -1;
	for (int i = 0; i < 1600; i++) de[i] = -1;
	for (int i = 0; i < 1600; i++) c[i] = NULL;
	for (int i = 0; i < 1024; i++) tmp[i] = -1;
	for (int i = 0; i < 1600; i++) tmp2[i] = -1;

	scanf("%s", c);

	if (c[0] == '-')
	{
		fl[0] = 1;
		k++;
	}

	while (c[i + k] != '.' && c[i + k] != NULL)
	{
		re[i] = (int)c[i + k] - 48;
		i++;
	}

	i++;

	while (c[i + k] != NULL)
	{
		de[j] = (int)c[i + k] - 48;
		j++;
		i++;
	}

	j = 0;

	while ((re[0] >= 2 || re[1] != -1) && j < 1024)
	{
		tmp[j] = strdiv2(re);
		if (re[0] == 0) re++;
		j++;
	}

	if (j != 1024)
	{
		tmp[j] = re[0];
		for (int i = 0; i <= j; i++)
		{
			tmp2[i] = tmp[j - i];
		}
	}

	exp = j;
	j++;

	int first = 10000;

	if (exp != 1024)
	{
		if (tmp2[0] == 0)
		{
			while (j - first <= 53 && de[0] != -1 && j <= 1074)
			{
				tmp2[j] = strmul2(de);
				if (tmp2[j] == 1 && first == 10000)
				{
					exp = -j;
					first = j;
				}
				j++;
			}

			if (de[0] > 5 || (de[0] == 5 && de[1] != -1))
			{
				int carry = banolim(tmp2, j - 1, first);
				if (carry == 1)
				{
					exp++;
					if (exp == 0)
						tmp2[0] = 1;
				}
			}

		}
		else
		{
			while (j <= 52 && de[0] != -1)
			{
				tmp2[j] = strmul2(de);
				j++;
			}

			if (de[0] > 5 || (de[0] == 5 && de[1] != -1))
			{
				int carry = banolim(tmp2, j - 1, 1);
				if (carry == 1)
				{
					exp++;
				}
			}
		}
	}

	int l = 9;

	if (exp != 1024)
	{
		if (tmp2[0] == 0)
			for (int i = 12; i < 64; i++)
			{
				if (exp < -1022)
					if (tmp2[126 + i - 11] == -1) fl[i] = 0;
					else fl[i] = tmp2[1022 + i - 11];
				else
					if (tmp2[-exp + i - 11] == -1) fl[i] = 0;
					else fl[i] = tmp2[-exp + i - 11];
			}
		else
			for (int i = 12; i < 64; i++)
			{
				if (tmp2[i - 11] == -1) fl[i] = 0;
				else fl[i] = tmp2[i - 11];
			}
	}
	else
	{
		for (int i = 12; i < 64; i++)
		{
			fl[i] = 0;
		}
	}

	exp = exp + 1023;

	if (exp > -52 && exp < 1)
	{
		for (int i = 11; i > 0; i--)
		{
			fl[i] = 0;
		}
	}
	else
	{
		for (int i = 11; i > 0; i--)
		{
			fl[i] = exp % 2;
			exp = exp / 2;
		}
	}

	for (int i = 0; i < 64; i++)
	{
		printf("%d", fl[i]);
	}
	////////////////////////////// 10 to 2
	for (int i = 0; i < 1024; i++) tmp[i] = -1;
	for (int i = 0; i < 1600; i++) tmp2[i] = -1;

	exp = 0;

	for (int i = 0; i < 11; i++)
	{
		exp *= 2;
		exp += fl[i + 1];
	}

	exp = exp -= 1023;


	if (exp == -1023)
	{
		i = 12;
		while (fl[i] == 0)
		{
			i++;
		}
		tmp[0] = 1;
		for (int j = i - 11; j < 52; j++)
		{
			mul2to10(tmp, fl[j + 12]);
		}
		exp++;
	}
	else
	{
		i = 12;
		if (exp == 1024)
		{
			while (fl[i] == 0 && i < 64)
			{
				i++;
			}
		}
		if (i != 64)
		{
			tmp[0] = 1;
			for (int i = 0; i < 52; i++)
			{
				mul2to10(tmp, fl[i + 12]);
			}
		}
	}

	exp -= 52;

	if (tmp[0] != -1)
	{
		if (exp > 0)
		{
			for (i = 0; i < exp; i++)
			{
				mul2to10(tmp, 0);
			}
			for (i = 0; i < 1024; i++)
			{
				if (tmp[i] == -1) break;
			}
			for (j = 0; j < i; j++)
			{
				tmp2[j] = tmp[i - 1 - j];
			}
			i = 10000;
		}
		else if (exp < 0)
		{
			for (i = 0; i < 1024; i++)
			{
				if (tmp[i] == -1) break;
			}
			for (j = 0; j < i; j++)
			{
				tmp2[j] = tmp[i - 1 - j];
			}

			for (k = exp; k < 0; k++)
			{
				div10by2(tmp2, i - 1);
			}
		}
	}

	l = 0;
	printf("\n");
	if (fl[0] == 1) printf("-");
	if (tmp[0] == -1) printf("inf");
	else
	{
		while (tmp2[l] == 0 && l < i - 1) l++;
		while (tmp2[l] != -1)
		{
			if (tmp2[l] != -2) printf("%d", tmp2[l]);
			if (l == i - 1 && tmp2[l + 1] != -1) printf(".");
			l++;
		}
	}
	printf("\n");

}