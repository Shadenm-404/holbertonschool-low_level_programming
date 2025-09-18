#include "main.h"

/**
 * alloc_grid - returns a pointer to a 2D array of integers
 * @width:  number of columns (must be > 0)
 * @height: number of rows (must be > 0)
 *
 * Return: pointer to newly allocated 2D grid initialized to 0,
 *         or NULL on failure / invalid params
 */
int **alloc_grid(int width, int height)
{
	int **grid;
	int i, j;

	if (width <= 0 || height <= 0)
		return (NULL);

	grid = (int **)malloc(height * sizeof(int *));
	if (grid == NULL)
		return (NULL);

	for (i = 0; i < height; i++)
	{
		grid[i] = (int *)malloc(width * sizeof(int));
		if (grid[i] == NULL)
		{
			/* free previously allocated rows to avoid leaks */
			while (i--)
				free(grid[i]);
			free(grid);
			return (NULL);
		}

		for (j = 0; j < width; j++)
			grid[i][j] = 0;
	}

	return (grid);
}
