cmake_minimum_required(VERSION 2.8)

if(ALSA_SEQ)
  message("ALSA_SEQ is ON")
  message("${ALSA_INCLUDE_DIRS}")
  if(ALSA_FOUND)
    message("ALSA libraries are found")
    include_directories(${ALSA_INCLUDE_DIRS})
    add_library(alsa_seq SHARED
      alsa_seq.cpp
      )
    target_link_libraries(alsa_seq ${ALSA_LIBRARIES})
    install(TARGETS alsa_seq LIBRARY DESTINATION ./lib)
  endif()
endif()