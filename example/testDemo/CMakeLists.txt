project(testDemo)

# 设置自动生成moc文件,AUTOMOC打开可以省去QT5_WRAP_CPP命令
SET(CMAKE_AUTOMOC ON)

# 设置自动生成ui.h文件,AUTOUIC打开可以省去QT5_WRAP_UI命令
SET(CMAKE_AUTOUIC ON)

# 【optional】设置自动处理.qrc文件
SET(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Svg Xml)

# 搜索源文件
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS *.h *.cpp)

# 添加资源文件
SET(RCC_FILES image.qrc)

add_executable(testDemo ${PROJECT_SOURCES} ${RCC_FILES})

target_link_libraries(
    testDemo
    PRIVATE
    Qt5::Widgets
    Qt5::Core
    Qt5::Svg
    Qt5::Xml
    fluentWidgets
)
