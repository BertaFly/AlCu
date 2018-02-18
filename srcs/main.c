/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 14:36:08 by inovykov          #+#    #+#             */
/*   Updated: 2018/02/18 12:25:17 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

t_bool	is_numeric(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
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

void	fill_stack(t_line **head, int amount)
{
	t_line	*node;

	node = (t_line *)malloc(sizeof(t_line));
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
}

/*
** Main function
*/

int		gnl_free(const int fd, char **line)
{
	ft_strdel(line);
	return (get_next_line(fd, line));
}

int		read_input(int fd, t_line **head, char **line)
{
	static int	count = 0;
	int			amount;

	while ((gnl_free(fd, line)) > 0 && (count += ft_strlen(*line) > 0))
	{
		if (!*line || !is_numeric(*line) || !(amount = ft_atoi(*line)))
			break ;
		else
		{
			if (amount >= 1 && amount <= 10000)
				fill_stack(head, amount);
			else if (fd && gnl_free(fd, line) == 0)
				return (1);
			else
				break ;
		}
	}
	if (*line && ((ft_strlen(*line) == 0 && !count && !fd) || (fd && count)))
		return (0);
	return (1);
}

int		main(int ac, char **av)
{
	int		fd;
	t_line	*head;
	t_line	*tmp;
	char	*line;

	head = NULL;
	line = NULL;
	fd = ac == 1 ? 0 : open(av[1], O_RDONLY);
	if (fd == -1 || read_input(fd, &head, &line) == 0)
	{
		ft_strdel(&line);
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
	ft_strdel(&line);
	game(head);
	ft_putendl("Bot won. again. You really suck. Try harder next time");
	return (0);
}
