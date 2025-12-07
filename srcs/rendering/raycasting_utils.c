#include "cub3d.h"

void	make_dir(t_control *main_control)
{
	if(main_control->player.direction == 'N')
	{
		main_control->dir.x = 0;
		main_control->dir.y = -1;
	}
	else if(main_control->player.direction == 'S')
	{
		main_control->dir.x = 0;
		main_control->dir.y = 1;
	}
	else if(main_control->player.direction == 'E')
	{
		main_control->dir.x = 1;
		main_control->dir.y = 0;
	}
	else if(main_control->player.direction == 'W')
	{
		main_control->dir.x = -1;
		main_control->dir.y = 0;
	}
}

void make_plane(t_control *main_control)
{
	double planeLen = 0.66;
	main_control->plane.x = (main_control->dir.y * -1) * planeLen;
	main_control->plane.y = main_control->dir.x * planeLen;
}
