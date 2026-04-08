# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

idf_component_register(
	SRCS "main.cpp" "Pca9685.cpp" "bluetooth.cpp" "MotionController.cpp" "Servo.cpp" "Leg.cpp"
	REQUIRES esp_driver_i2c
	REQUIRES esp_timer
	REQUIRES nvs_flash
	REQUIRES bt
)

