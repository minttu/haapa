set(MPDCLIENT_FOUND FALSE)

find_path(MPDCLIENT_INCLUDE_DIR mpd/client.h
  /usr/local/include
  /usr/include
)

find_library(MPDCLIENT_LIBRARY mpdclient
  /usr/local/lib
  /usr/lib
)

if(MPDCLIENT_INCLUDE_DIR)
  if(MPDCLIENT_LIBRARY)
    set(MPDCLIENT_LIBRARIES ${MPDCLIENT_LIBRARY})
    set(MPDCLIENT_FOUND TRUE)
  endif(MPDCLIENT_LIBRARY)
endif(MPDCLIENT_INCLUDE_DIR)

if(MPDCLIENT_FOUND)
  message(STATUS "Found libmpdclient: ${MPDCLIENT_LIBRARY}")
else(MPDCLIENT_FOUND)
  message(WARNING "Could NOT find libmpdclient.")
endif(MPDCLIENT_FOUND)
