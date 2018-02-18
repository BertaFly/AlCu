/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:10:53 by astadnik          #+#    #+#             */
/*   Updated: 2018/02/18 17:18:09 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

static void	print_board(t_line *head)
{
	char	str[10002];
	int		am;

	if (!head)
		return ;
	print_board(head->next);
	am = head->amount + 1;
	str[am--] = '\0';
	str[am] = '\n';
	while (am--)
		str[am] = '|';
	write(1, str, (size_t)head->amount + 1);
}

static void	my_turn(t_line *head)
{
	int		my_move;

	if (head->outcome == WIN)
	{
		my_move = (head->amount - 1) % 4;
		head->amount -= my_move;
	}
	else
	{
		my_move = head->amount % 4;
		head->amount -= my_move;
	}
	ft_putnbr(my_move);
	ft_putendl("");
	write(1, "===============================\n", 32);
}

static void	input(t_line *head)
{
	char	*ret;
	int		dec;

	ret = NULL;
	while (42)
	{
		write(1, "YOUR TURN: ", 11);
		get_next_line(0, &ret);
		if (!is_numeric(ret))
		{
			free(ret);
			continue ;
		}
		dec = ft_atoi(ret);
		free(ret);
		if (dec < 1 || dec > 3 || dec > head->amount)
			continue ;
		head->amount -= dec;
		break ;
	}
}

static void	play(t_line *head)
{
	if (head->player == THE_BEST_STRONG_AI)
	{
		print_board(head);
		write(1, "===============================\n", 32);
		write(1, "MY TURN: \n", 9);
		my_turn(head);
	}
	while (head->amount)
	{
		print_board(head);
		write(1, "===============================\n", 32);
		input(head);
		write(1, "===============================\n", 32);
		if (!head->amount)
			break ;
		print_board(head);
		write(1, "===============================\n", 32);
		write(1, "MY TURN: ", 9);
		my_turn(head);
	}
}

void		game(t_line *head)
{
	t_line	*tmp;

	while (head)
	{
		play(head);
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
