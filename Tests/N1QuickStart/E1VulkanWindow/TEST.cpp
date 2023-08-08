#include <gtest/gtest.h>
#include <QGuiApplication>
#include <QLoggingCategory>
#include <QVulkanInstance>
#include <vulkan/vulkan.hpp>
#include "VulkanRenderer.h"

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE   // ����Vulkan - HPP �Ķ�̬������

Q_LOGGING_CATEGORY(lcVk, "qt.vulkan")   // ����Qt����־

    class VulkanWindow : public QVulkanWindow
{   // Qt ��װ��Vulkan����
public:
    VulkanWindow()
    {
        QVector<int> sampleCounts = supportedSampleCounts();
        if (!sampleCounts.isEmpty()) {
            setSampleCount(sampleCounts.back());
        }
    }
    QVulkanWindowRenderer* createRenderer() override { return new VulkanRenderer(this); }
};
TEST(N1QuickStart, E1VulkanWindow)
{
    int          argc = 1;
    std::array<char*, 1> argv = {"asdasdas"};
    QGuiApplication app(argc, argv.data());

    static vk::DynamicLoader  dynamicLoader;   // ����HPP
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        dynamicLoader.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
    VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);

    QVulkanInstance instance;                              // ����vulkanʵ��
    instance.setLayers({"VK_LAYER_KHRONOS_validation"});   // ������֤��
    if (!instance.create()) qFatal("Failed to create Vulkan instance: %d", instance.errorCode());
    VULKAN_HPP_DEFAULT_DISPATCHER.init(instance.vkInstance());   // ��ʼ��vulkan hpp

    QLoggingCategory::setFilterRules(
        QStringLiteral("qt.vulkan=true"));   // ����Qt��־ϵͳ�Ĺ��˹�����ʾvulkan��־��

    VulkanWindow vkWindow;
    vkWindow.setVulkanInstance(&instance);   // ���ô��ڵ�Vulkanʵ��
    vkWindow.resize(1024, 768);              // ���ô��ڳߴ�
    vkWindow.show();                         // ��ʾ����

    app.exec();
}