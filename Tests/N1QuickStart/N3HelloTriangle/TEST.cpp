#include <gtest/gtest.h>
#include <QGuiApplication>
#include <QLoggingCategory>
#include <QVulkanInstance>
#include <vulkan/vulkan.hpp>

TEST(N1QuickStart, E3HelloTriangle)
{
    int                  argc = 1;
    std::array<char*, 1> argv = {"E3HelloTriangle"};
    QGuiApplication      app(argc, argv.data());

    static vk::DynamicLoader dynamicLoader;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        dynamicLoader.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
    VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);

    QVulkanInstance instance;
    instance.setLayers({"VK_LAYER_KHRONOS_validation"});
    if (!instance.create()) qFatal("Failed to create Vulkan instance: %d", instance.errorCode());
    VULKAN_HPP_DEFAULT_DISPATCHER.init(instance.vkInstance());


    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));
}