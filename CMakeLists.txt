cmake_minimum_required(VERSION 3.20)
project(OpisGrafow LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OpisGrafow
    main.cpp
    graph_logic.cpp
    graph_logic.h
    graph.cpp
    graph.h
    draw_graph.cpp
    draw_graph.h
)

find_package(SFML CONFIG REQUIRED COMPONENTS
    Graphics
    Window
    System
)

target_link_libraries(OpisGrafow PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

add_custom_command(TARGET OpisGrafow POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<$<CONFIG:Debug>:C:/vcpkg/installed/x64-windows/debug/bin>
    $<$<CONFIG:Release>:C:/vcpkg/installed/x64-windows/bin>
    $<TARGET_FILE_DIR:OpisGrafow>
)
