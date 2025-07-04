cmake_minimum_required(VERSION 3.30)

project(Typor
	LANGUAGES CXX
	VERSION 0.1.0
)

add_subdirectory(${PROJECT_SOURCE_DIR}/backend)
add_subdirectory(${PROJECT_SOURCE_DIR}/frontend)
add_subdirectory(${PROJECT_SOURCE_DIR}/examples)
