cmake_minimum_required(VERSION 3.20)
project(misc)

add_executable(lipo lipo.c)

target_include_directories(lipo PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../include
	${CMAKE_CURRENT_SOURCE_DIR}/../include/foreign
	${CMAKE_CURRENT_SOURCE_DIR}/../libstuff
)

target_compile_definitions(lipo PRIVATE
	__DARWIN_UNIX03
)

target_link_libraries(lipo PRIVATE stuff)

install(TARGETS lipo
    RUNTIME DESTINATION bin
)