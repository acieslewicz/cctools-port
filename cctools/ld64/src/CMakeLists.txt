cmake_minimum_required(VERSION 3.20)
project(ld64)

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(
        FATAL_ERROR
        "This project requires the Clang compiler. Current compiler: ${CMAKE_CXX_COMPILER_ID}"
    )
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-fblocks" COMPILER_SUPPORTS_FBLOCKS)
find_library(BLOCKS_RUNTIME_LIB BlocksRuntime)

set(ld64_include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/foreign
    ${CMAKE_CURRENT_SOURCE_DIR}/ld
    ${CMAKE_CURRENT_SOURCE_DIR}/ld/parsers
    ${CMAKE_CURRENT_SOURCE_DIR}/3rd
    ${CMAKE_CURRENT_SOURCE_DIR}/3rd/BlocksRuntime
    ${CMAKE_CURRENT_SOURCE_DIR}/3rd/include
    ${CMAKE_CURRENT_SOURCE_DIR}/abstraction
)

include_directories(${ld64_include_dirs})

set(ld64_sources
    ./ld/InputFiles.cpp
    ./ld/OutputFile.cpp
    ./ld/SymbolTable.cpp
    ./ld/code-sign-blobs/blob.cpp
    ./ld/parsers/lto_file.cpp
    ./ld/parsers/opaque_section_file.cpp
    ./ld/parsers/macho_relocatable_file.cpp
    ./ld/parsers/macho_dylib_file.cpp
    ./ld/parsers/textstub_dylib_file.cpp
    ./ld/parsers/archive_file.cpp
    ./ld/Options.cpp
    ./ld/Resolver.cpp
    ./ld/ld.cpp
    ./ld/Snapshot.cpp
    ./ld/passes/branch_island.cpp
    ./ld/passes/compact_unwind.cpp
    ./ld/passes/got.cpp
    ./ld/passes/tlvp.cpp
    ./ld/passes/branch_shim.cpp
    ./ld/passes/dtrace_dof.cpp
    ./ld/passes/order.cpp
    ./ld/passes/dylibs.cpp
    ./ld/passes/stubs/stubs.cpp
    ./ld/passes/huge.cpp
    ./ld/passes/bitcode_bundle.cpp
    ./ld/passes/objc.cpp
    ./3rd/md5.c
    ./3rd/strlcat.c
    ./3rd/helper.c
    ./3rd/strlcpy.c
    ./3rd/qsort_r.c
    ./3rd/eprintf.c
    ./ld/debugline.c
)

if(COMPILER_SUPPORTS_FBLOCKS AND NOT BLOCKS_RUNTIME_LIB)
    list(
        APPEND
        ld64_sources
        ./3rd/BlocksRuntime/runtime.c
        ./3rd/BlocksRuntime/data.c
    )
endif()

if(WIN32)
    list(APPEND ld64_sources ../../mman/mman.c)
endif()

add_executable(ld ${ld64_sources})

target_compile_definitions(
    ld
    PRIVATE
        EMULATED_HOST_CPU_TYPE=${EMULATED_HOST_CPU_TYPE}
        EMULATED_HOST_CPU_SUBTYPE=${EMULATED_HOST_CPU_SUBTYPE}
        __STDC_LIMIT_MACROS=1
        __STDC_CONSTANT_MACROS=1
        __DARWIN_UNIX03
        PROGRAM_PREFIX=""
        STDC_HEADERS=1
        HAVE_SYS_TYPES_H=1
        HAVE_SYS_STAT_H=1
        HAVE_STDLIB_H=1
        HAVE_STRING_H=1
        HAVE_MEMORY_H=1
        HAVE_STRINGS_H=1
        HAVE_INTTYPES_H=1
        HAVE_STDINT_H=1
        HAVE_UNISTD_H=1
        HAVE_DLFCN_H=1
        u_short=uint16_t
)

if(NOT WIN32)
    target_compile_definitions(ld PRIVATE HAVE_EXECINFO_H=1)
endif()

target_compile_options(
    ld
    PRIVATE
        -Wno-long-long
        -Wno-import
        -Wno-format
        -Wno-deprecated
        -Wno-unused-variable
        -Wno-unused-private-field
        -Wno-unused-function
        -Wno-invalid-offsetof
        -Wno-int-conversion
        -Wno-char-subscripts
        -Wno-shift-negative-value
)

if(COMPILER_SUPPORTS_FBLOCKS)
    target_compile_options(ld PRIVATE -fblocks)
    if(BLOCKS_RUNTIME_LIB)
        target_link_libraries(ld ${BLOCKS_RUNTIME_LIB})
        message(
            STATUS
            "Blocks support enabled with system runtime: ${BLOCKS_RUNTIME_LIB}"
        )
    else()
        if(WIN32)
            target_link_options(
                ld
                PRIVATE
                    -Wl,--defsym,__imp__NSConcreteStackBlock=_NSConcreteStackBlock
                    -Wl,--defsym,__imp__NSConcreteGlobalBlock=_NSConcreteGlobalBlock
                    -Wl,--defsym,__imp__NSConcreteMallocBlock=_NSConcreteMallocBlock
            )
        endif()
        message(STATUS "Blocks support enabled with bundled runtime")
    endif()
else()
    message(STATUS "Blocks support disabled")
endif()

if(WIN32)
    target_link_libraries(ld ws2_32 -ldl)
    target_link_options(ld PRIVATE -static-libgcc -static-libstdc++ -static)
else()
    target_link_libraries(ld -lpthread -ldl)
endif()

install(TARGETS ld RUNTIME DESTINATION bin)

if(WIN32)
    install(FILES ../../mman/LICENSE.mman DESTINATION .)
    install(
        FILES
            ../../../licenses/COPYING.dlfcn
            ../../../licenses/COPYING.libc++
            ../../../licenses/COPYING.libgcc
            ../../../licenses/COPYING.winpthreads
        DESTINATION .
    )
endif()
