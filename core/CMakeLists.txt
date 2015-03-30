cmake_minimum_required(VERSION 2.8)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_library(options STATIC
    option.cpp
    )
  target_link_libraries(options ${Boost_LIBRARIES})
endif()
