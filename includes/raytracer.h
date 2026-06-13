#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

// --- STRUCTURES ---

typedef struct s_vars {
    void    *mlx;
    void    *win;
}              t_vars;

typedef struct s_img {
    void    *img_ptr;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
}              t_img;

typedef struct s_vec3 {
    double  x;
    double  y;
    double  z;
}              t_vec3;

// --- PROTOTYPES DES FONCTIONS ---

t_vec3  vec_add(t_vec3 v1, t_vec3 v2);
t_vec3  vec_sub(t_vec3 v1, t_vec3 v2);

#endif