# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>


int	stringlenght(char *string)
{
	int	size;

	if (!string)
		return (0);
	size = 0;
	while (string[size])
		size++;
	return (size);
}

char *string_dup(char *string, int size)
{
	char *dup;
	int	index;

	if (!string || !size)
		return (NULL);
	dup = malloc((size + 1) * sizeof(char));
	if (!dup)
		exit(1);
	index = 0;
	while (string[index])
	{
		dup[index] = string[index];
		index++;
	}
	dup[index] = '\0';
	return (dup);
}

//------------string len
int	main(void)
{
	char *string = "isso e um teste";
	char *dup;
	int	size;

	size = stringlenght(string);
	printf("String: %s    Len: %d\n\n\n", string, stringlenght(string));

	dup = string_dup(string, size);
	printf("Original: %s\nDup: %s\n", string, dup);
}

