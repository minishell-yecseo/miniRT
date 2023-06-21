#include "miniRT.h"

void	v(void)
{
	system("leaks --list -- $PPID");
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	atexit(v);
	// argument checking
	vars.mlx = mlx_init();
	if (!check_args(argc, argv, &vars))
		exit(0);
	// mlx setting
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	vars.img.image = mlx_new_image(vars.mlx, WIDTH, HEIGHT);

	// drawing
	test(&(vars.img), &vars);
	mlx_key_hook(vars.win, key_hook_esc, &vars);
	mlx_hook(vars.win, 17, 0L, destroy_window, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

int	destroy_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}
