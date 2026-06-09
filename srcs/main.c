#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;


int esc_win(int keycode, void *void_vars)
{
    t_vars *vars = (t_vars *)void_vars;
    
    if (keycode == 65307)
    {
        mlx_loop_end(vars->mlx);
    }
    return (0);
}


int cross_esc_win(void *void_vars)
{
    t_vars *vars = (t_vars *)void_vars;
    mlx_loop_end(vars->mlx);
    return (0);
}



int main(void)
{
    t_vars vars;

    vars.mlx = mlx_init();
    if (!vars.mlx)
    {
        printf("Erreur : Impossible d'initialiser la MLX\n");
        return (1);
    }
    
    vars.win = mlx_new_window(vars.mlx, 800, 600, "Raytracer");
    if (!vars.win)
        return (1);


    // ----------Fermeture Win----------
    mlx_key_hook(vars.win, esc_win, &vars);
    mlx_hook(vars.win, 17, 0L, (void *) cross_esc_win, &vars); 
    // (void *) obligatoire sinon gcc ne veut pas compiler correctement => typr incompatible.
    
    // ----------LOOP----------
    mlx_loop(vars.mlx);
    return (0);
}

