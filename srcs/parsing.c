#include "cub3d.h"

void parsing(t_control *main_control, char av[])
{
	validit_filename(av, "cub");
    change_map_to_data(av); 
    validit_texture_and_color();
    clean_map_list(main_control);
    create_map_grid(main_control);
    validate_map_characters(main_control);
    validate_map_enclosure(main_control);
    make_dir(main_control);
	make_plane(main_control);
}