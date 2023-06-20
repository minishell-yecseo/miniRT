#include "miniRT.h"

void	color_image(t_img *img, t_vars *vars)
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

int	get_color(t_vars *vars, double x, double y)
{
	int	ret;
	int	r;
	int	g;
	int	b;

	ret = 0x00000000;
	r = (int)(255 * (x / (WIDTH - 1)));
	g = (int)(255 * (y / (HEIGHT - 1)));
	b = (int)(255 * 0.25);
	ret = (r << 16) + (g << 8) + b;
	return (ret);
}

void	paint(t_img *img, int x, int y, int color)
{
	void	*addr;
	char	*tmp;

	addr = mlx_get_data_addr(img->image, &img->bits_per_pixel, \
			&img->size_len, &img->endian);
	tmp = addr + ((HEIGHT - 1 - y) * img->size_len);
	tmp += x * (img->bits_per_pixel / 8);
	*(unsigned int *) tmp = color;
}
