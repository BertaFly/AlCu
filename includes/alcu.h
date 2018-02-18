/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inovykov <inovykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 14:35:51 by inovykov          #+#    #+#             */
/*   Updated: 2018/02/17 18:10:33 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALCU_H
# define ALCU_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_line	t_line;
typedef enum			e_outcome
{
	LOSE,
	WIN
}						t_outcome;

typedef enum			e_players
{
	LOSER,
	THE_BEST_STRONG_AI
}						t_players;

typedef enum			e_bool
{
	FALSE,
	TRUE
}						t_bool;

struct					s_line
{
	int					amount;
	t_outcome			outcome;
	t_players			player;
	t_line				*next;
};

t_bool					is_numeric(char *str);
void					game(t_line *head);

#endif
