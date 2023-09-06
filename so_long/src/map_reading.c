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

char	*ft_stringjoin(char *s1, char const *s2)
{
	int		total_len;
	int		len1;
	int		len2;
	char	*ptr;

	if (!s1 && !s2)
		return (free(s1), NULL);
	if (!s1 && s2)
		return (free(s1), ft_strdup(s2));
	if (s1 && !s2)
		return (free(s1), ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	total_len = len1 + len2 + 1;
	ptr = (char *)malloc(sizeof(char) * (total_len));
	if (!ptr)
		return (free(s1), NULL);
	ft_memmove(ptr, s1, len1);
	ft_memmove((ptr + len1), s2, len2);
	ptr[total_len - 1] = '\0';
	return (free(s1), ptr);
}

void	ft_read_map(char *argv, t_game *game)
{
	int		fd_map;
	char	*big_string;
	char	*string;

	fd_map = open(argv, O_RDONLY);
	big_string = ft_strdup("");
	if (fd_map == -1)
		ft_print_error_msg(YELLOW"File error or empty", 0);
	string = get_next_line(fd_map);
	if (!string || *string == '\n')
		ft_print_error_msg(YELLOW"Empty file", 0);
	while (string)
	{
		if (string && string[0] == '\n')
			ft_print_error_msg(YELLOW"line error or empty", 0);
		big_string = ft_stringjoin(big_string, string);
		free(string);
		string = get_next_line(fd_map);
	}
	close(fd_map);
	game->map = ft_split(big_string, '\n');
	game->map_copy = ft_split(big_string, '\n');
	free(big_string);
}

int	ft_flood_fill(t_game *game, int move_x, int move_y)
{
	if (game->map_copy[move_x][move_y] == 'E')
		game->count_exit--;
	if (game->map_copy[move_x][move_y] == 'C')
		game->count_collectables--;
	if (game->count_collectables == 0 && game->count_exit == 0)
		return (1);
	game->map_copy[move_x][move_y] = '&';
	if (game->map_copy[move_x][move_y - 1] != '&'
		&& game->map_copy[move_x][move_y - 1] != '1')
		if (ft_flood_fill(game, move_x, move_y - 1) == 1)
			return (1);
	if (game->map_copy[move_x][move_y + 1] != '&'
		&& game->map_copy[move_x][move_y + 1] != '1')
		if (ft_flood_fill(game, move_x, move_y + 1) == 1)
			return (1);
	if (game->map_copy[move_x - 1][move_y] != '&'
		&& game->map_copy[move_x - 1][move_y] != '1')
		if (ft_flood_fill(game, move_x - 1, move_y) == 1)
			return (1);
	if (game->map_copy[move_x + 1][move_y] != '&'
		&& game->map_copy[move_x + 1][move_y] != '1')
		if (ft_flood_fill(game, move_x + 1, move_y) == 1)
			return (1);
	return (-1);
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
	int		temporary_value;

	player_y = 0;
	player_x = 0;
	temporary_value = game->count_collectables;
	ft_player_position(game, &player_x, &player_y);
	if (ft_flood_fill(game, player_x, player_y) == -1)
		ft_print_error_msg(YELLOW"There is no posible way to win", 0);
	game->count_collectables = temporary_value;
}
