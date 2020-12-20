#include <stdio.h>
#include <stdlib.h>

int	ft_fibonacci(int index)
{
//	static int a =0;
//	a++;
//	printf("count %d\n", a);
/*	if (index < 0)
		return (-1);
	if (index == 0)
		return (0);*/
	if (index <= 1)
		return (1);
	else
		return (ft_fibonacci(index - 1) + ft_fibonacci(index - 2));
}

int main(int ac, char **av)
{
	printf("%d\n", ft_fibonacci(atoi(av[1])));
}
