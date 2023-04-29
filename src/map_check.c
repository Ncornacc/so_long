/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:55:43 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/04/18 14:55:46 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// CHECKS FOR THE .ber EXTENSION

void	ft_verify_mapname(char *map_name)
{
	size_t	len;

	len = ft_strlen(map_name);
	if (map_name[len - 3] != 'b' || map_name[len - 2] != 'e'
		|| map_name[len - 4] != '.' || map_name[len - 1] != 'r')
		ft_print_error_msg(YELLOW"File extension is wrong");
}

// CHECKS MAP BORDERS

void	ft_verify_map(char **map, t_game *game)
{
	int		i;
	int		x;

	while (map[game->rows])
	{
		while (map[game->rows][game->columns])
			game->columns++;
		game->rows++;
	}
	i = -1;
	while (map[++i])
	{
		x = -1;
		while (map[i][++x])
		{
			if ((i == 0 || i == game->rows - 1)
				|| (x == 0 || x == game->columns - 1))
				if (map[i][x] != '1')
					ft_print_error_msg(YELLOW"Map is not closed");
		}
	}
	ft_check_items(game);
	ft_verify_counts(game);
	ft_count_column(game);
	ft_verify_win(game);
}


void	ft_check_items(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
				game->count_player++;
			if (game->map[y][x] == 'C')
				game->count_collectables++;
			if (game->map[y][x] == 'E')
				game->count_exit++;
			x++;
		}
		y++;
	}	
}

// CHECKS IF THE PLAYER HAS THE RIGHT VALUES TO WIN

void	ft_verify_counts(t_game *game)
{
	if (game->count_player != 1 || game->count_exit != 1)
	{
		free(game);
		ft_print_error_msg(YELLOW"Error with chraracters");
	}
	if (game->count_collectables < 1)
	{
		free(game);
		ft_print_error_msg(YELLOW"There are any collectibles!");
	}
}


void	ft_count_column(t_game *game)
{
	int		count_line;
	int		tmp;
	int		i;

	game->rows = 0;
	tmp = 0;
	i = 0;
	count_line = ft_strlen(game->map[0]);
	while (game->map[i])
	{
		tmp = ft_strlen(game->map[i]);
		if (count_line != tmp)
		{
			ft_free_map(game);
			ft_print_error_msg(YELLOW"Column size error");
		}
		i++;
	}
	game->rows = tmp;
}