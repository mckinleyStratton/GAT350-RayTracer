#include "Plane.h"
#include "MathUtils.h"
#include "Material.h"

#include <iostream>


bool Plane::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit)
{
    float denominator = dot(ray.direction, m_normal);
    if (approximately(denominator, 0.0f))
    {
        return false;
    }

    float t = glm::dot(m_center - ray.origin, m_normal) / denominator;
    if (t < 0)
    {
        return false;
    }

    if (t <= minDistance || t >= maxDistance)
    {
        return false;
    }

    raycastHit.distance = t;

    raycastHit.point = ray.At(t);

    raycastHit.normal = glm::normalize(m_normal);
    raycastHit.material = GetMaterial();

    return true;
}