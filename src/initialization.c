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

// We use swap_png to load the initial texture and then use that value to load it into an Image.
// Afterwards we free it so we could use it again.
void	ft_create_textures(t_game *game)
{
	game->swap_png = mlx_load_png("assets/sprites/floor.png");
	game->floor = mlx_texture_to_image(game->mlx, game->swap_png);
	mlx_delete_texture(game->swap_png);
	game->swap_png = mlx_load_png("assets/sprites/wall.png");
	game->wall = mlx_texture_to_image(game->mlx, game->swap_png);
	mlx_delete_texture(game->swap_png);
	game->swap_png = mlx_load_png("assets/sprites/weed.png");
	game->collectables = mlx_texture_to_image(game->mlx, game->swap_png);
	mlx_delete_texture(game->swap_png);
	game->swap_png = mlx_load_png("assets/sprites/floor.png");
	game->player = mlx_texture_to_image(game->mlx, game->swap_png);
	mlx_delete_texture(game->swap_png);
	game->swap_png = mlx_load_png("assets/sprites/exit.png");
	game->exit = mlx_texture_to_image(game->mlx, game->swap_png);
	mlx_delete_texture(game->swap_png);
}


void	ft_verify_argc(int argc)
{
	if (argc > 2)
		ft_print_error_msg(YELLOW"Too many arguments");
	if (argc < 2)
		ft_print_error_msg(YELLOW"NO mapfile, ERROR");
}

void	ft_validate_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game-> map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (ft_strchr("PEC01", game->map[y][x]) == NULL)
			{
				free(game);
				ft_print_error_msg(YELLOW"Invalid characters! acceptable ones: P,E,C,0,1");
			}
			x++;
		}
		y++;
	}
}