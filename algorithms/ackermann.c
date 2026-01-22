#include <stdio.h>

int	recursive(int m, int n)
{
	if (m == 0)
		return (n + 1);
	else if (n == 0)
		return (recursive(m - 1, 1));
	else
		return (recursive(m - 1, recursive(m, n - 1)));
}

int	iterative(int m, int n)
{
	const int	size = m + 1;
	int			stack[size];

	if (m == 0)
		return (n + 1);
	stack[m] = 1;
	while (m < size)
	{
		stack[m]--;
		m--;
		stack[m] = n + 1;
		n = 1;
		if (m == 0)
		{
			n += stack[m];
			for (m++; m < size; m++)
			{
				if (stack[m] > 0)
					break ;
			}
		}
	}
	return (n);
}

int	main(void)
{
	printf("%d\n", iterative(3, 10));
	printf("%d\n", recursive(3, 10));
}
