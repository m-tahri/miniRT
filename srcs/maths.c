#include "../includes/raytracer.h"


void   vec_set(t_vec3 *v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

t_vec3  vec_add(t_vec3 v1, t_vec3 v2)
{
    t_vec3  res;

    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;
    res.z = v1.z + v2.z;
    return (res);
}

t_vec3  vec_sub(t_vec3 v1, t_vec3 v2)
{
    t_vec3  res;

    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;
    res.z = v1.z - v2.z;
    return (res);
}


// Multiplie un vecteur par un nombre (double)
t_vec3  vec_scale(t_vec3 v, double t)
{
    t_vec3  res;

    res.x = v.x * t;
    res.y = v.y * t;
    res.z = v.z * t;
    return (res);
}

double  vec_dot(t_vec3 v1, t_vec3 v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3  vec_normalize(t_vec3 v)
{
    t_vec3  res;
    double  len;
    len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (len == 0)
        return (v);
    res.x = v.x / len;
    res.y = v.y / len;
    res.z = v.z / len;
    return (res);
}