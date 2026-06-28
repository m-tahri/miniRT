#include "../mlx/mlx.h"
#include "../includes/raytracer.h" // Donne accès aux structures t_vars, t_img et t_vec3
#include <stdio.h>
#include <stdlib.h>

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

void fast_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;
    dst = img->addr + (y * img->line_length + x * (img->bpp / 8)); // changement de l'adresse
    *(unsigned int*)dst = color; 
    // à l'adresse dst on considère maintenant un bloc de 4 octet au lieu de 1 et on y associe color
}

void test_img_rouge(t_img* img, int width, int height)
{
    int A = 0;
    int R = 0; 
    int G = 255;   
    int B = 0;   
    int color = (A << 24) | (R << 16) | (G << 8) | B; // Calculé une seule fois hors de la boucle

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++){
            fast_mlx_pixel_put(img, x, y, color);
        }
    }
}

int main(void)
{
    t_vars  vars;
    t_img   img;
    int width = 1280;
    int height = 720;
    
    vars.mlx = mlx_init();
    if (!vars.mlx)
    {
        printf("Erreur : Impossible d'initialiser la MLX\n");
        return (1);
    }
    
    vars.win = mlx_new_window(vars.mlx, width, height, "Raytracer");
    if (!vars.win)
        return (1);

    img.img_ptr = mlx_new_image(vars.mlx, width, height);
    img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_length, &img.endian);

    test_img_rouge(&img, width, height);
    mlx_put_image_to_window(vars.mlx, vars.win, img.img_ptr, 0, 0);

    // ----------Fermeture Win----------
    mlx_key_hook(vars.win, esc_win, &vars);
    mlx_hook(vars.win, 17, 0L, (void *) cross_esc_win, &vars); 
    // (void *) obligatoire sinon gcc ne veut pas compiler correctement => typr incompatible.
    
    // ----------LOOP----------
    mlx_loop(vars.mlx);
    return (0);
}