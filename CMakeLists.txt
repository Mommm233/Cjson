cmake_minimum_required(VERSION 3.12)
project(MyJsonParser)

set(CMAKE_CXX_STANDARD 11)

# 添加源文件
set(SOURCE_FILES
    Main.cpp
    JsonValue.cpp
    JsonParser.cpp
)

# 生成可执行文件
add_executable(my_program ${SOURCE_FILES})
