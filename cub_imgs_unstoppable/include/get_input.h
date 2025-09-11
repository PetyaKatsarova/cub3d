/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_input.h                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 13:23:35 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/20 13:23:37 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_INPUT_H
# define GET_INPUT_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

# define ALLOC_FAILED "failed to allocate memory\n"
# define OPEN_FAILED "failed to open file\n"
# define EMPTY "empty .cub file\n"
# define NO_MAP "no map found\n"
# define NO_PLAYER "no player on map\n"
# define MULT_PLAYERS "multiple players on map\n"
# define INV_CHAR_MAP "invalid char in map\n"
# define EMPTY_LINE_MAP "empty line in map\n"
# define NOT_ENCLOSED "map not enclosed\n"
# define ARGS "please provide one argument\n"
# define FILENAME "no filename\n"
# define FILE_EXT "incorrect file extension\n"
# define FC_SPACE "missing space after F/C id\n"
# define INV_CHAR_FC "invalid character in F/C definition\n"
# define FC_REDEF "F/C redefinition\n"
# define LEADING_ZERO "leading zero in RGB definition\n"
# define OVERFLOW "RGB value exceeds 255\n"
# define COMMA "missing comma in F/C definition\n"
# define TEXTURE_SPACE "missing space after texture id\n"
# define TEXTURE_REDEF "texture redefinition\n"
# define INV_CHAR "invalid char\n"
# define FILE_PATH "file not found/failed to open file\n"
# define TEXTURE_PATH "texture not found/failed to open texture\n"
# define INV_CHAR_TEXTURE "invalid char in texture id\n"
# define INV_CHAR_FC_TEXTURE "texture/F/C def: invalid char at start of line\n"
# define INV_CHAR_PATH "invalid char after texture path\n"

typedef struct s_parsing
{
	char	**scene;
	char	*no;
	char	*ea;
	char	*so;
	char	*we;
	int		floor[3];
	int		ceiling[3];
	int		map_first_line;
	int		map_last_line;
	int		map_first_col;
	int		map_last_col;
	int		map_rows;
	int		map_columns;
	char	**test_map;
	int		test_rows;
	int		test_columns;
}	t_parsing;

typedef struct s_game_configs
{
	char	*no;
	char	*ea;
	char	*so;
	char	*we;
	int		floor_argb;
	int		ceiling_argb;
	char	**map;
	int		map_rows;
	int		map_cols;
	int		player_start_row;
	int		player_start_col;
	char	player_start_orientation;
}	t_game_configs;

int				main(int argc, char **argv);
t_game_configs	*get_input(int argc, char **argv);
void			validate_file(int argc, char **argv);
void			exit_error_parsing(char *message, t_parsing *parsing);
void			read_file(char *filepath, t_parsing *parsing);
void			free_parsing(t_parsing *parsing);
void			free_game_configs(t_game_configs *game_configs);
void			initialize_parsing_data(t_parsing *parsing);
void			parse_scene(t_parsing *parsing);
void			parse_texture(t_parsing *parsing, int i, int j);
void			parse_floor_ceiling(t_parsing *parsing, int i, int j);
void			parse_map(t_parsing *parsing, int i);
void			validate_path(char *path, t_parsing *parsing, char *message);
int				ft_strncmp(char *s1, char *s2, int n);
size_t			ft_strlen(char *s);
t_game_configs	*make_game_configs(t_parsing *parsing);
void			initialize_game_configs(t_game_configs *game_configs);
void			all_chars_legal(t_parsing *parsing, int i);
void			check_test_map_enclosed(t_parsing *parsing);
void			count_players(t_parsing *parsing, int i);
void			illegal_empty_lines(t_parsing *parsing, int i);
void			map_enclosed(t_parsing *parsing, int i);
void			measure_map(t_parsing *parsing, int i);
bool			is_space(char c);
int				traverse_space(t_parsing *parsing, int i, int j);
void			print_parsing(t_parsing *parsing);
void			print_game_configs(t_game_configs *game_configs);
void			get_rgb_vals(t_parsing *parsing, t_game_configs *game_configs);
void			copy_map(t_parsing *parsing, t_game_configs *game_configs);
void			print_argb(t_game_configs *game_configs);
void			print_fc(t_parsing *parsing, t_game_configs *game_configs);

#endif
