cmake_minimum_required(VERSION 3.20)

project(myhome LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)

add_executable(myhome WIN32
	src/main.cpp
	src/model/Building.cpp
	src/model/Level.cpp
	src/model/Opening.cpp
	src/model/Plan.cpp
	src/model/Wall.cpp
	src/renderer/WallRenderer.cpp
	src/renderer/WindowRenderer.cpp
	src/ui/Canvas.cpp
	src/ui/MainWindow.cpp
)

set_target_properties(myhome PROPERTIES
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)
target_compile_options(myhome PRIVATE
	/std:c++latest
)
target_include_directories(myhome PRIVATE src)
target_link_libraries(myhome PRIVATE Qt6::Widgets)

add_custom_command(TARGET myhome POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:myhome>/platforms"
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"$<TARGET_FILE:Qt6::QWindowsIntegrationPlugin>"
		"$<TARGET_FILE_DIR:myhome>/platforms/$<TARGET_FILE_NAME:Qt6::QWindowsIntegrationPlugin>"
	COMMENT "Deploying the Qt Windows platform plugin"
)

set_target_properties(Qt6::Widgets PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")