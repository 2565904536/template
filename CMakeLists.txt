cmake_minimum_required(VERSION 3.29.3)

project(Template)

set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_EXE_LINKER_FLAGS "-mwindows")
file(GLOB_RECURSE SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(main ${SRC})

target_link_libraries(main 
mingw32
${PROJECT_SOURCE_DIR}/lib/libSDL2main.a
${PROJECT_SOURCE_DIR}/bin/SDL2.dll
${PROJECT_SOURCE_DIR}/bin/SDL2_image.dll
${PROJECT_SOURCE_DIR}/bin/SDL2_ttf.dll
${PROJECT_SOURCE_DIR}/bin/SDL2_mixer.dll

stdc++exp
)
