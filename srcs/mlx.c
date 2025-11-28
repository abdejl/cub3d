#include "cub3d.h"

void mlx(t_control *main_control)
{
	main_control->mlx_ptr = mlx_init();
    main_control->mlx_win = mlx_new_window(main_control->mlx_ptr, WIDTH, HEIGHT, "CUB3D");
	main_control->img_ptr = mlx_new_image(main_control->mlx_ptr, WIDTH, HEIGHT);
	main_control->data = mlx_get_data_addr(main_control->img_ptr, &main_control->bits_per_pixel, &main_control->line_length, &main_control->endian);
	load_texture(main_control);
	setup_hooks(main_control);
	mlx_loop(main_control->mlx_ptr);
}
