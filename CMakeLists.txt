cmake_minimum_required(VERSION 3.29.3)

project(Template)

set(CMAKE_CXX_STANDARD 23)
file(GLOB SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(main ${SRC})

target_link_libraries(main PRIVATE mingw32
${PROJECT_SOURCE_DIR}/lib/libSDL2maind.a
${PROJECT_SOURCE_DIR}/bin/SDL2d.dll
${PROJECT_SOURCE_DIR}/bin/SDL2_imaged.dll
${PROJECT_SOURCE_DIR}/bin/SDL2_ttfd.dll
stdc++exp
)