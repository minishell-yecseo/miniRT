#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_vars	*vars;

	vars = (t_vars *) malloc(sizeof(t_vars));
	if (!vars)
		exit(0);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "fractol");
	vars->img.image = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	color_image(&(vars->img), vars);
	mlx_key_hook(vars->win, key_hook_esc, vars);
	mlx_hook(vars->win, 17, 0L, destroy_window, vars);
	mlx_loop(vars->mlx);
	return (0);
}

int	destroy_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}
