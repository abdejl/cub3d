#ifndef CUB3D_H
#define CUB3D_H

#define BUFFER_SIZE 10

#define textureWidth 64
#define textureHeight 64

#define WIDTH 1920
#define HEIGHT 1080

#define MOVE_SPEED 0.06
#define ROT_SPEED 0.04

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include "../mlx_linux/mlx.h"

typedef struct s_move
{
	double	x_step;
	double	y_step;
	double	new_x;
	double	new_y;
	double buffer;
} t_move;

typedef struct s_dir
{
	double x;
	double y;
}	t_dir;


typedef struct s_plane
{
	double x;
	double y;
}	t_plane;

typedef struct s_delta_dist
{
	double x;
	double y;
}	t_delta_dist;

typedef struct s_step
{
	int x;
	int y;
}	t_step;

typedef struct s_side_dist
{
	double x;
	double y;
}	t_side_dist;

typedef struct s_ray_position
{
	double x;
	double y;
}	t_ray_position;

typedef struct s_raydir
{
	double x;
	double y;
}	t_raydir;


typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left_arrow;
	int	right_arrow;
}	t_keys;


typedef struct s_texture
{
    void    *img_ptr;
    char    *addr;
	char 	*data;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
} t_texture;


typedef struct s_player
{
	double	x;
	double	y;
	char	direction;
}	t_player;

typedef struct s_node
{
	void	*data;
	struct	s_node *next;
}	t_node;

typedef struct s_map
{
	char	*line;
	struct	s_map *next;
}	t_map;

typedef struct s_color
{
	int Floor[3];
	int Ceiling[3];
}	t_color;


typedef struct s_control
{
	t_keys keys;
	void *mlx_ptr;
	void *mlx_win;
	char	**map_grid;
	t_player player;
	t_node	*node;
	t_map	*map;
	t_color		color;
	// char		*texture[4];
	t_dir			dir;
	t_plane			plane;
	double			camerax;
	t_raydir		raydir;
	t_ray_position	Map;
	t_delta_dist	delta_dist;
	t_step			step;
	t_side_dist		side_dist;
	t_texture north_tex;
	t_texture south_tex;
	t_texture west_tex;
	t_texture east_tex;
	int *width;
	int *height;
	int current_x;

	char	*no_texture_path;
	char	*so_texture_path;
	char	*we_texture_path;
	char	*ea_texture_path;
	int		floor_color;
	int		ceiling_color;
	int		elements_found;
	int drawstart;
	int drawend;
	double  wallX;
    int     texx;
    double  steP;
    double  texPos;
	double  lineHeight;
    double  perpWallDist;

	void	*img_ptr;
	char	*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_control;

/*--------------------FREE------------------------*/

void		free_all();
void		add_m_node(void *data);

/*----------------------------------*/

/*----------LIBFT---------------------*/

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strchr(char *s, char c);
void	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(const char *s);
int		ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_atoi(const char *str);
char	*ft_strdup(const char *s);
char	**ft_split(const char *s, char c);

/*----------------------------------*/

t_control	*control_memo(void);
int			check_argm(int ac);
void		printer_and_free(char *s);
void		validit_filename(char *s, const char *sc);
void		add_node(char *data);
char 		*get_next_line(int fd);
void		validate_map_characters(t_control *main);
void		validate_map_enclosure(t_control *main);
char		*strip_newline(char *line);
void		create_map_grid(t_control *main);
void		calculate_ray_to_wall(t_control *main_control);
void		make_dir(t_control *main_control);
void		make_plane(t_control *main_control);
void		calculate_ray_direction(t_control *main_control);
void		setup_hooks(t_control *control);
void		update_player_movement(t_control *main);
void		load_texture(t_control *main);
void		paint_line(t_control *main, int y_start, int y_end, int color);
int			get_texture_pixel_color(t_texture *texture, int x, int y);
void		pixel_on_img(t_control *main, int x, int y, int color);
void    paint_texture_line(t_control *main, t_texture *tex);
void		mlx(t_control *main_control);
void		parsing(t_control *main_control, char av[]);
void		change_map_to_data(char *file_nmae);
void		validit_texture_and_color();
void		clean_map_list(t_control *main);
void		destroy_images(t_control *main);
void		cleanup_game(t_control *control);
int			close_game(t_control *control);
void		rotate_player(t_control *main, int direction);
void		move_player_left(t_control *main);
void		move_player_right(t_control *main);
void		move_player_backward(t_control *main);
void		move_player_forward(t_control *main);

#endif