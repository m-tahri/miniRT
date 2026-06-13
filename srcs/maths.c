#include "../includes/raytracer.h"

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