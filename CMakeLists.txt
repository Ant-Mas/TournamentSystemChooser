cmake_minimum_required(VERSION 3.30)
project(TournamentSystemChooser)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_INCLUDE_PATH D:\\Uczelnia\\jezykC\\TournamentSystemChooser\\libharu_build\\include)
#set(CMAKE_LIBRARY_PATH D:\\Uczelnia\\jezykC\\TournamentSystemChooser\\libharu_build\\src)

include_directories(libharu/include)
link_directories(libharu/build/src)

add_executable(TournamentSystemChooser main.cpp
        TournamentSystem.h)

find_library(TEST_LIBRARY hpdf libharu/build/src)
target_link_libraries(TournamentSystemChooser LINK_PUBLIC ${TEST_LIBRARY})