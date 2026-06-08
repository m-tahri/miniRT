#include "../mlx/mlx.h"
#include <stdlib.h>

int main(void)
{
    void    *mlx_ptr;
    void    *win_ptr;

    // Initialisation de la connexion avec le serveur graphique
    mlx_ptr = mlx_init();
    if (!mlx_ptr)
        return (1);
        
    // Ouverture d'une fenêtre de 800x600 pixels
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Mon miniRT");
    if (!win_ptr)
        return (1);

    // Boucle infinie pour maintenir la fenêtre ouverte
    mlx_loop(mlx_ptr);
    return (0);
}