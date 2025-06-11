cmake_minimum_required(VERSION 3.10)

project(cern_root_demo_cpp_23)

find_package(ROOT)

add_library(root_demo SHARED source/main.cpp)

target_include_directories(root_demo
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(root_demo PUBLIC ROOT::Core)

ROOT_GENERATE_DICTIONARY(G__root_demo__cc
    ${PROJECT_SOURCE_DIR}/include/header.hpp
    MODULE root_demo
    ${PROJECT_SOURCE_DIR}/Linkdef.h
)

include(GNUInstallDirs)

install(
    TARGETS root_demo
    LIBRARY
)

install(
    DIRECTORY
    include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
    FILES
        ${PROJECT_BINARY_DIR}/libroot_demo_rdict.pcm
        ${PROJECT_BINARY_DIR}/libroot_demo.rootmap
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

configure_file(${PROJECT_SOURCE_DIR}/.rootrc.tmpl ${PROJECT_BINARY_DIR}/.rootrc @ONLY)
configure_file(${PROJECT_SOURCE_DIR}/profile.sh.tmpl ${PROJECT_BINARY_DIR}/profile.sh @ONLY)
install(
    FILES
        ${PROJECT_BINARY_DIR}/profile.sh
        ${PROJECT_SOURCE_DIR}/rootlogon.C
    DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

message(WARNING "To prepare your evironment, load profile:\n . ${CMAKE_INSTALL_FULL_BINDIR}/profile.sh")
