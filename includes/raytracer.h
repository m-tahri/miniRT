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
    double  fov; // !!! angle en degré
    t_vec3 horizontal; // norme = largeur viewport
    t_vec3 vertical; // norme = longueur viewport
    t_vec3 lower_left_corner; //pos du pt en bas à gauche du viewport
}              t_cam;

typedef struct s_ambient {
    double  ratio;      // Intensité [0.0, 1.0]
    t_vec3  color;     
}              t_ambient;

typedef struct s_light {
    t_vec3  pos;        
    double  ratio;      // Intensité [0.0, 1.0]
    t_vec3  color;
}              t_light;

typedef struct s_sphere {
    t_vec3  center;
    double  radius;     
}              t_sphere;

typedef struct s_plane {
    t_vec3  point;      
    t_vec3  normal;
}              t_plane;

typedef struct s_cylinder {
    t_vec3  center;
    t_vec3  normal;     //axe du cylindre
    double  radius;
    double  height;
}              t_cylinder;

typedef enum e_type {
    SPHERE,
    PLANE,
    CYLINDER
}            t_type;

typedef struct s_obj {
    t_type type;
    t_vec3 color;
    union {
        t_sphere    sphere;
        t_plane     plane;
        t_cylinder  cylinder;
    } shape;
}              t_obj;

typedef struct s_scene{
    t_cam      cam;
    t_ambient  ambient;
    t_light    light;
    t_obj      *objects;
    int        object_count;
}               t_scene;

// --- PROTOTYPES DES FONCTIONS ---

t_vec3  vec_add(t_vec3 v1, t_vec3 v2);
t_vec3  vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3  vec_scale(t_vec3 v, double t);
double  vec_dot(t_vec3 v1, t_vec3 v2);
t_vec3  vec_normalize(t_vec3 v);
void    vec_set(t_vec3 *v, double x, double y, double z);
t_cam   cam_setup(void);
t_cam   cam_build(t_vec3 pos, t_vec3 forward, double fov);
t_ray   ray_create(t_vec3 origin, t_vec3 direction);
int     background_color(t_ray r);
t_scene parser(const char *scene_path);

#endif