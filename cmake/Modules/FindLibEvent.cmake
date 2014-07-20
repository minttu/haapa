set(EVENT_FOUND FALSE)

find_path(EVENT_INCLUDE_DIR event.h
  /usr/local/include
  /usr/include
)

find_library(EVENT_LIBRARY event
  /usr/local/lib
  /usr/lib
)

if(EVENT_INCLUDE_DIR)
  if(EVENT_LIBRARY)
    set(EVENT_LIBRARIES ${EVENT_LIBRARY})
    set(EVENT_FOUND TRUE)
  endif(EVENT_LIBRARY)
endif(EVENT_INCLUDE_DIR)

if(EVENT_FOUND)
  message(STATUS "Found libevent: ${EVENT_LIBRARY}")
else(EVENT_FOUND)
  message(FATAL_ERROR "Could NOT find libevent.")
endif(EVENT_FOUND)
