cmake_minimum_required(VERSION 3.20)

project(game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(breakout
    main.cpp
    game.cpp
    unit.cpp
    paddle.cpp
    ball.cpp
    brick.cpp
    draw-digit.cpp
    view.cpp
    game-controller.cpp
    audio.cpp
)

target_link_libraries(breakout PRIVATE
    splashkit
)

file(COPY ${CMAKE_SOURCE_DIR}/sounds
    DESTINATION ${CMAKE_BINARY_DIR}
)
