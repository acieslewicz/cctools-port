cmake_minimum_required(VERSION 3.20)
project(libstuff)

add_library(stuff STATIC
    allocate.c
    apple_version.c
    arch.c
    arch_usage.c
    best_arch.c
    breakout.c
    bytesex.c
    checkout.c
    crc32.c
    dylib_roots.c
    dylib_table.c
    port.c
    errors.c
    #execute.c
    fatal_arch.c
    fatals.c
    get_arch_from_host.c
    get_toc_byte_sex.c
    guess_short_name.c
    hash_string.c
    hppa.c
    llvm.c
    lto.c
    macosx_deployment_target.c
    ofile.c
    ofile_error.c
    ofile_get_word.c
    print.c
    reloc.c
    rnd.c
    seg_addr_table.c
    set_arch_flag_name.c
    swap_headers.c
    symbol_list.c
    SymLoc.c
    unix_standard_mode.c
    version_number.c
    #writeout.c
    coff_bytesex.c
)

target_include_directories(stuff PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/foreign
)

target_compile_definitions(stuff PRIVATE
	__DARWIN_UNIX03
	PROGRAM_PREFIX="${PROGRAM_PREFIX}"
	PACKAGE_NAME="${PACKAGE_NAME}"
	PACKAGE_VERSION="${PACKAGE_VERSION}"
	EMULATED_HOST_CPU_TYPE=${EMULATED_HOST_CPU_TYPE}
	EMULATED_HOST_CPU_SUBTYPE=${EMULATED_HOST_CPU_SUBTYPE}
)

