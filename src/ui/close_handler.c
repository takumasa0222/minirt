#include "../../includes/parser.h"
#include "../../includes/ui.h"
#include <mlx.h>
#include <stdlib.h>

int	close_btn_click(t_mlx_env *mlx)
{
	t_env	*env;
	t_obj	*obj;

	if (mlx->img)
		free(mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	env = set_get_env(GET, NULL);
	obj = set_get_obj(GET, NULL);
	free_lit(env->lit);
	free(env);
	free_obj(obj);
	exit(0);
}
