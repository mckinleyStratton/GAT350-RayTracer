#pragma once
#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric(const glm::vec3& albedo, float index) : m_albedo{ albedo }, m_index{ index } {}
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const override;

protected:
	glm::vec3 m_albedo{ 1 };
	float m_index{ 1 }; // refraction index
};
