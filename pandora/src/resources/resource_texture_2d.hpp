#pragma once

#include "resources/resource.hpp"

#include <webgpu/webgpu_cpp.h>

namespace WingsOfSteel::Pandora
{

class ResourceTexture2D : public Resource
{
public:
    ResourceTexture2D();
    ~ResourceTexture2D() override;

    void Load(const std::string& path) override;
    ResourceType GetResourceType() const override;

    wgpu::TextureView GetTextureView() const;

private:
    void LoadInternal(FileReadResult result, FileSharedPtr pFile);

    wgpu::Texture m_Texture;
    wgpu::TextureView m_TextureView;
    int m_Width;
    int m_Height;
    int m_Channels;
};

} // namespace WingsOfSteel::Pandora