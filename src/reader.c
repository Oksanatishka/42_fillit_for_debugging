/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 17:43:27 by pbondoer          #+#    #+#             */
/*   Updated: 2016/02/09 16:53:44 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "fillit.h"
#include <stdio.h>

/*
** Utility function to get min-max values for get_piece.
*/

void	min_max(char *str, t_point *min, t_point *max)
{
	int i;

	i = 0;
	// find the smallest x coordinate and biggest y coordinate of tetrimino
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if (i / 5 < min->y)
				min->y = i / 5;
			if (i / 5 > max->y)
				max->y = i / 5;
			if (i % 5 < min->x)
				min->x = i % 5;
			if (i % 5 > max->x)
				max->x = i % 5;
		}
		i++;
	}
	printf("str = \n%s\n, min.x = %d, min.y = %d, max.x = %d, max.y = %d\n", str, min->x, min->y, max->x, max->y);
}

/*
** Reads a piece from a valid chunk, allocates a structure and populates it.
*/

// converts tetrimino from for example:
// .##.
// .#..
// .#..
// ....

// to

// ##
// #.
// #.
t_etris	*get_piece(char *str, char value)
{
	printf("start get_piece()\n");
	t_point		*mi;
	t_point		*max;
	char		**pos;
	int			i;
	t_etris		*tetri;

	// init point structure with x = 3, y = 3
	mi = point_new(3, 3);
	// init point structure with x = 0, y = 0
	max = point_new(0, 0);
	// find min x, y and max x,y from current tetrimino
	// e.g for:
	// .##.
	// .#..
	// .#..
	// ....
	// result will be: min.x = 1, min.y = 0, max.x = 2, max.y = 2
	min_max(str, mi, max);
	// allocate memory for pos, basically height of tetrimino
	pos = ft_memalloc(sizeof(char *) * (max->y - mi->y + 1));
	i = 0;
	// fill row by row tetrimino without not needed "."
	// e.g
	// .##.
	// .#..
	// .#..
	// ....

	// to

	// ##
	// #.
	// #.

	// it goes through each row in the terimino and copies only needed characters to "pos" array
	while (i < max->y - mi->y + 1)
	{
		pos[i] = ft_strnew(max->x - mi->x + 1);
		ft_strncpy(pos[i], str + (mi->x) + (i + mi->y) * 5, max->x - mi->x + 1);
		printf("pos[i] = %s, i = %d\n", pos[i], i);
		i++;
	}
	// init new tetris structure
	// e.g
	// pos =
	// 		 ##
	// 		 #.
	// 		 #.
	// width = 2, heighr = 3, value = 'A'
	tetri = tetris_new(pos, max->x - mi->x + 1, max->y - mi->y + 1, value);
	// delete memory of mi and max variables
	ft_memdel((void **)&mi);
	ft_memdel((void **)&max);
	// return our new tetri structure
	return (tetri);
}

/*
** Checks connection counts, if we have 6 or 8 connections, the tetrimino is
** valid. Otherwise, our tetrimino is not contiguous.
*/

int		check_connection(char *str)
{
	int block;
	int i;

	block = 0;
	i = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if ((i + 1) < 20 && str[i + 1] == '#')
				block++;
			if ((i - 1) >= 0 && str[i - 1] == '#')
				block++;
			if ((i + 5) < 20 && str[i + 5] == '#')
				block++;
			if ((i - 5) >= 0 && str[i - 5] == '#')
				block++;
		}
		i++;
	}
	return (block == 6 || block == 8);
}

/*
** Checks character counts and that chunk format is valid.
*/

int		check_counts(char *str, int count)
{
	int i;
	int blocs;

	blocs = 0;
	i = 0;
	while (i < 20)
	{
		if (i % 5 < 4)
		{
			if (!(str[i] == '#' || str[i] == '.'))
				return (1);
			if (str[i] == '#' && ++blocs > 4)
				return (2);
		}
		else if (str[i] != '\n')
			return (3);
		i++;
	}
	if (count == 21 && str[20] != '\n')
		return (4);
	if (!check_connection(str))
		return (5);
	return (0);
}

/*
** Read tetriminos from fd and put them in a list.
** We use 21 sized reads to read piece by piece since there are
** 4 lines made of 4 chars (+ newline) = 20 chars + sep. newline = 21 chars
*/

t_list	*read_tetri(int fd)
{
	printf("start read_tetri()\n");
	char	*buf;
	int		count;
	t_list	*list;
	t_etris	*tetris;
	char	cur;

	buf = ft_strnew(21);
	list = NULL;
	cur = 'A';
	while ((count = read(fd, buf, 21)) >= 20)
	{
		if (check_counts(buf, count) != 0
				|| (tetris = get_piece(buf, cur++)) == NULL)
		{
			ft_memdel((void **)&buf);
			return (free_list(list));
		}
		ft_lstadd(&list, ft_lstnew(tetris, sizeof(t_etris)));
		ft_memdel((void **)&tetris);
	}
	ft_memdel((void **)&buf);
	if (count != 0)
		return (free_list(list));
	ft_lstrev(&list);
	return (list);
}
