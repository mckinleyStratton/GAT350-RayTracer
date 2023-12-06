#include "Camera.h"
#include "MathUtils.h"
#include <iostream>

Camera::Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectRatio) :
	m_fov{ fov },
	m_aspectRatio{ aspectRatio }{
	LookAt(eye, target, up);
}

void Camera::LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
	m_eye = eye;
	m_forward = glm::normalize(eye - target);
	m_right = glm::normalize(glm::cross(up, m_forward));
	m_up = glm::normalize(glm::cross(m_forward, m_right));

	CalculateViewPlane();
}

void Camera::CalculateViewPlane()
{
	float theta = glm::radians(m_fov);
	float halfHeight = tan(theta * 0.5f);
	float height = 2.0f * halfHeight;
	float width = height * m_aspectRatio;

	m_horizontal = m_right * width;
	m_vertical = m_up * height;
	m_lowerLeft = m_eye - (m_right * 0.5f) - (m_up * 0.5f) - m_forward;
}

ray_t Camera::GetRay(const glm::vec2& point) const
{
	ray_t ray;
	ray.origin = m_eye;
	ray.direction = glm::normalize(m_lowerLeft + (m_horizontal * point.x) + (m_vertical * point.y) - m_eye);

	return ray;
}


