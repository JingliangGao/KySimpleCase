cmake_minimum_required(VERSION 3.15)
project(ort_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- 查找头文件 ----
# 优先找 /usr/include/onnxruntime/，找不到就退回 /usr/include/
find_path(ORT_INCLUDE_DIR
    NAMES onnxruntime_cxx_api.h
    PATHS /usr/include/onnxruntime /usr/include /usr/local/include
    REQUIRED
)

# ---- 查找库文件 ----
find_library(ORT_LIB
    NAMES onnxruntime
    PATHS /usr/lib/x86_64-linux-gnu /usr/lib /usr/local/lib
    REQUIRED
)

message(STATUS "ORT_INCLUDE_DIR = ${ORT_INCLUDE_DIR}")
message(STATUS "ORT_LIB         = ${ORT_LIB}")

add_executable(ort_test main.cpp)

target_include_directories(ort_test PRIVATE "${ORT_INCLUDE_DIR}")
target_link_libraries(ort_test PRIVATE "${ORT_LIB}")

# 因为库装在 /usr/lib/x86_64-linux-gnu 这种系统路径，
# 运行时动态链接器能直接找到，一般不用再设 rpath。
# 如果装到了 /usr/local/lib，加上：
# set_target_properties(ort_test PROPERTIES
#     BUILD_RPATH "/usr/local/lib"
#     INSTALL_RPATH "/usr/local/lib")