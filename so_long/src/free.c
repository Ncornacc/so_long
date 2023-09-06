/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:16:26 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/04/18 16:16:26 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_free_game(t_game *game)
{
	mlx_delete_image(game->mlx, game->floor);
	mlx_delete_image(game->mlx, game->wall);
	mlx_delete_image(game->mlx, game->collectables);
	mlx_delete_image(game->mlx, game->player);
	mlx_delete_image(game->mlx, game->exit);
	ft_free_map(game);
	mlx_close_window(game->mlx);
	free(game);
	exit(EXIT_SUCCESS);
}

void	ft_free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->rows)
	{
		if (game->map_copy)
			free(game->map_copy[i]);
		free(game->map[i]);
		i++;
	}
	free(game->map_copy);
	free(game->map);
	game->map = NULL;
}

void	ft_print_error_msg(char *string, t_game *game)
{
	if (game == 0)
	{
		ft_printf(RED"Error\n%s\n", string);
		exit(EXIT_FAIL);
	}
	ft_printf(RED"Error\n%s\n", string);
	ft_free_game(game);
	exit(EXIT_FAIL);
}

void	ft_open_exit(t_game *game)
{
	ft_printf(GREEN"\nYou finish the game with %d moves", game->count_moves);
	ft_free_game(game);
}
