#include <vector>

#include <render/debug_render.hpp>
#include <pandora.hpp>

#include "sector/phenomena/asteroid_field.hpp"
#include "sector/signal/asteroid_field_signal.hpp"

// to remove
#include <scene/camera.hpp>
#include <scene/scene.hpp>
#include <render/window.hpp>

namespace WingsOfSteel::TheBrightestStar
{

AsteroidField::AsteroidField(const AsteroidFieldSignal* pSignal)
: m_pSignal(pSignal)
{

}

AsteroidField::~AsteroidField()
{

}

void AsteroidField::OnAddedToScene(Pandora::Scene* pScene)
{
    Pandora::Entity::OnAddedToScene(pScene);
}

void AsteroidField::Update(float delta) 
{
    Pandora::Entity::Update(delta);

    Pandora::GetDebugRender()->Circle(
        m_pSignal->GetPosition(),
        glm::vec3(0.0f, 1.0f, 0.0f),
        Pandora::Color::Green,
        20.0f,
        20.0f
    );

    using namespace Pandora;
    Camera* pCamera = GetActiveScene() ? GetActiveScene()->GetCamera() : nullptr;
    if (pCamera)
    {
        const glm::mat4 viewProjection = pCamera->GetProjectionMatrix() * pCamera->GetViewMatrix();
        GetDebugRender()->ProjectedText(m_pSignal->GetName(), m_pSignal->GetPosition(), Color::White, viewProjection, 0, 0, GetWindow()->GetWidth(), GetWindow()->GetHeight());
    }
}

void AsteroidField::Render(wgpu::RenderPassEncoder renderPass)
{
    Pandora::Entity::Render(renderPass);
}

} // namespace WingsOfSteel::TheBrightestStar