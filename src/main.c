/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 17:41:37 by pbondoer          #+#    #+#             */
/*   Updated: 2016/02/09 16:52:51 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "fillit.h"

/*
** Entry point for our application
*/

void printTetrisPos(t_list* list) {
	int i = 0;
	char** pos = ((t_etris*)list->content)->pos;

	while (i < ((t_etris*)list->content)->height) {
		printf("%s\n", pos[i]);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_list	*list;
	t_map	*map;

	// if number of arguments less than 1 -> print usage info
	if (argc != 2)
	{
		ft_putstr("usage: fillit input_file\n");
		return (1);
	}
	// populate linked list from text file where each linked list item contains
	// t_etris structure in void content* variable
	// argv[1] - path to file
	if ((list = read_tetri(open(argv[1], O_RDONLY))) == NULL)
	{
		ft_putstr("error\n");
		return (1);
	}
	// print first linked list item
	printf("list[0].content_size = %d\n", (int)list->content_size);
	printf("list[0].content.width = %d\n", ((t_etris*)list->content)->width);
	printf("list[0].content.height = %d\n", ((t_etris*)list->content)->height);
	printf("list[0].content.value = %c\n", ((t_etris*)list->content)->value);
	printf("list[0].content.pos\n");
	printTetrisPos(list);

	// pass linked liss to solve function which returns char** with solution
	map = solve(list);
	// print solution
	print_map(map);
	// free memory for map
	free_map(map);
	// free memory for list
	free_list(list);
	return (0);
}
