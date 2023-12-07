#include "Scene.h"
#include "Canvas.h"
#include "Camera.h"
#include "Color.h"
#include "MathUtils.h"
#include "Ray.h"
#include "Random.h"
#include <iostream>

void Scene::Render(Canvas& canvas, int numSamples)
{
	for (int y = 0; y < canvas.GetSize().y; y++) {
		for (int x = 0; x < canvas.GetSize().x; x++) {

			glm::vec2 pixel = glm::vec2{ x, y };

			color3_t color{ 1, 0, 0 };

			for (int sample = 0; sample < numSamples; sample++)
			{	
				glm::vec2 point = (pixel + glm::vec2{ random01(), random01() }) / glm::vec2(canvas.GetSize().x, canvas.GetSize().y);

				point.y = 1.0f - point.y;
				ray_t ray = m_camera->GetRay(point);

				raycastHit_t raycastHit;
				color += Trace(ray, 0, 100, raycastHit, m_depth);
			}
			color /= numSamples;

			canvas.DrawPoint(pixel, color4_t(color, 1));
		}
	}
}

color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth)
{
	bool rayHit = false;
	float closestDistance = maxDistance;

	for (const auto& object : m_objects)
	{
		if (object->Hit(ray, minDistance, closestDistance, raycastHit))
		{
			rayHit = true;
			closestDistance = raycastHit.distance;
		}
	}

	if (rayHit)
	{
		ray_t scattered;
		color3_t color;

		if (depth > 0 && raycastHit.material->Scatter(ray, raycastHit, color, scattered))
		{
			return color * Trace(scattered, minDistance, maxDistance, raycastHit, depth -1);
		}
		else
		{
			return raycastHit.material->GetEmissive();
		}
	}
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f;
	color3_t color = lerp(m_bottomColor, m_topColor, t);

	return color;
}


