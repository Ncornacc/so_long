/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 16:52:50 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/05/03 16:52:51 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_move_up(t_game *game)
{
	game->player->instances[0].y -= 32;
	game->move_x--;
	game->count_moves++;
	ft_printf(BLUE"\nMoves: %d", game->count_moves);
	ft_check_map_values(game);
}

void	ft_move_down(t_game *game)
{
	game->player->instances[0].y += 32;
	game->move_x++;
	game->count_moves++;
	ft_printf(BLUE"\nMoves: %d", game->count_moves);
	ft_check_map_values(game);
}

void	ft_move_left(t_game *game)
{
	game->player->instances[0].x -= 32;
	game->move_y--;
	game->count_moves++;
	ft_printf(BLUE"\nMoves: %d", game->count_moves);
	ft_check_map_values(game);
}

void	ft_move_right(t_game *game)
{
	game->player->instances[0].x += 32;
	game->move_y++;
	game->count_moves++;
	ft_printf(BLUE"\nMoves: %d", game->count_moves);
	ft_check_map_values(game);
}
