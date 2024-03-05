#pragma once

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtc/quaternion.hpp> // glm::quat
#include <glm/gtx/quaternion.hpp> // glm::toMat


class Camera
{
public:
	static Camera& Instance()
	{
		static Camera* instance = new Camera();
		return *instance;
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::inverse(glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(m_Rotation));
	}

	glm::mat4 GetProjectionMatrix()
	{
		return m_ProjectionMatrix;
	}

	glm::mat4 GetViewProjection()
	{
		return m_ProjectionMatrix * GetViewMatrix();
	}

	glm::mat4 GetRotationMatrix()
	{
		return glm::inverse(toMat4(m_Rotation));
	}

	glm::vec3 GetPosition()
	{
		return m_Position;
	}

	Camera& SetFoV(float vfov)
	{
		m_VFoV = vfov;
		glm::perspective(m_VFoV, m_Aspect, 0.1f, 10000.0f);
		return Instance();
	}

	Camera& SetAspect(float aspect)
	{
		m_Aspect = aspect;
		glm::perspective(m_VFoV, m_Aspect, 0.1f, 10000.0f);
		return Instance();
	}

	Camera& MoveForward(float offset)
	{
		glm::vec3 direction = m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f);
		m_Position += direction * offset;
		return Instance();
	}

	Camera& MoveRight(float offset)
	{
		glm::vec3 direction = m_Rotation * glm::vec3(1.0f, 0.0f, 0.0f);
		m_Position += direction * offset;
		return Instance();
	}

	Camera& MoveUp(float offset)
	{
		glm::vec3 direction = m_Rotation * glm::vec3(0.0f, 1.0f, 0.0f);
		m_Position += direction * offset;
		return Instance();
	}

	Camera& Rotate(float pitch, float yaw)
	{
		m_Rotation = glm::angleAxis(glm::radians(-yaw * 0.1f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(m_Rotation, glm::radians(pitch * 0.1f), glm::vec3(1.0f, 0.0f, 0.0f));
		return Instance();
	}

private:
	float m_VFoV = glm::pi<float>() * 0.25f;
	float m_Aspect = 16.0f / 9.0f;

	glm::vec3 m_Position = glm::vec3(0.0f);
	glm::quat m_Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	glm::mat4 m_ProjectionMatrix = glm::perspective(m_VFoV, m_Aspect, 0.1f, 1000.0f);
};

