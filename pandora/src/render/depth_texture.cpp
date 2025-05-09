#include "render/depth_texture.hpp"

namespace WingsOfSteel::Pandora
{

DepthTexture::DepthTexture()
{
    
}

DepthTexture::DepthTexture(wgpu::Device& device, uint32_t width, uint32_t height, const std::string& label)
{
    wgpu::TextureDescriptor textureDesc{
        .label = label.c_str(),
        .usage = wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::TextureBinding,
        .dimension = wgpu::TextureDimension::e2D,
        .size{
            .width = width,
            .height = height,
            .depthOrArrayLayers = 1
        },
        .format = wgpu::TextureFormat::Depth32Float
    };

    m_Texture = device.CreateTexture(&textureDesc);
    m_TextureView = m_Texture.CreateView();

    wgpu::SamplerDescriptor samplerDesc{
        .magFilter = wgpu::FilterMode::Linear,
        .minFilter = wgpu::FilterMode::Linear,
        .compare = wgpu::CompareFunction::LessEqual
    };
    m_Sampler = device.CreateSampler(&samplerDesc);
}

DepthTexture::~DepthTexture()
{

}

} // namespace WingsOfSteel::Pandora
