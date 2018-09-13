#include "fillit.h"
#include "libft.h"

/*
** Frees an allocated map structure.
*/

void free_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->size)
	{
		ft_memdel((void **)&(map->array[i]));
		i++;
	}
	ft_memdel((void **)&(map->array));
	ft_memdel((void **)&map);
}

/*
** Prints an allocated map structure to standard output.
*/

void print_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->size)
	{
		ft_putstr(map->array[i]);
		ft_putchar('\n');
		i++;
	}
}

/*
** Allocates a new map structure with specified size.
*/

t_map *map_new(int size)
{
	t_map *map;
	int i;
	int j;
	// allocate memory for t_map structure
	map = (t_map *)ft_memalloc(sizeof(t_map));
	// set size variable in the strucre
	map->size = size;
	// set array variable in the structure with memory of size
	// basically it will contain array of arrays of characters, e.g if size = 3 array field will become
	// ...
	// ...
	// ...
	map->array = (char **)ft_memalloc(sizeof(char *) * size);
	i = 0;
	while (i < size)
	{
		map->array[i] = ft_strnew(size);
		j = 0;
		while (j < size)
		{
			map->array[i][j] = '.';
			j++;
		}
		i++;
	}
	return (map);
}

/*
** Places a tetrimino on map at specified position, checking if the placement is
** possible.
*/

int place(t_etris *tetri, t_map *map, int x, int y)
{
	int i;
	int j;

	i = 0;
	// go through tetrimino row by row, e.g
	// #.
	// #.
	// ##
	// and try to find if there are no colissions in the result matrix

	// for example if result matrix has following:
	// .##
	// .##
	// ...
	// and our tetrimino is:
	// #.
	// #.
	// ##

	// and x = 0 and y = 0
	// then we can clearly see that
	// we can insert it in the left top corner
	while (i < tetri->width)
	{
		j = 0;
		while (j < tetri->height)
		{
			if (tetri->pos[j][i] == '#' && map->array[y + j][x + i] != '.')
				return (0);
			j++;
		}
		i++;
	}
	// if there are no colissions
	// add tetrimino to the result matrix starting from x,y coordinate
	set_piece(tetri, map, point_new(x, y), tetri->value);
	return (1);
}

/*
** Sets a tetrimino on a map at a position with the specified character.
** To place, call with c=tetri->value. To remove, call with c='.'.
*/

// for example if result matrix (map) has following:
// .##
// .##
// ...
// and our tetrimino(tetri) is:
// #.
// #.
// ##

// and point structure has x = 0 and y = 0
// then we can clearly see that
// we can insert it in the left top corner using character c (can be 'A', 'B', 'C' and so on)
// so result of map will be:
// BAA
// BAA
// BB.
void set_piece(t_etris *tetri, t_map *map, t_point *point, char c)
{
	int i;
	int j;

	i = 0;
	while (i < tetri->width)
	{
		j = 0;
		while (j < tetri->height)
		{
			if (tetri->pos[j][i] == '#')
				map->array[point->y + j][point->x + i] = c;
			j++;
		}
		i++;
	}
	ft_memdel((void **)&point);
}
