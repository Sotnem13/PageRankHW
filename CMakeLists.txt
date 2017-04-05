cmake_minimum_required(VERSION 3.6)


set(projectName pageRang)

set(SOURCE_FILES
        test/main.cpp
        src/page.cpp
        src/net_manager.cpp
        src/url.cpp
        src/net_graph.cpp)


set(CMAKE_CXX_STANDARD 11)
set(CURL_FLAGS "-lcurl")
set(PARALLEL_FLAGS "-ltbb")


include_directories(include)

project(${projectName})
add_executable(${projectName} ${SOURCE_FILES})


target_link_libraries(${projectName} ${PARALLEL_FLAGS})
target_link_libraries(${projectName} ${CURL_FLAGS})