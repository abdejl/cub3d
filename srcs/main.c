#include "cub3d.h"

t_control	*control_memo(void)
{
	static t_control	control;

	return (&control);
}
void	print_data()
{
	t_control *main;
	t_map *head;
	main = control_memo();
	head = main->map;
	while (head != NULL)
	{
		printf("%s",head->line);
		head = head->next;
	}
}

int main(int ac, char *av[])
{
    (void) ac;
    t_control *main_control;

    main_control = control_memo();
    if (check_argm(ac))
        printer_and_free("Invalid number of arguments");
    validit_filename(av[1], "cub");
    change_map_to_data(av[1]);
    validit_texture_and_color();
    read_and_parse_file(av[1]);
    create_map_grid(main_control);
    validate_map_characters(main_control);
    validate_map_enclosure(main_control);
    make_dir(main_control);
	make_plane(main_control);
	calculate_ray_to_wall(main_control);

    main_control->mlx_ptr = mlx_init();
    main_control->mlx_win = mlx_new_window(main_control->mlx_ptr, 1920, 1080, "CUB3D");
	//t_map *map;
	// while(main_control->map_grid && main_control->map_grid[i])
	// {
	// 	printf("%d", main_control->map->line[i]);
	// 	i++;
	// }
    //setup_hooks(main_control);
    update_player_movement(main_control);
	setup_hooks(main_control);
	mlx_loop(main_control->mlx_ptr);
    return (0);
}
