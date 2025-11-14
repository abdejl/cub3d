#include "cub3d.h"


// void	ft_free_tab(char **tab)
// {
// 	int	i;

// 	if (!tab)
// 		return ;
// 	i = -1;
// 	while (tab[++i])
// 		free(tab[i]);
// 	free(tab);
// }

// t_map *free_map(t_map *map)
// {
//     if(map)
//     {
//         if(map->line)
//             ft_free_tab(map->line);
//         free(map);
//     }
//     return (NULL);
// }

void cleanup_game(t_control *control)
{
    if(control->mlx_win)
        mlx_destroy_window(control->mlx_ptr, control->mlx_win);
    if(control->mlx_ptr)
    {
        mlx_destroy_display(control->mlx_ptr);
        free(control->mlx_ptr);
    }
    if(control->map)
        free(control->map);
}


int close_game(t_control *control)
{
    cleanup_game(control);
    exit(0);
    return(0);
}


int	key_press_handler(int keycode, t_control *main)
{
	if (keycode == 119)
	{
		printf("w key is pressed: %d\n", main->keys.w);
		main->keys.w = 1;
	}
	else if (keycode == 97)
	{
		printf("a key is pressed: %d\n", main->keys.a);
		main->keys.a = 1;
	}
	else if (keycode == 115)
	{
		printf("s key is pressed: %d\n", main->keys.d);
		main->keys.s = 1;
	}
	else if (keycode == 100)
	{
		printf("d key is pressed: %d\n", main->keys.d);
		main->keys.d = 1;
	}
	else if (keycode == 65361)
	{
		printf("left arrow key is pressed: %d\n", main->keys.left_arrow);
		main->keys.left_arrow = 1;
	}
	else if (keycode == 65363)
	{
		printf("right arrow key is pressed: %d\n", main->keys.right_arrow);
		main->keys.right_arrow = 1;
	}
	else if (keycode == 65307)
		close_game(main);
	return (0);
}


int key_release_handler(int keycode, t_control *main)
{
    if (keycode == 119)
	{
		main->keys.w = 0;
		printf("w key is released: %d\n", main->keys.w);
	}
	else if (keycode == 97)
	{
		main->keys.a = 0;
		printf("a key is released: %d\n", main->keys.a);
	}
	else if (keycode == 115)
	{
		main->keys.s = 0;
		printf("s key is released: %d\n", main->keys.s);
	}
	else if (keycode == 100)
	{
		main->keys.d = 0;
		printf("d key is released: %d\n", main->keys.d);
	}
	else if (keycode == 65361)
	{
		main->keys.left_arrow = 0;
		printf("left arrow is released: %d\n", main->keys.left_arrow);
	}
	else if (keycode == 65363)
	{
		main->keys.right_arrow = 0;
		printf("right arrow is released: %d\n", main->keys.right_arrow);
	}
	return (0);
}

int	master_loop(t_control *main)
{
    update_player_movement(main);
    return (0);
}

void setup_hooks(t_control *control)
{
    mlx_hook(control->mlx_win, 17, 0, close_game, control);
    mlx_hook(control->mlx_win, 2, 1L<<0, key_press_handler, control);
	mlx_hook(control->mlx_win, 3, 1L<<1, key_release_handler, control);
	mlx_loop_hook(control->mlx_ptr, master_loop, control);
}





// void destroy_images(t_control *control)
// {

// }





