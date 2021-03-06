cmake_minimum_required(VERSION 3.1.0)
project(chess)

set(CMAKE_CXX_STANDARD 11)

# SFML lib
# set(SFML_DIR "/usr/local/lib/cmake/SFML/")

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

set(SRC_DIRECTORY src)
set(INCLUDE_DIRECTORY include)

set(SOURCES
    ${SRC_DIRECTORY}/board_slot.cpp
    ${SRC_DIRECTORY}/chessboard.cpp
    ${SRC_DIRECTORY}/chess_move.cpp
    ${SRC_DIRECTORY}/chess_piece.cpp
    ${SRC_DIRECTORY}/chess_user.cpp
    ${SRC_DIRECTORY}/bishop.cpp
    ${SRC_DIRECTORY}/king.cpp
    ${SRC_DIRECTORY}/knight.cpp
    ${SRC_DIRECTORY}/pawn.cpp
    ${SRC_DIRECTORY}/queen.cpp
    ${SRC_DIRECTORY}/rook.cpp
    ${SRC_DIRECTORY}/utils/audio_player.cpp
    ${SRC_DIRECTORY}/utils/settings.cpp
    ${SRC_DIRECTORY}/utils/helpers.cpp
)

include_directories(${INCLUDE_DIRECTORY})
add_executable(${PROJECT_NAME}
    ${SRC_DIRECTORY}/main.cpp
    ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio)

add_subdirectory(tests)