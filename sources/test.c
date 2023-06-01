#include "miniRT.h"

void	test(t_img *img, t_vars *vars)
{
	int			x;
	int			y;
	int			color;

	mlx_clear_window(vars->mlx, vars->win);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			color = get_color(vars, x, y);
			paint(img, x, y, color);
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->image, 0, 0);
}