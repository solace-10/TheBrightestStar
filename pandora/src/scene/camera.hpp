#pragma once

#include <glm/vec3.hpp>

#include "scene/entity.hpp"

namespace WingsOfSteel::Pandora
{

class Camera
{
public:
    Camera(float fov, float nearPlane, float farPlane);
    ~Camera();

    void LookAt(const glm::vec3& cameraPosition, const glm::vec3& targetPosition, const glm::vec3& up);
    
    void SetNearPlane(float distance);
    float GetNearPlane() const;
    void SetFarPlane(float distance);
    float GetFarPlane() const;
    void SetFieldOfView(float degrees);
    float GetFieldOfView() const;
    
    const glm::mat4& GetViewMatrix() const;
    const glm::mat4& GetProjectionMatrix() const;

private:
    void CalculateProjectionMatrix();

    float m_Fov = 45.0f;
    float m_NearPlane = 0.01f;
    float m_FarPlane = 100.0f;
    glm::mat4 m_ViewMatrix { 1.0f };
    glm::mat4 m_ProjectionMatrix { 1.0f };
};

} // namespace WingsOfSteel::Pandora