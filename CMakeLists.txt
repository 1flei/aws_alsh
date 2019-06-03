PROJECT(AWSNN)

CMAKE_MINIMUM_REQUIRED(VERSION 3.4)
set (CMAKE_CXX_STANDARD 14)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-sign-compare")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")


find_package(Boost COMPONENTS program_options REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(alsh ${DIR_SRCS}
                "main.cpp"
                "pri_queue.cpp"
                "register.cpp"
                "alsh/ground_truth.cpp"
                "alsh/e2lsh.cpp"
                "alsh/srp.cpp"
                "alsh/s2alsh.cpp"
                "alsh/slalsh.cpp"
                "alsh/experiment/precision_recall.cpp"
                "alsh/experiment/fraction_recall.cpp"
              )

TARGET_LINK_LIBRARIES( alsh LINK_PUBLIC ${Boost_LIBRARIES})