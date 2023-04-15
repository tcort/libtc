# CMakeLists.txt
# Copyright 2022, 2023  Thomas Cort
#
# Copying and distribution of this file, with or without modification, are
# permitted in any medium without royalty, provided the copyright notice and
# this notice are preserved. This file is offered as-is, without any warranty.

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# project version MUST be an integer
project(libtc VERSION 2022 DESCRIPTION "a collection of functions" LANGUAGES C)

set(PROJECT_AUTHOR "Thomas Cort")
set(PROJECT_COPYRIGHT "Copyright (C) 2022, 2023  Thomas Cort")
set(PROJECT_LICENSE "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\\nThis is free software: you are free to change and redistribute it.\\nThere is NO WARRANTY, to the extent permitted by law.")
set(PROJECT_BUILD 0)

include(GNUInstallDirs)

configure_file (
    "${PROJECT_SOURCE_DIR}/include/tc/version.h.in"
    "${PROJECT_BINARY_DIR}/include/tc/version.h"
)

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_BINARY_DIR}/include"
)

# pkg-config
configure_file(tc.pc.in tc.pc @ONLY)


file(GLOB LIBTC_SRC src/*.c)
add_library(tc SHARED ${LIBTC_SRC})

# Library Versioning
set_target_properties(tc PROPERTIES
                            VERSION ${PROJECT_VERSION}
                            SOVERSION 1)


# install
install(TARGETS tc
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/tc DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/tc.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
install(FILES
        ${CMAKE_SOURCE_DIR}/AUTHORS
        ${CMAKE_SOURCE_DIR}/COPYING
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/libtc)

## Examples

list(APPEND EXAMPLES nanoid)

foreach(EXAMPLEPROG IN LISTS EXAMPLES)
    add_executable(${EXAMPLEPROG} examples/${EXAMPLEPROG}.c)
    target_link_libraries(${EXAMPLEPROG} tc)
endforeach()

## Testing

list(APPEND TESTS ctype.check)
list(APPEND TESTS errno.check)
list(APPEND TESTS html.check)
list(APPEND TESTS libgen.check)
list(APPEND TESTS luhn.check)
list(APPEND TESTS math.check)
list(APPEND TESTS md2.check)
list(APPEND TESTS mtrand.check)
list(APPEND TESTS string.check)

enable_testing(true)
foreach(TESTPROG IN LISTS TESTS)
    add_executable(${TESTPROG} tests/${TESTPROG}.c)
    target_link_libraries(${TESTPROG} tc)
    add_test(NAME ${TESTPROG} COMMAND ${TESTPROG})
endforeach()

## Packaging

set(CPACK_PACKAGE_NAME "libtc")
set(CPACK_PACKAGE_VENDOR ${PROJECT_AUTHOR})
set(CPACK_GENERATOR "") # platform defaults
set(CPACK_SOURCE_GENERATOR "TGZ;TXZ;ZIP")
set(CPACK_PACKAGE_DIRECTORY ${PROJECT_BINARY_DIR}/package)

set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}.${PROJECT_BUILD}")

set(CPACK_SOURCE_IGNORE_FILES .git/ _CPack_Packages/
    ${CMAKE_BINARY_DIR}/ ${PROJECT_BINARY_DIR}/
    build/ ".*~$"
)

include(CPack)
