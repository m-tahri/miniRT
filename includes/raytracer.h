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

typedef struct s_ray {
    t_vec3  origin;
    t_vec3  direction;
}              t_ray;

typedef struct s_cam {
    t_vec3  pos; // pos de l'oeil
    t_vec3  direction; // où regarde la cam
    double fov; // !!! angle en degré
    t_vec3 horizontal; // norme = largeur viewport
    t_vec3 vertical; // norme = longueur viewport
    t_vec3 lower_left_corner; //pos du pt en bas à gauche du viewport
}              t_cam;


// --- PROTOTYPES DES FONCTIONS ---

t_vec3  vec_add(t_vec3 v1, t_vec3 v2);
t_vec3  vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3  vec_scale(t_vec3 v, double t);
double  vec_dot(t_vec3 v1, t_vec3 v2);
t_vec3  vec_normalize(t_vec3 v);
void    vec_set(t_vec3 *v, double x, double y, double z);
t_cam   cam_setup(void);
t_ray   ray_create(t_vec3 origin, t_vec3 direction);
int     ray_test_color(t_ray r);

#endif