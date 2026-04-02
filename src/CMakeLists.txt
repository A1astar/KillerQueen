# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

idf_component_register(
	SRCS "main.cpp" "Pca9685.cpp" "bluetooth.cpp" "motion_controller.cpp" "Servo.cpp" "Leg.cpp"
	REQUIRES bt
)

