#pragma once

#include <QVulkanWindowRenderer>
#include <vulkan\vulkan.hpp>

class VulkanRenderer : public QVulkanWindowRenderer
{   // Vulkan ��Ⱦ��
public:
    VulkanRenderer(QVulkanWindow* window);

    void initResources() override;      // ����vulkan��Դ
    void releaseResources() override;   // �ͷ�vulkan��Դ

    void initSwapChainResources() override;      // ������������Դ
    void releaseSwapChainResources() override;   // �ͷŽ�������Դ

    void startNextFrame() override;   // ��ʼ��һ֡�Ļ���

private:
    QVulkanWindow* window_;
};