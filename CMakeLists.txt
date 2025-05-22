cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(double_game)

set(CMAKE_AUTOMOC ON)


include_directories("C:\\Qt\\6.10.0\\mingw_64\\include\\QtWidgets"
        "C:\\Qt\\6.10.0\\mingw_64\\include\\QtCore"
        "C:\\Qt\\6.10.0\\mingw_64\\include\\QtGui"
        "C:\\Qt\\6.10.0\\mingw_64\\include")

link_directories("C:\\Qt\\6.10.0\\mingw_64\\lib")

set(Qt6Widgets_DIR "C:\\Qt\\6.10.0\\mingw_64\\lib\\cmake\\Qt6Widgets")
find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(Qt6Core_DIR "C:\\Qt\\6.10.0\\mingw_64\\lib\\cmake\\Qt6Core")
find_package(Qt6Core REQUIRED)
set(Qt6Gui_DIR "C:\\Qt\\6.10.0\\mingw_64\\lib\\cmake\\Qt6Gui")
find_package(Qt6Gui REQUIRED)

add_executable(double_game main.cpp
        hdr/Platform.h
        src/platform.cpp
        hdr/Globals.h
        hdr/Doodle.h
        src/doodle.cpp
        hdr/MainWindow.h
        src/MainWindow.cpp
        hdr/GameWidget.h
        src/GameWidget.cpp
        hdr/MenuWidget.h
        src/MenuWidget.cpp
        hdr/CustomButton.h
        src/CustomButton.cpp
        src/Generator.cpp
        src/Globals.cpp
        hdr/Generator.h
        hdr/RemoveUnnecessaryPlatforms.h
        src/RemoveUnnecessaryPlatforms.cpp
        hdr/EndGameWidget.h
        src/EndGameWidget.cpp
        src/HighScoresDialog.cpp
)

target_link_libraries(double_game PRIVATE Qt6Widgets Qt6Core Qt6Gui)