cmake_minimum_required (VERSION 3.15)


project (test_logger)

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cpp thread2_write_cam.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
                        ${GST_INCLUDE_DIRS}
                        "../spdlog/include"
                        "../")

target_link_libraries(${PROJECT_NAME} "/usr/local/lib/logger.so" -pthread)
