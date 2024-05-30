cmake_minimum_required(VERSION 3.29)

project(Engine)

# Add each .cpp file
add_executable(Engine 

	src/main.cpp
	src/Shader.cpp
	src/Camera.cpp
	src/Importer.cpp
	src/Mesh.cpp

)

#add_executable(Engine src/*.cpp)

# Find packages
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

target_link_libraries(Engine PRIVATE glfw glad::glad glm::glm-header-only)
