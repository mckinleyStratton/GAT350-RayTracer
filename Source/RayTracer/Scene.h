#pragma once
#include "Color.h"
#include "Camera.h"
#include "Object.h"

#include <memory>
#include <vector>

class Scene
{
public:
	Scene() = default;
	Scene(int depth = 5) : m_depth{ depth } {}
	Scene(const color3_t& topColor, const color3_t& bottomColor) :
		m_topColor{ topColor },
		m_bottomColor{ bottomColor }
	{}
	Scene(int depth, const color3_t& topColor, const color3_t& bottomColor) :
		m_depth{ depth },
		m_topColor{ topColor },
		m_bottomColor{ bottomColor }
	{}

	void Render(class Canvas& canvas, int numSamples, int depth);

	color3_t Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth);
	void AddObject(std::unique_ptr<Object> object) { m_objects.push_back(std::move(object)); }

	void SetCamera(std::shared_ptr<Camera> camera)
	{
		m_camera = camera;
	}


private:
	std::shared_ptr<Camera> m_camera;
	std::vector<std::unique_ptr<Object>> m_objects;

	color3_t m_topColor{ 0 };
	color3_t m_bottomColor{ 1 };
	int m_depth{ 5 };
};