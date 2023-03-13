# Coffee2D C++ Multimedia Component
cmake_minimum_required(VERSION 3.18)

# Project Include Files
set(INCROOT "include/ProjectSilver")
set(PROJECTSILVER_INCLUDE
	"${INCROOT}/SilverGame.hpp")

# Project Source Files
set(SRCROOT "src/ProjectSilver")
set(PROJECTSILVER_SRC
	"${SRCROOT}/Main.cpp"
	"${SRCROOT}/SilverGame.cpp")

set(PROJECTSILVER_LIBS
	Coffee2D)

add_executable(ProjectSilver ${PROJECTSILVER_SRC} ${PROJECTSILVER_INCLUDE})

target_compile_definitions(ProjectSilver PRIVATE BUILD_SHARED_LIBS=1)
target_include_directories(ProjectSilver PRIVATE "include")
target_compile_features(ProjectSilver PRIVATE cxx_std_20)
target_link_libraries(ProjectSilver PRIVATE ${PROJECTSILVER_LIBS})

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ProjectSilver POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:ProjectSilver> $<TARGET_FILE_DIR:ProjectSilver> COMMAND_EXPAND_LISTS)
endif()

# Removes the console window
if (WIN32)
    target_link_options(ProjectSilver PRIVATE /SUBSYSTEM:WINDOWS)
else()
    target_link_options(ProjectSilver PRIVATE -mwindows)
endif()