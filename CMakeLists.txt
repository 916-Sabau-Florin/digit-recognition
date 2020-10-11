cmake_minimum_required(VERSION 3.17)
project(digit_recognition)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(neural_network/include)

set(SFML_DIR "/home/nacho/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(digit_recognition
        include/App.hpp
        include/Button.hpp
        include/PaintArea.hpp
        include/Resources.hpp
        include/TextArea.hpp
        include/Widget.hpp
        neural_network/include/func.hpp
        neural_network/include/idx_format.hpp
        neural_network/include/matrix.tpp
        neural_network/include/neural_network.hpp
        neural_network/include/random.tpp
        neural_network/include/utils.hpp
        neural_network/src/func.cpp
        neural_network/src/neural_network.cpp
        neural_network/src/utils.cpp
        src/Button.cpp
        src/main.cpp
        src/PaintArea.cpp
        src/Resources.cpp
        src/TextArea.cpp
        src/Widget.cpp)
target_link_libraries(digit_recognition sfml-graphics)