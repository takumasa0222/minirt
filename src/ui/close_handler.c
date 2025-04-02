#include "../../includes/parser.h"
#include "../../includes/ui.h"
#include <mlx.h>
#include <stdlib.h>

int	close_btn_click(t_mlx_env *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx);
	return (0);
}
