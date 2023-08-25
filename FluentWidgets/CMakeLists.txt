project(fluentWidgets)

# 设置自动生成moc文件,AUTOMOC打开可以省去QT5_WRAP_CPP命令
SET(CMAKE_AUTOMOC ON)

# 设置自动生成ui.h文件,AUTOUIC打开可以省去QT5_WRAP_UI命令
SET(CMAKE_AUTOUIC ON)

# 【optional】设置自动处理.qrc文件
SET(CMAKE_AUTORCC ON)

# 查找Qt依赖
find_package(Qt5 REQUIRED COMPONENTS Widgets Svg Core)

# 搜索源文件
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS include/*.h src/*.cpp)

# 添加资源文件
SET(RCC_FILES fluentWidgets.qrc)

# 添加为库
add_library(${PROJECT_NAME} ${PROJECT_SOURCES} ${RCC_FILES})

# 添加头文件引用路径
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/Common
    ${PROJECT_SOURCE_DIR}/include/Widgets
)

# 链接动态库
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    Qt5::Widgets
    Qt5::Core
    Qt5::Svg
)

foreach(var ${PROJECT_SOURCES})
    message("CPP : " ${var})
endforeach(var ${PROJECT_SOURCES})
