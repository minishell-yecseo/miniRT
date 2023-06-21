#include "./headers/miniRT.h"


void	paint(t_img *img, int x, int y, int color)
{
	void	*addr;
	char	*tmp;

	addr = mlx_get_data_addr(img->image, &img->bits_per_pixel, \
			&img->size_len, &img->endian);
	tmp = addr + ((HEIGHT - y) * img->size_len);
	tmp += x * (img->bits_per_pixel / 8);
	*(unsigned int *) tmp = color;
}

double	map(double value, double *range, double *new_range)
{
	double	ret;
	ret = (((value - range[0]) * (new_range[1] - new_range[0])) \
		/ (range[1] - range[0])) + new_range[0];
	return (ret);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_img	texture;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	vars.img.image = mlx_new_image(vars.mlx, WIDTH, HEIGHT);

	texture.image = mlx_xpm_file_to_image(vars.mlx, "./test.xpm", &texture.w, &texture.h);
	texture.data = (int *)mlx_get_data_addr(texture.image, &texture.bits_per_pixel, &texture.size_len, &texture.endian);
	//int *result = (int *)malloc(sizeof(int) * (texture.w * texture.h));
	//int row = -1;
	//int col;
	//while (++row < texture.h)
	//{
	//	col = -1;
	//	while (++col < texture.w)
	//	{
	//		result[texture.w * row + col] = texture.data[texture.w * row + col];
	//	}
	//}

	int y, x;
	y = HEIGHT - 1;
	while (--y >= 0)
	{
		x = -1;
		while (++x < WIDTH)
		{
			double range1[2];
			double range2[2];

			range1[0] = 0;
			range1[1] = HEIGHT;
			
			range2[0] = 0;
			range2[1] = texture.h;

			int yy = map(y, range1, range2);

			range1[0] = 0;
			range1[1] = WIDTH;
			
			range2[0] = 0;
			range2[1] = texture.w;
			int xx = map(x, range1, range2);
			int color = texture.data[texture.w * yy + xx];

			paint(&vars.img, x, y, color);
		}
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.image, 0, 0);

	//mlx_key_hook(vars.win, key_hook_esc, &vars);
	//mlx_hook(vars.win, 17, 0L, destroy_window, &vars);
	mlx_loop(vars.mlx);
	return (0);
}