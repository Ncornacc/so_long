/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 16:53:16 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/05/03 16:53:21 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_check_map_values(t_game *game)
{
	if (game->map[game->move_x][game->move_y] == 'C')
	{
		game->count_collectables--;
		game->map[game->move_x][game->move_y] = '0';
		mlx_image_to_window(game->mlx, game->floor,
			game->move_y * 32, game->move_x * 32);
		if (game->orientation == 0)
			ft_player_right(game);
		else
			ft_player_left(game);
		return ;
	}
	if (game->map[game->move_x][game->move_y] == 'E' &&
		game->count_collectables == 0)
		ft_open_exit(game);
	if (game->map[game->move_x][game->move_y] == 'E' &&
		game->count_collectables != 0)
		ft_printf("You don't have enough Weed, smoke more!");
	if (game->orientation == 0)
		ft_player_right(game);
	else
		ft_player_left(game);
	return ;
}

void	ft_player_right(t_game *game)
{
	game->orientation = 0;
	mlx_delete_image(game->mlx, game->player);
	game->swap_png = mlx_load_png("assets/sprites/player_right.png");
	if (!game->swap_png)
		ft_print_error_msg("Player right problem", game);
	game->player = mlx_texture_to_image(game->mlx, game->swap_png);
	if (!game->player)
		ft_print_error_msg("PLAYER right problem", game);
	mlx_delete_texture(game->swap_png);
	mlx_image_to_window(game->mlx, game->player, game->move_y
		* 32, game->move_x * 32);
	return ;
}

void	ft_player_left(t_game *game)
{
	game->orientation = 1;
	mlx_delete_image(game->mlx, game->player);
	game->swap_png = mlx_load_png("assets/sprites/player_left.png");
	if (!game->swap_png)
		ft_print_error_msg("Player right problem", game);
	game->player = mlx_texture_to_image(game->mlx, game->swap_png);
	if (!game->player)
		ft_print_error_msg("PLAYER right problem", game);
	mlx_delete_texture(game->swap_png);
	mlx_image_to_window(game->mlx, game->player, game->move_y * 32,
		game->move_x * 32);
	return ;
}

void	ft_movement(mlx_key_data_t key_stroke, t_game *game)
{
	if (((key_stroke.key == MLX_KEY_D || key_stroke.key == MLX_KEY_RIGHT)
			&& key_stroke.action == MLX_PRESS)
		&& (game->map[game->move_x][game->move_y + 1] != '1'))
	{
		ft_player_right(game);
		ft_move_right(game);
	}
	if (((key_stroke.key == MLX_KEY_A || key_stroke.key == MLX_KEY_LEFT)
			&& key_stroke.action == MLX_PRESS)
		&& (game->map[game->move_x][game->move_y - 1] != '1'))
	{
		ft_player_left(game);
		ft_move_left(game);
	}
	if (((key_stroke.key == MLX_KEY_W || key_stroke.key == MLX_KEY_UP)
			&& key_stroke.action == MLX_PRESS)
		&& (game->map[game->move_x - 1][game->move_y] != '1'))
		ft_move_up(game);
	if (((key_stroke.key == MLX_KEY_S || key_stroke.key == MLX_KEY_DOWN)
			&& key_stroke.action == MLX_PRESS)
		&& (game->map[game->move_x + 1][game->move_y] != '1'))
		ft_move_down(game);
	if ((key_stroke.key == MLX_KEY_ESCAPE || key_stroke.key == MLX_KEY_Q)
		&& key_stroke.action == MLX_PRESS)
		ft_free_game(game);
}
