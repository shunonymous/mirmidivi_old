cmake_minimum_required(VERSION 2.8)
project(mirmidivi)

# Version
set (VERSION_MAJOR "0")
set (VERSION_MINOR "0")
set (VERSION_PATCH "1")
set (VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

# Boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREAD ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.32 COMPONENTS program_options)

# ALSA
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(ALSA_SEQ ON)
  find_package(ALSA)
  add_subdirectory(alsa_seq)
endif()

add_subdirectory(core)

add_executable(mirmidivi core/mirmidivi.cpp)
target_link_libraries(mirmidivi ${CMAKE_DL_LIBS})
target_link_libraries(mirmidivi options)