/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 14:36:08 by inovykov          #+#    #+#             */
/*   Updated: 2018/02/18 15:51:29 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

t_bool	is_numeric(char *str)
{
	if (!str || !*str)
		return (FALSE);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

/*
** Fill stack with a new line
**
** @param head    Head of the stack
** @param amount  Amount of matches parsed
** @param outcome Whether our bot should win or lose on current line
*/

int		fill_stack(t_line **head, int amount)
{
	t_line	*node;

	if (!(node = (t_line *)malloc(sizeof(t_line))))
		return (0);
	node->amount = amount;
	node->next = *head;
	if (!*head)
		node->outcome = WIN;
	else
	{
		if ((*head)->player == THE_BEST_STRONG_AI)
			node->outcome = WIN;
		else
			node->outcome = LOSE;
	}
	node->player = (t_players)(((node->outcome && (amount - 1) % 4)) ||
								(!node->outcome && (amount % 4)));
	*head = node;
	return (1);
}

int		read_input(int fd, t_line **head)
{
	int			amount;
	char		*line;

	line = NULL;
	while (get_next_line(fd, &line) == 1 && is_numeric(line))
	{
		amount = ft_atoi(line);
		free(line);
		if (amount < 1 || amount > 10000 || !fill_stack(head, amount))
			return (0);
	}
	amount = *head && (!line || (!fd && !*line));
	free(line);
	return (amount);
}

/*
** Main function
*/

int		main(int ac, char **av)
{
	int		fd;
	t_line	*head;
	t_line	*tmp;

	head = NULL;
	fd = ac == 1 ? 0 : open(av[1], O_RDONLY);
	if (read_input(fd, &head) == 0)
	{
		while (head)
		{
			tmp = head;
			head = (head)->next;
			free(tmp);
		}
		fd ? close(fd) : 0;
		write(2, "ERROR\n", 6);
		return (1);
	}
	game(head);
	ft_putendl("I won. Now I understand what Marvin feels");
	return (0);
}
