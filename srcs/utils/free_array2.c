#include "utils.h"

void	free_array2(void **array)
{
	size_t	index;

	index = 0;
	if (!array)
		return ;
	while (array[index] != NULL)
	{
		free(array[index]);
		index++;
	}
	free(array);
}
