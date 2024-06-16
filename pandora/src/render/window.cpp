#if defined(TARGET_PLATFORM_NATIVE)
#include <webgpu/webgpu_glfw.h>
#elif defined(TARGET_PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#include "render/window.hpp"

#include "render/rendersystem.hpp"
#include "pandora.hpp"

namespace WingsOfSteel::Pandora
{

Window::Window()
: m_pWindow(nullptr)
{
    m_Width = 512;
    m_Height = 512;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_pWindow = glfwCreateWindow(m_Width, m_Height, "The Brightest Star", nullptr, nullptr);
    ConfigureSurface();
}

Window::~Window()
{

}

wgpu::Surface Window::GetSurface() const
{
    return m_pSurface;
}

wgpu::TextureFormat Window::GetTextureFormat() const
{
    return m_Format;
}

GLFWwindow* Window::GetRawWindow() const
{
    return m_pWindow;
}

void Window::ConfigureSurface()
{
#if defined(TARGET_PLATFORM_NATIVE)
    m_pSurface = wgpu::glfw::CreateSurfaceForWindow(GetRenderSystem()->GetInstance(), m_pWindow);
#elif defined(TARGET_PLATFORM_WEB)
    wgpu::SurfaceDescriptorFromCanvasHTMLSelector canvasDesc{};
    canvasDesc.selector = "#canvas";

    wgpu::SurfaceDescriptor surfaceDesc{.nextInChain = &canvasDesc};

    m_pSurface = GetRenderSystem()->GetInstance().CreateSurface(&surfaceDesc);
#endif

    wgpu::SurfaceCapabilities capabilities;
    m_pSurface.GetCapabilities(GetRenderSystem()->GetAdapter(), &capabilities);
    m_Format = capabilities.formats[0];

    wgpu::SurfaceConfiguration config{
        .device = GetRenderSystem()->GetDevice(),
        .format = m_Format,
        .width = m_Width,
        .height = m_Height
    };
    m_pSurface.Configure(&config);
}

} // namespace WingsOfSteel::Pandora