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
	char *c = (char*)malloc(200 * sizeof(char));
	int *re = (int*)malloc(200 * sizeof(int));
	int *de = (int*)malloc(200 * sizeof(int));
	int *tmp = (int*)malloc(128 * sizeof(int));
	int *tmp2 = (int*)malloc(200 * sizeof(int));
	float y = 1;
	int exp = -1;
	int exp2 = 0;
	int fl[32];
	int i = 0;
	int j = 0;
	int k = 0;

	for (int i = 0; i < 32; i++) fl[i] = 0;
	for (int i = 0; i < 200; i++) re[i] = -1;
	for (int i = 0; i < 200; i++) de[i] = -1;
	for (int i = 0; i < 100; i++) c[i] = NULL;
	for (int i = 0; i < 128; i++) tmp[i] = -1;
	for (int i = 0; i < 200; i++) tmp2[i] = -1;

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

	while ((re[0] >= 2 || re[1] != -1) && j < 128)
	{
		tmp[j] = strdiv2(re);
		if (re[0] == 0) re++;
		j++;
	}

	if (j != 128)
	{
		tmp[j] = re[0];
		for (int i = 0; i <= j; i++)
		{
			tmp2[i] = tmp[j - i];
		}
	}

	exp = j;
	j++;

	int first = 1000;

	if (exp != 128)
	{
		if (tmp2[0] == 0)
		{
			while (j - first <= 24 && de[0] != -1 && j <= 149)
			{
				tmp2[j] = strmul2(de);
				if (tmp2[j] == 1 && first == 1000)
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
			while (j <= 23 && de[0] != -1)
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

	if (exp != 128)
	{
		if (tmp2[0] == 0)
			for (int i = 9; i < 32; i++)
			{
				if (exp < -126)
					if (tmp2[126 + i - 8] == -1) fl[i] = 0;
					else fl[i] = tmp2[126 + i - 8];
				else
					if (tmp2[-exp + i - 8] == -1) fl[i] = 0;
					else fl[i] = tmp2[-exp + i - 8];
			}
		else
			for (int i = 9; i < 32; i++)
			{
				if (tmp2[i - 8] == -1) fl[i] = 0;
				else fl[i] = tmp2[i - 8];
			}
	}
	else
	{
		for (int i = 9; i < 32; i++)
		{
			fl[i] = 0;
		}
	}

	exp = exp + 127;

	if (exp > -23 && exp < 1)
	{
		for (int i = 8; i > 0; i--)
		{
			fl[i] = 0;
		}
	}
	else
	{
		for (int i = 8; i > 0; i--)
		{
			fl[i] = exp % 2;
			exp = exp / 2;
		}
	}

	for (int i = 0; i < 32; i++)
	{
		printf("%d", fl[i]);
	}
	////////////////////////////// 10 to 2
	for (int i = 0; i < 128; i++) tmp[i] = -1;
	for (int i = 0; i < 200; i++) tmp2[i] = -1;

	exp = 0;

	for (int i = 0; i < 8; i++)
	{
		exp *= 2;
		exp += fl[i + 1];
	}

	exp = exp -= 127;


	if (exp == -127)
	{
		i = 9;
		while (fl[i] == 0)
		{
			i++;
		}
		tmp[0] = 1;
		for (int j = i - 8; j < 23; j++)
		{
			mul2to10(tmp, fl[j + 9]);
		}
		exp++;
	}
	else
	{
		i = 9;
		if (exp == 128)
		{
			while (fl[i] == 0 && i < 32)
			{
				i++;
			}
		}
		if (i != 32)
		{
			tmp[0] = 1;
			for (int i = 0; i < 23; i++)
			{
				mul2to10(tmp, fl[i + 9]);
			}
		}
	}

	exp -= 23;

	if (tmp[0] != -1)
	{
		if (exp > 0)
		{
			for (i = 0; i < exp; i++)
			{
				mul2to10(tmp, 0);
			}
			for (i = 0; i < 128; i++)
			{
				if (tmp[i] == -1) break;
			}
			for (j = 0; j < i; j++)
			{
				tmp2[j] = tmp[i - 1 - j];
			}
			i = 1000;
		}
		else if (exp < 0)
		{
			for (i = 0; i < 128; i++)
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