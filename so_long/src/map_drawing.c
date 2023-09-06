/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_drawing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:55:43 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/04/18 14:55:46 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_draw_collectable(mlx_t *mlx, int rows, int columns, t_game *game)
{
	mlx_image_to_window(mlx, game->floor, columns * PIXELS, rows * PIXELS);
	mlx_image_to_window(mlx, game->collectables, columns * PIXELS,
		rows * PIXELS);
}

void	ft_draw_player(mlx_t *mlx, int rows, int columns, t_game *game)
{
	mlx_image_to_window(mlx, game->floor, columns * PIXELS, rows * PIXELS);
	mlx_image_to_window(mlx, game->player, columns * PIXELS, rows * PIXELS);
	game->move_x = rows;
	game->move_y = columns;
}

void	ft_draw_exit(mlx_t *mlx, int rows, int columns, t_game *game)
{
	mlx_image_to_window(mlx, game->floor, columns * PIXELS, rows * PIXELS);
	mlx_image_to_window(mlx, game->exit, columns * PIXELS, rows * PIXELS);
}

void	ft_draw_map(mlx_t *mlx, t_game *game)
{
	int		j;
	int		i;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
			if (game->map[i][j] == '1')
				mlx_image_to_window(mlx, game->wall, j * PIXELS, i * PIXELS);
		else if (game->map[i][j] == 'C')
			ft_draw_collectable(mlx, i, j, game);
		else if (game->map[i][j] == 'E')
			ft_draw_exit(mlx, i, j, game);
		else if (game->map[i][j] == 'P')
			ft_draw_player(mlx, i, j, game);
		else if (game->map[i][j] == '0')
			mlx_image_to_window(mlx, game->floor, j * PIXELS, i * PIXELS);
	}
}
