
#ifndef UI_H
# define UI_H
#include "./raytracing.h"
#include "./parser.h"

# define W_WIDTH 800
# define W_HEIGHT 450
# define WIN_TITLE "minirt"
# define DESTROY_NOTIFY 17

typedef struct s_mlx_env
{
	void *mlx;
	void *window;
}	t_mlx_env;

int	close_btn_click(t_mlx_env *mlx);
int	init_window(t_obj *data, t_env *env);

#endif