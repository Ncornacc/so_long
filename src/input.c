/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                          :+:    :+:              */
/*                                                     +:+                    */
/*   By: ncornacc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:55:43 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/04/18 14:55:46 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

//ASSIGNMENT OF KEY_STOKES TO CORRISPECTIVE KEY FUNCTIONS

void	ft_movement(mlx_key_data_t key_stroke, t_game *game)
{
	if ((key_stroke.key == MLX_KEY_W || key_stroke.key == MLX_KEY_UP)
        && key_stroke.action == MLX_PRESS)
		ft_movement_up(game);
	if ((key_stroke.key == MLX_KEY_S || key_stroke.key == MLX_KEY_DOWN)
		&& key_stroke.action == MLX_PRESS)
		ft_movement_down(game);
	if ((key_stroke.key == MLX_KEY_A || key_stroke.key == MLX_KEY_LEFT)
		&& key_stroke.action == MLX_PRESS)
		ft_movement_left(game);
	if ((key_stroke.key == MLX_KEY_D || key_stroke.key == MLX_KEY_RIGHT)
		&& key_stroke.action == MLX_PRESS)
		ft_movement_right(game);
	if ((key_stroke.key == MLX_KEY_ESCAPE || key_stroke.key == MLX_KEY_Q)
		&& key_stroke.action == MLX_PRESS)
		ft_free_game(game);
}

//ALL THE MOVEMENT FUNCTIONS COUNT THE COLLECTABLES AS WELL AND CHECK IF WE CAN WIN

void	ft_movement_up(t_game *game)
{	
	if (game->map[game->move_x - 1][game->move_y] != '1'
		&& (game->map[game->move_x - 1][game->move_y] != 'E'
		|| game->count_collectables == 0))
	{
		game->map[game->move_x][game->move_y] = '0';
		if (game->map[game->move_x - 1][game->move_y] == 'C')
			game->count_collectables--;
		if (game->map[game->move_x - 1][game->move_y] == 'E'
			&& game->count_collectables == 0)
			ft_open_exit(game);
		else
		{
			game->map[game->move_x - 1][game->move_y] = 'P';
			ft_draw_map(game->mlx, game);
			game->count_moves++;
			ft_printf(BLUE"\nMoves: %d", game->count_moves);
		}
	}
}


void	ft_movement_down(t_game *game)
{
	if (game->map[game->move_x + 1][game->move_y] != '1'
		&& (game->map[game->move_x + 1][game->move_y] != 'E'
		|| game->count_collectables == 0))
	{
		game->map[game->move_x][game->move_y] = '0';
		if (game->map[game->move_x + 1][game->move_y] == 'C')
			game->count_collectables--;
		if (game->map[game->move_x + 1][game->move_y] == 'E'
			&& game->count_collectables == 0)
			ft_open_exit(game);
		else
		{
			game->map[game->move_x + 1][game->move_y] = 'P';
			ft_draw_map(game->mlx, game);
			game->count_moves++;
			ft_printf(BLUE"\nMoves: %d", game->count_moves);
		}
	}
}


void	ft_movement_left(t_game *game)
{
	if (game->map[game->move_x][game->move_y - 1] != '1'
		&& (game->map[game->move_x][game->move_y - 1] != 'E'
		|| game->count_collectables == 0))
	{
		game->map[game->move_x][game->move_y] = '0';
		if (game->map[game->move_x][game->move_y - 1] == 'C')
			game->count_collectables--;
		if (game->map[game->move_x][game->move_y - 1] == 'E'
			&& game->count_collectables == 0)
			ft_open_exit(game);
		else
		{
			game->map[game->move_x][game->move_y - 1] = 'P';
			ft_draw_map(game->mlx, game);
			game->count_moves++;
			ft_printf(BLUE"\nMoves: %d", game->count_moves);
		}
	}
}


void	ft_movement_right(t_game *game)
{
	if (game->map[game->move_x][game->move_y + 1] != '1'
		&& (game->map[game->move_x][game->move_y + 1] != 'E'
		|| game->count_collectables == 0))
	{
		game->map[game->move_x][game->move_y] = '0';
		if (game->map[game->move_x][game->move_y + 1] == 'C')
			game->count_collectables--;
		if (game->map[game->move_x][game->move_y + 1] == 'E'
			&& game->count_collectables == 0)
			ft_open_exit(game);
		else
		{
			game->map[game->move_x][game->move_y + 1] = 'P';
			ft_draw_map(game->mlx, game);
			game->count_moves++;
			ft_printf(BLUE"\nMoves: %d", game->count_moves);
		}
	}
}