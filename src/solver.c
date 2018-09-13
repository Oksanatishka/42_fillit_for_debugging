#include <string.h>
#include "libft.h"
#include "fillit.h"
#include <stdio.h>
/*
** Backtracking implementation of the solver.
*/

int solve_map(t_map *map, t_list *list)
{
	printf("start of solve_map\n");
	int x;
	int y;
	t_etris *tetri;

	// if list NULL return 1 which means end of program
	if (list == NULL)
		return (1);
	y = 0;
	// get tetrimino from current linked list item
	tetri = (t_etris *)(list->content);
	printf("first while y = %d, map.size = %d, t.height = %d, t.width = %d\n", y, map->size, tetri->height, tetri->width);
	// while current tetrimino's height is equal or smaller than result matrix size
	while (y <= map->size - tetri->height)
	{
		x = 0;
		// while current tetrimino's width is equal or smaller than result matrix size
		while (x <= map->size - tetri->width)
		{
			printf("before place(): x = %d, y = %d\n", x, y);
			// try to put current tetrimino starting from x,y coordinate in result matrix
			// it returns "1" if there are no collissions or "0" otherwise
			if (place(tetri, map, x, y))
			{
				printf("after place()\n");
				print_map(map);
				printf("\n");
				printf("before interior solve_map()\n");
				// if current terimino was successfully placed lets try to place next tetrimino
				if (solve_map(map, list->next))
				{
					printf("end of interior solve_map: return 1\n");
					return (1);
				}
				else
				{
					// if next tetrimino failed to be placed -
					// remove previous tetrimino from result matrix
					// and try to shift previous tetrimino (right, bottom, right-bottom)
					printf("before set_piece(): x = %d, y = %d\n", x, y);
					set_piece(tetri, map, point_new(x, y), '.');
					printf("after set_piece(): \n");
					print_map(map);
					printf("\n");
				}
			}
			x++;
			printf("x++ = %d\n", x);
		}
		y++;
		printf("y++ = %d\n", y);
	}
	printf("end of solve_map: return 0\n");
	return (0);
}

/*
** Gets the rounded up sqrt of a number. Equivalent to ceil(sqrt(n)).
*/

int high_sqrt(int n)
{
	int size;

	size = 2;
	while (size * size < n)
		size++;
	return (size);
}

/*
** Tries to solve maps starting from the smallest possible size.
*/

t_map *solve(t_list *list)
{
	t_map *map;
	int size;

	// calculate initial size of result matrix, e.g 3x3 or 4x4 or 5x5 and so on
	// if there is only 1 tetrimino the calculation will be:
	// sqrt(1*4) + 1 = 3 which is 3x3
	// if there are for example 3 tetriminos the calculation will be:
	// sqrt(3*4) + 1 = 4 which is 4x4
	size = high_sqrt(ft_lstcount(list) * 4);
	printf("high_sqrt = %d\n", size);
	// init result matrix and fill it with dots
	// e.g with 3x3 it will be:
	// ...
	// ...
	// ...
	map = map_new(size);
	printf("map.size = %d\n", map->size);
	printf("print map before solve_map \n\n");
	print_map(map);

	// run while until it returns "1"
	// otherwise - increase result matrix to 1 more
	// e.g if there is not solution for 3x3 -
	// the result matrix will be increased to 4x4 to try again and so on
	while (!solve_map(map, list))
	{
		// increase size of result matrix
		size++;
		// destroy result matrix and clear memory
		free_map(map);
		// init new result matrix which will be bigger than previous for 1 unit
		// e.g if there is no solution for:
		// ...
		// ...
		// ...

		// result matrix will be increase and become
		// ....
		// ....
		// ....
		// ....
		// after that solve_map in the while loop will be called again to try solution
		map = map_new(size);
		printf("print map after map_new\n\n");
		print_map(map);
	}
	return (map);
}
