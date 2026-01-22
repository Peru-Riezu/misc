#include <stdio.h>

unsigned int	memoization(unsigned int x)
{
	static unsigned int	minus_two;
	unsigned int		minus_one;
	unsigned int		res;

	if (x < 2)
	{
		minus_two = 0;
		return (x);
	}
	minus_one = memoization(x - 1);
	res = minus_one + minus_two;
	minus_two = minus_one;
	return (res);
}

unsigned int	recursive(unsigned int x)
{
	if (x < 2)
		return (x);
	return (recursive(x - 1) + recursive(x - 2));
}

unsigned int	iterative(unsigned int x)
{
	unsigned int	i;
	unsigned int	past;
	unsigned int	present;

	past = 1;
	present = 0;
	for (i = 0; i < x; i++)
	{
		present += past;
		past = present - past;
	}
	return (present);
}

int	main(void)
{
	printf("%d\n", iterative(112));
	printf("%d\n", memoization(112));
	printf("%d\n", recursive(112));
}
