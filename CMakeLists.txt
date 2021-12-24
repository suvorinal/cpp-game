cmake_minimum_required(VERSION 3.21)
project (cpp_game)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")

add_executable(cpp_game main.cpp Objects/Player.cpp Objects/Map.cpp Objects/Bomb.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include)
target_link_libraries(cpp_game sfml-system sfml-window sfml-graphics sfml-audio sfml-network)