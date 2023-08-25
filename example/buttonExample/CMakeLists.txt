project(buttonExample)

# 设置自动生成moc文件,AUTOMOC打开可以省去QT5_WRAP_CPP命令
SET(CMAKE_AUTOMOC ON)

# 设置自动生成ui.h文件,AUTOUIC打开可以省去QT5_WRAP_UI命令
SET(CMAKE_AUTOUIC ON)

# 【optional】设置自动处理.qrc文件
SET(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(buttonExample main.cpp ButtonPlane.cpp ButtonPlane.h)

target_link_libraries(
    buttonExample
    PRIVATE
    Qt5::Widgets
    fluentWidgets
)