/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialization.c                                          :+:    :+:     */
/*                                                     +:+                    */
/*   By: ncornacc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:55:43 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/04/18 14:55:46 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_init_vars(t_game *game)
{
	game->rows = 0;
	game->columns = 0;
	game->orientation = 0;
	game->move_x = 0;
	game->move_y = 0;
	game->count_player = 0;
	game->count_collectables = 0;
	game->count_moves = 0;
	game->count_exit = 0;
	game->exit_game = 0;
	game->player_x = 0;
	game->player_y = 0;
}

void	ft_create_textures(t_game *game)
{
	ft_load(game, "assets/sprites/floor.png");
	game->floor = mlx_texture_to_image(game->mlx, game->swap_png);
	if (!game->floor)
		ft_print_error_msg("FLOOR loading problem", game);
	mlx_delete_texture(game->swap_png);
	ft_load(game, "assets/sprites/wall.png");
	game->wall = mlx_texture_to_image(game->mlx, game->swap_png);
	if (!game->wall)
		ft_print_error_msg("WALL loading problem", game);
	mlx_delete_texture(game->swap_png);
	ft_load(game, "assets/sprites/weed.png");
	game->collectables = mlx_texture_to_image(game->mlx, game->swap_png);
	if (!game->collectables)
		ft_print_error_msg("COLLECTABLES loading problem", game);
	mlx_delete_texture(game->swap_png);
	ft_load(game, "assets/sprites/player_right.png");
	game->player = mlx_texture_to_image(game->mlx, game->swap_png);
	if (!game->player)
		ft_print_error_msg("Player loading problem", game);
	mlx_delete_texture(game->swap_png);
	ft_load(game, "assets/sprites/exit.png");
	game->exit = mlx_texture_to_image(game->mlx, game->swap_png);
	if (!game->exit)
		ft_print_error_msg("COLLECTABLES loading problem", game);
	mlx_delete_texture(game->swap_png);
}

void	ft_check_argc(int argc)
{
	if (argc > 2)
		ft_print_error_msg(YELLOW"Too many arguments", 0);
	if (argc < 2)
		ft_print_error_msg(YELLOW"NO mapfile, you have to input one!", 0);
}

void	ft_control_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (ft_strchr("PEC01", game->map[y][x]) == NULL)
				ft_print_error_msg(YELLOW"Invalid characters!", 0);
			x++;
		}
		y++;
	}
}

void	ft_create_window(t_game *game)
{
	game->window_x = game->rows * PIXELS;
	game->window_y = (game->columns * 32);
	game->mlx = mlx_init(game->window_y, game->window_x, "so_long", 0);
	if (!game->mlx)
		ft_print_error_msg("Failed window Creation!", game);
	ft_create_textures(game);
	ft_draw_map(game->mlx, game);
	mlx_key_hook(game->mlx, (mlx_keyfunc)ft_movement, game);
	mlx_loop(game->mlx);
	ft_free_game(game);
	return ;
}
