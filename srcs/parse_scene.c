#include "../includes/raytracer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *skip_spaces(char *src)
{
    while (*src && isspace((unsigned char)*src))
        src++;
    return (src);
}

static int parse_vec3(const char *token, t_vec3 *out)
{
    double x;
    double y;
    double z;
    char   sep1;
    char   sep2;

    if (token == NULL)
        return (0);
    if (sscanf(token, " %lf %c %lf %c %lf", &x, &sep1, &y, &sep2, &z) != 5)
        return (0);
    if (sep1 != ',' || sep2 != ',')
        return (0);
    out->x = x;
    out->y = y;
    out->z = z;
    return (1);
}

static int parse_color(const char *token, t_vec3 *out)
{
    int   r;
    int   g;
    int   b;
    char  sep1;
    char  sep2;

    if (token == NULL)
        return (0);
    if (sscanf(token, " %d %c %d %c %d", &r, &sep1, &g, &sep2, &b) != 5)
        return (0);
    if (sep1 != ',' || sep2 != ',')
        return (0);
    if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
        return (0);
    out->x = (double)r;
    out->y = (double)g;
    out->z = (double)b;
    return (1);
}

static int parse_camera_line(char *line, t_scene *scene)
{
    char *pos_token;
    char *dir_token;
    char *fov_token;
    double fov;

    pos_token = strtok(line, " \t\n");
    dir_token = strtok(NULL, " \t\n"); //strtok se souvient de la position dans la chaîne traitée
    fov_token = strtok(NULL, " \t\n");

    if (!pos_token || !dir_token || !fov_token)
        return (0);
    if (!parse_vec3(pos_token, &scene->cam.pos))
        return (0);
    if (!parse_vec3(dir_token, &scene->cam.direction))
        return (0);
    fov = atof(fov_token);
    if (fov <= 0.0 || fov >= 180.0)
        return (0);

    scene->cam = cam_build(scene->cam.pos, scene->cam.direction, fov);
    return (1);
}

static int parse_ambient_line(char *line, t_scene *scene)
{
    char *ratio_token;
    char *color_token;

    ratio_token = strtok(line, " \t\n");
    color_token = strtok(NULL, " \t\n");

    if (!ratio_token || !color_token)
        return (0);
    scene->ambient.ratio = atof(ratio_token);
    if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
        return (0);

    return parse_color(color_token, &scene->ambient.color);
}

static int parse_light_line(char *line, t_scene *scene)
{
    char *pos_token;
    char *ratio_token;
    char *color_token;

    pos_token = strtok(line, " \t\n");
    ratio_token = strtok(NULL, " \t\n");
    color_token = strtok(NULL, " \t\n");

    if (!pos_token || !ratio_token || !color_token)
        return (0);
    if (!parse_vec3(pos_token, &scene->light.pos))
        return (0);
    scene->light.ratio = atof(ratio_token);
    if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
        return (0);

    return parse_color(color_token, &scene->light.color);
}

static t_obj *scene_add_object(t_scene *scene)
{
    t_obj *new_array;

    new_array = realloc(scene->objects, sizeof(t_obj) * (scene->object_count + 1));

    if (new_array == NULL)
        return (NULL);
    scene->objects = new_array;
    return (&scene->objects[scene->object_count++]);
}

static int parse_sphere_line(char *line, t_scene *scene)
{
    char *center_token;
    char *radius_token;
    char *color_token;
    t_obj *obj;

    center_token = strtok(line, " \t\n");
    radius_token = strtok(NULL, " \t\n");
    color_token = strtok(NULL, " \t\n");
    if (!center_token || !radius_token || !color_token)
        return (0);
    obj = scene_add_object(scene);
    if (obj == NULL)
        return (0);
    obj->type = SPHERE;
    if (!parse_vec3(center_token, &obj->shape.sphere.center))
        return (0);
    obj->shape.sphere.radius = atof(radius_token) * 0.5;
    if (obj->shape.sphere.radius <= 0.0)
        return (0);
    return parse_color(color_token, &obj->color);
}

static int parse_plane_line(char *line, t_scene *scene)
{
    char *point_token;
    char *normal_token;
    char *color_token;
    t_obj *obj;

    point_token = strtok(line, " \t\n");
    normal_token = strtok(NULL, " \t\n");
    color_token = strtok(NULL, " \t\n");
    if (!point_token || !normal_token || !color_token)
        return (0);
    obj = scene_add_object(scene);
    if (obj == NULL)
        return (0);
    obj->type = PLANE;
    if (!parse_vec3(point_token, &obj->shape.plane.point))
        return (0);
    if (!parse_vec3(normal_token, &obj->shape.plane.normal))
        return (0);
    return parse_color(color_token, &obj->color);
}

static int parse_cylinder_line(char *line, t_scene *scene)
{
    char *center_token;
    char *normal_token;
    char *radius_token;
    char *height_token;
    t_obj *obj;

    center_token = strtok(line, " \t\n");
    normal_token = strtok(NULL, " \t\n");
    radius_token = strtok(NULL, " \t\n");
    height_token = strtok(NULL, " \t\n");
    if (!center_token || !normal_token || !radius_token || !height_token)
        return (0);
    obj = scene_add_object(scene);
    if (obj == NULL)
        return (0);
    obj->type = CYLINDER;
    if (!parse_vec3(center_token, &obj->shape.cylinder.center))
        return (0);
    if (!parse_vec3(normal_token, &obj->shape.cylinder.normal))
        return (0);
    obj->shape.cylinder.radius = atof(radius_token);
    obj->shape.cylinder.height = atof(height_token);
    if (obj->shape.cylinder.radius <= 0.0 || obj->shape.cylinder.height <= 0.0)
        return (0);
    return 1;
}

static void init_scene(t_scene *scene)
{
    scene->cam = cam_setup();
    scene->ambient.ratio = 0.0;
    vec_set(&scene->ambient.color, 0.0, 0.0, 0.0);
    vec_set(&scene->light.pos, 0.0, 0.0, 0.0);
    scene->light.ratio = 0.0;
    vec_set(&scene->light.color, 0.0, 0.0, 0.0);
    scene->objects = NULL;
    scene->object_count = 0;
}

static void print_object(const t_obj *obj, int index)
{
    if (obj->type == SPHERE)
    {
        printf("Object %d: SPHERE center=%.2f,%.2f,%.2f radius=%.2f color=%.0f,%.0f,%.0f\n",
            index,
            obj->shape.sphere.center.x,
            obj->shape.sphere.center.y,
            obj->shape.sphere.center.z,
            obj->shape.sphere.radius,
            obj->color.x,
            obj->color.y,
            obj->color.z);
    }
    else if (obj->type == PLANE)
    {
        printf("Object %d: PLANE point=%.2f,%.2f,%.2f normal=%.2f,%.2f,%.2f color=%.0f,%.0f,%.0f\n",
            index,
            obj->shape.plane.point.x,
            obj->shape.plane.point.y,
            obj->shape.plane.point.z,
            obj->shape.plane.normal.x,
            obj->shape.plane.normal.y,
            obj->shape.plane.normal.z,
            obj->color.x,
            obj->color.y,
            obj->color.z);
    }
    else if (obj->type == CYLINDER)
    {
        printf("Object %d: CYLINDER center=%.2f,%.2f,%.2f normal=%.2f,%.2f,%.2f radius=%.2f height=%.2f\n",
            index,
            obj->shape.cylinder.center.x,
            obj->shape.cylinder.center.y,
            obj->shape.cylinder.center.z,
            obj->shape.cylinder.normal.x,
            obj->shape.cylinder.normal.y,
            obj->shape.cylinder.normal.z,
            obj->shape.cylinder.radius,
            obj->shape.cylinder.height);
    }
}

static void print_scene(const t_scene *scene)
{
    printf("Camera: pos=%.2f,%.2f,%.2f dir=%.2f,%.2f,%.2f fov=%.2f\n",
        scene->cam.pos.x,
        scene->cam.pos.y,
        scene->cam.pos.z,
        scene->cam.direction.x,
        scene->cam.direction.y,
        scene->cam.direction.z,
        scene->cam.fov);
    printf("Ambient: ratio=%.2f color=%.0f,%.0f,%.0f\n",
        scene->ambient.ratio,
        scene->ambient.color.x,
        scene->ambient.color.y,
        scene->ambient.color.z);
    printf("Light: pos=%.2f,%.2f,%.2f ratio=%.2f color=%.0f,%.0f,%.0f\n",
        scene->light.pos.x,
        scene->light.pos.y,
        scene->light.pos.z,
        scene->light.ratio,
        scene->light.color.x,
        scene->light.color.y,
        scene->light.color.z);
    printf("Objects: %d\n", scene->object_count);
    for (int i = 0; i < scene->object_count; i++)
        print_object(&scene->objects[i], i);
}

t_scene parser(const char *scene_path)
{
    t_scene scene;
    char    line[256];
    FILE   *file;
    char    id[16];
    int     consumed;
    char   *content;

    file = fopen(scene_path, "r");
    if (file == NULL)
    {
        perror(scene_path);
        exit(EXIT_FAILURE);
    }
    init_scene(&scene);
    while (fgets(line, sizeof(line), file) != NULL)
    {
        content = skip_spaces(line);
        if (*content == '\0' || *content == '\n' || *content == '#')
            continue;
        if (sscanf(content, "%15s%n", id, &consumed) != 1)
            continue;
        content += consumed; //on décale la chaine pour bien isolé id et content
        content = skip_spaces(content);

        if (strcmp(id, "C") == 0)
        {
            if (!parse_camera_line(content, &scene))
                fprintf(stderr, "Erreur: ligne Camera invalide\n");
        }
        else if (strcmp(id, "A") == 0)
        {
            if (!parse_ambient_line(content, &scene))
                fprintf(stderr, "Erreur: ligne Ambient invalide\n");
        }
        else if (strcmp(id, "L") == 0)
        {
            if (!parse_light_line(content, &scene))
                fprintf(stderr, "Erreur: ligne Light invalide\n");
        }
        else if (strcmp(id, "sp") == 0)
        {
            if (!parse_sphere_line(content, &scene))
                fprintf(stderr, "Erreur: ligne Sphere invalide\n");
        }
        else if (strcmp(id, "pl") == 0)
        {
            if (!parse_plane_line(content, &scene))
                fprintf(stderr, "Erreur: ligne Plane invalide\n");
        }
        else if (strcmp(id, "cy") == 0)
        {
            if (!parse_cylinder_line(content, &scene))
                fprintf(stderr, "Erreur: ligne Cylinder invalide\n");
        }
    }
    fclose(file);
    print_scene(&scene);
    return (scene);
}
