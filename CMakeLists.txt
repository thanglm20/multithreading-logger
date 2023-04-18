cmake_minimum_required (VERSION 3.15)
project (logger)

# include(${CMAKE_SOURCE_DIR}/common.cmake)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall --std=c++11 -O0 -fPIC -rdynamic -g" )

find_package(Threads REQUIRED)

add_subdirectory(spdlog)

add_library (${PROJECT_NAME} SHARED 
                        ILogger.h 
                        ILogger.cpp 
                        SPDLogger.h 
                        SPDLogger.cpp 
                        LogUtil.h
                        LoggerPool.cpp
                        LoggerPool.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC 
                        "spdlog/include" 
                        "/usr/include/glib-2.0/")

target_link_libraries(${PROJECT_NAME} PUBLIC
                        spdlog 
                        -pthread)

set_target_properties(${PROJECT_NAME}
                        PROPERTIES 
                        PREFIX "" 
                        ARCHIVE_OUTPUT_DIRECTORY "../"
                        LIBRARY_OUTPUT_DIRECTORY "../"
                        RUNTIME_OUTPUT_DIRECTORY "../")

install(TARGETS ${PROJECT_NAME}
            LIBRARY DESTINATION "/usr/local/lib"
)


add_subdirectory(test_logger)