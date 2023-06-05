/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:55:43 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/04/18 14:55:46 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/include/libft.h"
# include "stdlib.h"
# include "stdarg.h"
# include "fcntl.h"

# define PIXELS 32
# define EXIT_SUCCESS 0
# define EXIT_FAIL 1

# define DEF_COLOR "\033[0;39m"
# define GRAY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"

typedef struct s_game
{
	mlx_t				*mlx;
	char				**map;
	char				**map_copy;
	int					orientation;
	int					rows;
	int					columns;
	int					window_x;
	int					window_y;
	int					move_x;
	int					move_y;
	int					count_player;
	int					count_collectables;
	int					count_moves;
	int					count_exit;
	int					exit_game;
	int					player_x;
	int					player_y;
	mlx_texture_t		*swap_png;
	mlx_image_t			*floor;
	mlx_image_t			*wall;
	mlx_image_t			*collectables;
	mlx_image_t			*player;
	mlx_image_t			*exit;
}			t_game;

/*--------------FREE AND ERROR FUNCTIONS----------------------*/
void	ft_free_game(t_game *game);
void	ft_free_map(t_game *game);
void	ft_free_images(t_game *game);
void	ft_print_error_msg(char *string, t_game *game);
void	ft_open_exit(t_game *game);

/*--------------INITIALIZATION FUNCTIONS-------------------------*/
void	ft_init_vars(t_game *game);
void	ft_create_textures(t_game *game);
void	ft_check_argc(int argc);
void	ft_control_map(t_game *game);
void	ft_load(t_game *game, char *string);
void	ft_create_window(t_game *game);

/*--------------MOVEMENT AND INPUT(hooks) FUNCTIONS---------------*/
void	ft_movement(mlx_key_data_t key_stroke, t_game *game);
void	ft_move_up(t_game *game);
void	ft_move_down(t_game *game);
void	ft_move_left(t_game *game);
void	ft_move_right(t_game *game);
void	ft_check_map_values(t_game *game);
void	ft_player_right(t_game *game);
void	ft_player_left(t_game *game);

/*--------------DRAWING MAP FUNCTIONS-------------------------*/
void	ft_draw_collectable(mlx_t *mlx, int rows, int columns, t_game *game);
void	ft_draw_player(mlx_t *mlx, int rows, int columns, t_game *game);
void	ft_draw_exit(mlx_t *mlx, int rows, int columns, t_game *game);
void	ft_draw_map(mlx_t *mlx, t_game *game);

/*--------------READING MAP FUNCTIONS----------------------------*/
void	ft_read_map(char *map_file, t_game *game);
int		ft_flood_fill(t_game *game, int column, int line);
void	ft_to_fill(t_game *game, int move_x, int move_y);
void	ft_player_position(t_game *game, int *player_x, int *player_y);
void	ft_verify_win(t_game *game);
char	*ft_stringjoin(char *s1, char const *s2);

/*--------------CHECK MAP FUNCTIONS----------------------------*/
void	ft_verify_mapname(char *map_name);
void	ft_verify_map(char **map, t_game *game);
void	ft_check_items(t_game *game);
void	ft_verify_counts(t_game *game);
void	ft_count_column(t_game *game);

#endif