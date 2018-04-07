#include <stdio.h>
#include <string.h>

int main ()
{
	int a [4] = {0, 0, 0, 0};
	int op = 0, op1 = 0, op2 = 0;
	while (1)
	{
		scanf ("%d", &op);
		switch (op)
		{
			case 0 :
				return 0;
				break;
			case 1 :
				scanf ("%d %d", &op1, &op2);
				a[op1 % 5] = a[op1 % 5] + a[op2 % 5];
				break;
			case 2 :
				scanf ("%d %d", &op1, &op2);
				a[op1 % 5] = a[op1 % 5] - a[op2 % 5];
				break;
			case 3 :
				scanf ("%d %d", &op1, &op);
				a[op1 % 5] = op;
				break;
			case 4 :
				printf ("%d %d %d %d\n", a[0] % 256, a[1] % 256, a[2] % 256, a[3] % 256);
				break;
		}
	}
	return 0;
}
