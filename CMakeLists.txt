# CMakeList.txt: проект CMake для SaPDA-2; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("SaPDA-2")
set(CMAKE_CXX_STANDARD 23)

# Добавьте источник в исполняемый файл этого проекта.
add_executable(Classwork1 "Classwork1/main.cpp")
add_executable(Classwork2 "Classwork2/main.cpp")
add_executable(Classwork3 "Classwork3/main.cpp")
add_executable(Practice1_1 "Practice1_1/main.cpp")
add_executable(Practice1_2 "Practice1_2/main.cpp")
add_executable(Practice2_1 "Practice2_1/main.cpp" Practice2_1/textFileOperations.cpp)
add_executable(Practice2_2 "Practice2_2/main.cpp" Practice2_2/binFileOperations.cpp)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
