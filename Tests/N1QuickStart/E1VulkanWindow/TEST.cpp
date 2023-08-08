#include <gtest/gtest.h>
#include <QGuiApplication>
#include <QLoggingCategory>
#include <QVulkanInstance>
#include <vulkan/vulkan.hpp>
#include "VulkanRenderer.h"

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE   // 定义Vulkan - HPP 的动态加载器

Q_LOGGING_CATEGORY(lcVk, "qt.vulkan")   // 开启Qt的日志

    class VulkanWindow : public QVulkanWindow
{   // Qt 封装的Vulkan窗口
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

    static vk::DynamicLoader  dynamicLoader;   // 加载HPP
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        dynamicLoader.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
    VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);

    QVulkanInstance instance;                              // 创建vulkan实例
    instance.setLayers({"VK_LAYER_KHRONOS_validation"});   // 开启验证层
    if (!instance.create()) qFatal("Failed to create Vulkan instance: %d", instance.errorCode());
    VULKAN_HPP_DEFAULT_DISPATCHER.init(instance.vkInstance());   // 初始化vulkan hpp

    QLoggingCategory::setFilterRules(
        QStringLiteral("qt.vulkan=true"));   // 定义Qt日志系统的过滤规则（显示vulkan日志）

    VulkanWindow vkWindow;
    vkWindow.setVulkanInstance(&instance);   // 设置窗口的Vulkan实例
    vkWindow.resize(1024, 768);              // 设置窗口尺寸
    vkWindow.show();                         // 显示窗口

    app.exec();
}