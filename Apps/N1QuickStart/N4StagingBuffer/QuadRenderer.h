#pragma once

#include <QVulkanWindowRenderer>
#include <vulkan\vulkan.hpp>

class QuadRenderer : public QVulkanWindowRenderer
{
public:
    QuadRenderer(QVulkanWindow* window);
    void initResources() override;
    void initSwapChainResources() override;
    void releaseSwapChainResources() override;
    void releaseResources() override;
    void startNextFrame() override;

private:
    QVulkanWindow*   window_ = nullptr;

    vk::Buffer       singleBuffer_;
    vk::DeviceMemory singleDevMemory_;

    vk::DescriptorBufferInfo vertexBufferInfo_;
    vk::DescriptorBufferInfo indexBufferInfo_;
    vk::DescriptorBufferInfo uniformBufferInfo_[QVulkanWindow::MAX_CONCURRENT_FRAME_COUNT];

    vk::PipelineCache  piplineCache_;
    vk::PipelineLayout piplineLayout_;
    vk::Pipeline       pipline_;
};
