#include "cub3d.h"

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
		main->keys.w = 1;
	}
	else if (keycode == 97)
	{
		main->keys.a = 1;
	}
	else if (keycode == 115)
	{
		main->keys.s = 1;
	}
	else if (keycode == 100)
	{
		main->keys.d = 1;
	}
	else if (keycode == 65361)
	{
		main->keys.left_arrow = 1;
	}
	else if (keycode == 65363)
	{
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
	}
	else if (keycode == 97)
	{
		main->keys.a = 0;
	}
	else if (keycode == 115)
	{
		main->keys.s = 0;
	}
	else if (keycode == 100)
	{
		main->keys.d = 0;
	}
	else if (keycode == 65361)
	{
		main->keys.left_arrow = 0;
	}
	else if (keycode == 65363)
	{
		main->keys.right_arrow = 0;
	}
	return (0);
}

int master_loop(t_control *main)
{
    update_player_movement(main);
    calculate_ray_to_wall(main);
    mlx_put_image_to_window(main->mlx_ptr, main->mlx_win, main->img_ptr, 0, 0);
    return (0);
}

void setup_hooks(t_control *control)
{
    mlx_hook(control->mlx_win, 17, 0, close_game, control);
    mlx_hook(control->mlx_win, 2, 1L<<0, key_press_handler, control);
	mlx_hook(control->mlx_win, 3, 1L<<1, key_release_handler, control);
	mlx_loop_hook(control->mlx_ptr, master_loop, control);
}

