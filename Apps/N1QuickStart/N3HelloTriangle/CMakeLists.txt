set(TARGET_NAME "N1QuickStart_N3HelloTriangle")

# just for qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

find_package(Vulkan COMPONENTS glslang SPIRV-Tools  shaderc_combined REQUIRED)
file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/source)


source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

add_executable(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME ${TARGET_NAME})
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Apps)

target_link_libraries(${TARGET_NAME} 
      PRIVATE
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            Vulkan::Vulkan
            Shader
            Vulkan::glslang
            Vulkan::SPIRV-Tools
            Vulkan::shaderc_combined
)

target_include_directories(
  ${TARGET_NAME} 
  PUBLIC 
)

add_test(
    NAME ${TARGET_NAME}
    COMMAND ${TARGET_NAME}
)