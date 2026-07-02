#include "../includes/raytracer.h"

t_ray ray_create(t_vec3 origin, t_vec3 direction)
{
    t_ray   ray;

    ray.direction = vec_normalize(direction);
    ray.origin = origin;
    return (ray);
};


t_cam   cam_setup(void)
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

t_cam cam_build(t_vec3 pos, t_vec3 forward, double fov)
{
    t_cam cam;
    double aspect_ratio;
    double theta;
    double viewport_height;
    double viewport_width;

    cam.pos = pos;
    cam.direction = vec_normalize(forward);
    cam.fov = fov;
    aspect_ratio = 16.0 / 9.0;
    theta = fov * 3.14159265358979323846 / 180.0;
    viewport_height = 2.0 * tan(theta * 0.5);
    viewport_width = aspect_ratio * viewport_height;
    vec_set(&cam.horizontal, viewport_width, 0.0, 0.0);
    vec_set(&cam.vertical, 0.0, viewport_height, 0.0);
    cam.lower_left_corner = vec_add(cam.pos, cam.direction);
    cam.lower_left_corner = vec_sub(cam.lower_left_corner, vec_scale(cam.horizontal, 0.5));
    cam.lower_left_corner = vec_sub(cam.lower_left_corner, vec_scale(cam.vertical, 0.5));
    return (cam);
}

int background_color(t_ray r)
{
    // r.direction est déjà normalisé grâce à ray_create, donc son Y est entre -1.0 et 1.0.
    // On transforme cet intervalle en un float 't' entre 0.0 et 1.0.
    double t = 0.5 * (r.direction.y + 1.0);

    // Interpolation linéaire (Lerp) entre le Blanc (1.0, 1.0, 1.0) et le Bleu Ciel (0.5, 0.7, 1.0)
    // Formule : (1.0 - t) * Couleur_Blanche + t * Couleur_Bleue
    double r_color = (1.0 - t) * 1.0 + t * 0.5;
    double g_color = (1.0 - t) * 1.0 + t * 0.7;
    double b_color = (1.0 - t) * 1.0 + t * 1.0;

    // Conversion des channels (0.0 à 1.0) en entiers (0 à 255)
    int ir = (int)(255.999 * r_color);
    int ig = (int)(255.999 * g_color);
    int ib = (int)(255.999 * b_color);

    // On assemble le tout au format TRGB pour la MiniLibX
    return (ir << 16 | ig << 8 | ib);
}