#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include "../../includes/ui.h"

int	init_window(t_data *data, t_env *env)
{
	t_mlx_env	mlx;

	(void)data;
	(void)env;

	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, W_WIDTH, W_HEIGHT, WIN_TITLE);
	//mlx_hook(mlx.window, DESTROY_NOTIFY, 0, close_btn_click, &mlx);
	mlx_loop(mlx.mlx);
	mlx_hook(mlx.window, DESTROY_NOTIFY, 0, close_btn_click, &mlx);
	return (EXIT_SUCCESS);
}

