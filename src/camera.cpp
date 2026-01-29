#include "Camera.h"

using namespace linalg;

void Camera::MoveTo(const vec3f& position) noexcept
{
	m_position = position;
}

void Camera::Move(const vec3f& direction) noexcept
{
	m_position += direction;
}

void Camera::RotateCamera(long mouse_dx, long mouse_dy) noexcept 
{
	m_yaw += m_mouse_sensitivity * static_cast<float>(mouse_dx);
	m_pitch += m_mouse_sensitivity * static_cast<float>(mouse_dy);



}

mat4f Camera::RotationMatrix() const noexcept 
{
	return mat4f::rotation(0.0f, m_yaw, m_pitch);
}

mat4f Camera::WorldToViewMatrix() const noexcept
{
	
	//inverse(T(p)* R) = inverse(R) * inverse(T(p)) = transpose(R) * T(-p)
	const mat4f R = RotationMatrix();
	const mat4f R_inv = transpose(R);
	const mat4f T_inv = mat4f::translation(-m_position);
	return R_inv * T_inv;
}


mat4f Camera::ProjectionMatrix() const noexcept
{
	return mat4f::projection(m_vertical_fov, m_aspect_ratio, m_near_plane, m_far_plane);
}

