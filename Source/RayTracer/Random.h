#pragma once
#include <stdlib.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>


static void seedRandom(unsigned int seed)
{
	srand(seed);
}

static float random01()
{
	return (float)rand() / RAND_MAX;
}

static float random(float min, float max)
{
	if (min > max)
	{
		std::swap(min, max);
	}
	float randomFraction = (float)rand() / RAND_MAX;
	return min + randomFraction * (max - min);
}
static inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max)
{  
	return glm::vec3(random(min.x, max.x), random(min.y, max.y), random(min.z, max.z));
}

static inline glm::vec3 randomInUnitSphere()
{
	glm::vec3 v;
	do
	{
		v = random(glm::vec3(-1.0f), glm::vec3(1.0f));

	} while (glm::length2(v) >= 1.0f);

	return v;
}
