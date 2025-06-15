cmake_minimum_required(VERSION 3.20)
project(cctools-port)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Install prefix" FORCE)
endif()

add_subdirectory(cctools)

install(FILES 
    cctools/APPLE_LICENSE
    README.md
    DESTINATION .
)