/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_reading.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:55:43 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/04/18 14:55:46 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

//OPEN MAP AND USE STR_JOIN AND FT_SPLIT TO INSERT IT INTO A 2D ARRAY, THEN CHECK FOR ERROR

void	ft_read_map(char *argv, t_game *game)
{
	int		fd_map;
	char	*temp;
	char	*big_string;
	char	*string;

	fd_map = open(argv, O_RDONLY);
	big_string = ft_strdup("");
	if (fd_map == -1)
		ft_print_error_msg("File error or empty");
	string = get_next_line(fd_map);
	if (!string)
		ft_print_error_msg("Empty file");
	while (string)
	{
		temp = ft_strjoin(big_string, string);
		free(big_string);
		big_string = temp;
		free(string);
		string = get_next_line(fd_map);
	}
	free(string);
	free(temp);
	close(fd_map);
	game->map = ft_split(big_string, '\n');
	game->map_copy = ft_split(big_string, '\n');
}


void	ft_flood_fill(t_game *game, int move_x, int move_y)
{
	if (move_x < 0 || move_y < 0 || move_x >= game->columns
		|| move_y >= game->rows || game->map_copy[move_x][move_y] == '1'
			|| game->map_copy[move_x][move_y] == 'X')
		return ;
	if (((game->map_copy[move_x + 1][move_y] == 'E')
		|| (game->map_copy[move_x - 1][move_y] == 'E'))
		&& ((game->map_copy[move_x][move_y + 1] == '1')
			|| (game->map_copy[move_x][move_y - 1] == '1')))
		return ;
	if (((game->map_copy[move_x][move_y + 1] == 'E')
		|| (game->map_copy[move_x][move_y - 1] == 'E'))
		&& ((game->map_copy[move_x + 1][move_y] == '1')
		|| (game->map_copy[move_x - 1][move_y] == '1')))
		return ;
	if (game->map_copy[move_x][move_y] == 'E' ||
		game->map_copy[move_x][move_y] == 'C')
		game->map_copy[move_x][move_y] = '0';
	game->map_copy[move_x][move_y] = 'X';
	ft_flood_fill(game, move_x - 1, move_y);
	ft_flood_fill(game, move_x + 1, move_y);
	ft_flood_fill(game, move_x, move_y - 1);
	ft_flood_fill(game, move_x, move_y + 1);
}

// FUNCTIONS THAT RECALLS FLODFILL

void	ft_to_fill(t_game *game, int move_x, int move_y)
{
	ft_flood_fill(game, move_x, move_y);
}



void	ft_player_position(t_game *game, int *player_x, int *player_y)
{
	int	i;
	int	j;

	i = 0;
	while (game->map_copy[i])
	{
		j = 0;
		while (game->map_copy[i][j])
		{
			if (game->map_copy[i][j] == 'P')
			{
				*player_x = i;
				*player_y = j;
			}
			j++;
		}
		i++;
	}
}


void	ft_verify_win(t_game *game)
{
	int		player_x;
	int		player_y;
	int		y;
	int		x;

	player_y = 0;
	player_x = 0;
	y = 0;
	ft_player_position(game, &player_x, &player_y);
	ft_to_fill(game, player_x, player_y);
	while (game->map_copy[y])
	{
		x = 0;
		while (game->map_copy[y][x])
		{
			if (game->map_copy[y][x] == 'C'
				|| game->map_copy[y][x] == 'E')
				ft_print_error_msg(YELLOW"There is no posible way to win");
			x++;
		}
		y++;
	}
}