CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
project(cpp-checkers)
ADD_EXECUTABLE(checkers direction.h main_noncurses.cpp model/model.cpp model/player.cpp model/game_piece.cpp model/checker_piece.cpp model/board.cpp model/checker_board.cpp nc_controller/command.cpp nc_controller/controller.cpp ncview/window.cpp ncview/ui.cpp ncview/player_selection_window.cpp ncview/menu.cpp ncview/main_menu.cpp ncview/game_window.cpp ncview/add_player_window.cpp)
SET(CMAKE_CXX_FLAGS "-g -std=c++14 -Wall -pedantic -lboost_program_options")
SET(CMAKE_CXX_COMPILER "/opt/rh/devtoolset-6/root/usr/bin/g++")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)