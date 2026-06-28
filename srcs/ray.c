#include "../includes/raytracer.h"

t_ray ray_create(t_vec3 origin, t_vec3 direction)
{
    t_ray   ray;

    ray.direction = vec_normalize(direction);
    ray.origin = origin;
    return (ray);
};

#include "../includes/raytracer.h"

t_cam   setup_cam(void)
{
    t_cam   cam;
    double  aspect_ratio;
    double  viewport_height;
    double  viewport_width;
    t_vec3  forward;

    vec_set(&cam.pos, 0.0, 0.0, 0.0);
    vec_set(&cam.direction, 0.0, 0.0, -1.0);
    cam.fov = 90.0;

    // Calcul des dimensions du Viewport (ratio 16:9)
    aspect_ratio = 16.0 / 9.0;
    viewport_height = 2.0;
    viewport_width = aspect_ratio * viewport_height;

    // Définition des vecteurs horizontal et vertical
    vec_set(&cam.horizontal, viewport_width, 0.0, 0.0);
    vec_set(&cam.vertical, 0.0, viewport_height, 0.0);

    // Calcul du lower_left_corner
    // Origine + Direction - (Horizontal / 2) - (Vertical / 2)
    forward = cam.direction;
    
    cam.lower_left_corner = vec_add(cam.pos, forward);
    cam.lower_left_corner = vec_sub(cam.lower_left_corner, vec_scale(cam.horizontal, 0.5));
    cam.lower_left_corner = vec_sub(cam.lower_left_corner, vec_scale(cam.vertical, 0.5));

    return (cam);
}