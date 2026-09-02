cmake_minimum_required(VERSION 3.20)

project(openhome LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)

add_executable(openhome WIN32
	src/openhome.cpp
	src/model/Building.cpp
	src/model/Level.cpp
	src/model/Plan.cpp
	src/model/Wall.cpp
	src/renderer/WallRenderer.cpp
	src/ui/Canvas.cpp
	src/ui/MainWindow.cpp
)

set_target_properties(openhome PROPERTIES
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)
target_compile_options(openhome PRIVATE
	/std:c++latest
)
target_include_directories(openhome PRIVATE src)
target_link_libraries(openhome PRIVATE Qt6::Widgets)

add_custom_command(TARGET openhome POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:openhome>/platforms"
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"$<TARGET_FILE:Qt6::QWindowsIntegrationPlugin>"
		"$<TARGET_FILE_DIR:openhome>/platforms/$<TARGET_FILE_NAME:Qt6::QWindowsIntegrationPlugin>"
	COMMENT "Deploying the Qt Windows platform plugin"
)

set_target_properties(Qt6::Widgets PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")