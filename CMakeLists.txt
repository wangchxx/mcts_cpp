cmake_minimum_required(VERSION 3.10)

# set the project name
PROJECT(MCTS)


# include_directories(include)
# add the executable
add_executable(main main.cpp src/board.cpp src/node.cpp src/mcts.cpp)