set(IWLIB_FOUND FALSE)

find_path(IWLIB_INCLUDE_DIR iwlib.h
  /usr/local/include
  /usr/include
)

find_library(IWLIB_LIBRARY iw
  /usr/local/lib
  /usr/lib
)

if(IWLIB_INCLUDE_DIR)
  if(IWLIB_LIBRARY)
    set(IWLIB_LIBRARIES ${IWLIB_LIBRARY})
    set(IWLIB_FOUND TRUE)
  endif(IWLIB_LIBRARY)
endif(IWLIB_INCLUDE_DIR)

if(IWLIB_FOUND)
  message(STATUS "Found iwlib: ${IWLIB_LIBRARY}")
else(IWLIB_FOUND)
  message(WARNING "Could NOT find iwlib.")
endif(IWLIB_FOUND)
