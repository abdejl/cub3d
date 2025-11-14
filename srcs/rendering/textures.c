#include "cub3d.h"

void load_texture(t_control *main)
{

    main->east_tex.img_ptr = mlx_xpm_file_to_image(main->mlx_ptr, main->ea_texture_path, &main->east_tex.width, &main->east_tex.height);
    main->north_tex.img_ptr = mlx_xpm_file_to_image(main->mlx_ptr, main->no_texture_path, &main->north_tex.width, &main->north_tex.height);
    main->south_tex.img_ptr = mlx_xpm_file_to_image(main->mlx_ptr, main->so_texture_path, &main->south_tex.width, &main->south_tex.height);
    main->west_tex.img_ptr = mlx_xpm_file_to_image(main->mlx_ptr, main->we_texture_path, &main->west_tex.width, &main->west_tex.height);

    main->east_tex.data = mlx_get_data_addr(main->east_tex.img_ptr, &main->east_tex.bit_per_pixel, &main->east_tex.line_length, &main->east_tex.endian);
    main->north_tex.data = mlx_get_data_addr(main->north_tex.img_ptr, &main->north_tex.bit_per_pixel, &main->north_tex.line_length, &main->north_tex.endian);
    main->south_tex.data = mlx_get_data_addr(main->south_tex.img_ptr, &main->south_tex.bit_per_pixel, &main->south_tex.line_length, &main->south_tex.endian);
    main->west_tex.data = mlx_get_data_addr(main->west_tex.img_ptr, &main->west_tex.bit_per_pixel, &main->west_tex.line_length, &main->west_tex.endian);
}


void pixel_on_img(t_control *main, int x, int y, int color)
{
    int y_offset;
    int x_offset;
    int final_addr_index;
    int red_byte;
    int green_byte;
    int blue_byte;

    y_offset = y * main->line_length;
    x_offset = x * (main->bits_per_pixel / 8);
    final_addr_index = y_offset + x_offset;

    red_byte = (color >> 16) & 0xFF;
    green_byte = (color >> 8) & 0xFF;
    blue_byte = color & 0xFF;

    if(main->endian == 0)
    {
        main->data[final_addr_index] = blue_byte;
        main->data[final_addr_index + 1] = green_byte;
        main->data[final_addr_index + 2] = red_byte;
    }
    if(main->endian == 1)
    {
        main->data[final_addr_index] = red_byte;
        main->data[final_addr_index + 1] = green_byte;
        main->data[final_addr_index + 2] = blue_byte;
    }
}

int get_texture_pixel_color(t_texture *texture, int x, int y)
{
    int y_offset;
    int x_offset;
    int final_addr_index;
    int final_color;
    int red_byte;
    int green_byte;
    int blue_byte;

    y_offset = y * texture->line_length;
    x_offset = x * (texture->bit_per_pixel / 8);
    final_addr_index = y_offset + x_offset;

    if(texture->endian == 0)
    {
        blue_byte = texture->data[final_addr_index];
        green_byte = texture->data[final_addr_index + 1];
        red_byte = texture->data[final_addr_index + 2];
    }
    if(texture->endian == 1)
    {
        red_byte = texture->data[final_addr_index];
        green_byte = texture->data[final_addr_index + 1];
        blue_byte = texture->data[final_addr_index + 2];
    }
    final_color = (blue_byte << 16) | (green_byte << 8) | red_byte;
    return(final_color);
}

void paint_line(t_control *main, int x, int y_start, int y_end, int color)
{
    int y;
    if(y_start < 0)
        y_start = 0;
    if(y_end > HEIGHT)
        y_end = HEIGHT;
    y = y_start;

    while(y < y_end)
    {
        pixel_on_img(main, x, y, color);
        y++;
    }
}