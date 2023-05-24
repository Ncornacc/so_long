/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:16:26 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/04/18 16:16:26 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	ft_check_argc(argc);
	game = ft_calloc(sizeof(t_game), 1);
	if (!game)
		ft_print_error_msg(YELLOW"MALLOC ERROR\n");
	ft_verify_mapname(argv[1]);
	ft_read_map(argv[1], game);
	ft_control_map(game);
	ft_verify_map(game->map, game);
	ft_create_window(game);
	return (EXIT_SUCCESS);
}
