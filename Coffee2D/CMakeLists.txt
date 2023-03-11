# Coffee2D C++ Multimedia Component
cmake_minimum_required(VERSION 3.18)

# Fetch SFML dependency
FetchContent_Declare(SFML
	GIT_REPOSITORY https://github.com/SFML/SFML
	GIT_TAG master)
FetchContent_MakeAvailable(SFML)

# Fetch GLM dependency
FetchContent_Declare(GLM
	GIT_REPOSITORY https://github.com/g-truc/glm
	GIT_TAG master)
FetchContent_MakeAvailable(GLM)

# Project Include Files

set(INCROOT "include/Coffee2D")
set(COFFEE2D_INCLUDE
	# Graphics
	"${INCROOT}/Graphics/Renderer.hpp"
	"${INCROOT}/Graphics/Texture.hpp"
	"${INCROOT}/Graphics/Vertex.hpp"
	"${INCROOT}/Graphics/Model2D.hpp"
	"${INCROOT}/Graphics/Shader.hpp"

	# Game
	"${INCROOT}/Game/Game.hpp"

	# Other
	"${INCROOT}/Export.hpp"

	# External
	"external/include/stb/stb_image.h"
	"external/include/glad/glad.h"
)

# Project Source Files

set(SRCROOT "src/Coffee2D")
set(COFFEE2D_SRC
	# Graphics
	"${SRCROOT}/Graphics/Renderer.cpp"
	"${SRCROOT}/Graphics/Texture.cpp"
	"${SRCROOT}/Graphics/Vertex.cpp"
	"${SRCROOT}/Graphics/Model2D.cpp"
	"${SRCROOT}/Graphics/Shader.cpp"

	# Graphics - OpenGL Implementation
	"${SRCROOT}/Graphics/OpenGL/RendererOpenGL.cpp"
	"${SRCROOT}/Graphics/OpenGL/RendererOpenGL.hpp"
	"${SRCROOT}/Graphics/OpenGL/TextureOpenGL.cpp"
	"${SRCROOT}/Graphics/OpenGL/TextureOpenGL.hpp"
	"${SRCROOT}/Graphics/OpenGL/Model2DOpenGL.cpp"
	"${SRCROOT}/Graphics/OpenGL/Model2DOpenGL.hpp"
	"${SRCROOT}/Graphics/OpenGL/ShaderOpenGL.cpp"
	"${SRCROOT}/Graphics/OpenGL/ShaderOpenGL.hpp"
	
	# Game
	"${SRCROOT}/Game/Game.cpp"

	# External
	"external/src/stb/stb_image.cpp"
	"external/src/glad/glad.c")

set(COFFEE2D_LIBS
	sfml-window
	sfml-graphics
	sfml-main)

	
add_library(Coffee2D ${COFFEE2D_SRC} ${COFFEE2D_INCLUDE})
target_compile_definitions(Coffee2D PRIVATE BUILD_SHARED_LIBS=1)
target_compile_definitions(Coffee2D PRIVATE COFFEE2D_API_EXPORTS=1)
target_include_directories(Coffee2D PRIVATE "external/include")
target_include_directories(Coffee2D PUBLIC "include")
target_compile_features(Coffee2D PUBLIC cxx_std_20)
target_link_libraries(Coffee2D PUBLIC ${COFFEE2D_LIBS})
target_link_libraries(Coffee2D PUBLIC glm::glm)