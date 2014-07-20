cmake_minimum_required(VERSION 2.6)
project(haapa)

set(CMAKE_C_COMPILER, clang)
add_definitions(--std=gnu99 -Wall -O2)

execute_process(
    COMMAND /bin/sh -c "uname -r | cut -d. -f2"
    OUTPUT_VARIABLE KERNEL_2ND_VERSION
    RESULT_VARIABLE ASD
)

if(KERNEL_2ND_VERSION GREATER 13)
    message("Kernel >3.13, using new memory")
    add_definitions(-DHAAPA_NEWMEM)
endif(KERNEL_2ND_VERSION GREATER 13)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(LibEvent REQUIRED)

add_executable(haapa src/haapa.c)
target_link_libraries(haapa ${EVENT_LIBRARIES})

set(LIBS acpi exec format fs network output proc result time uname util x256)

find_package(LibMPDClient)
if(MPDCLIENT_FOUND)
    list(APPEND LIBS mpd)
    list(APPEND CORELIBS ${MPDCLIENT_LIBRARY})
    add_definitions(-DINCLUDE_MPD)
endif(MPDCLIENT_FOUND)

find_package(ALSA)
if(ALSA_FOUND)
    list(APPEND LIBS alsa)
    list(APPEND CORELIBS ${ALSA_LIBRARY})
    add_definitions(-DINCLUDE_ALSA)
endif(ALSA_FOUND)

find_package(X11)
if(X11_FOUND)
    list(APPEND LIBS output_x)
    list(APPEND CORELIBS ${X11_LIB})
    add_definitions(-DINCLUDE_XLIB)
endif(X11_FOUND)

find_package(LibIW)
if(IWLIB_FOUND)
    list(APPEND LIBS wireless)
    list(APPEND CORELIBS ${IWLIB_LIBRARY})
    add_definitions(-DINCLUDE_IWLIB)
endif(IWLIB_FOUND)

foreach(f ${LIBS})
    add_library(${f} src/${f}.c)
endforeach(f)

target_link_libraries(haapa ${CORELIBS} m ${LIBS})
