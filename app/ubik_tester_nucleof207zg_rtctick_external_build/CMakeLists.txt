cmake_minimum_required(VERSION 3.24)

set(PROJECT_TARGET_NAME "app")

if(NOT DEFINED PROJECT_BASE_DIR)
    set(PROJECT_BASE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../..")
    get_filename_component(PROJECT_BASE_DIR ${PROJECT_BASE_DIR} REALPATH)
endif()
if(NOT DEFINED PROJECT_LIB_DIR)
    set(PROJECT_LIB_DIR "${PROJECT_BASE_DIR}/lib")
endif()

get_filename_component(CUR_DIR_NAME "${CMAKE_CURRENT_LIST_DIR}" NAME)
set(PROJECT_CONFIG_NAME "${CUR_DIR_NAME}")
set(PROJECT_CONFIG_DIR "${CMAKE_CURRENT_LIST_DIR}/../../app")

set(PROJECT_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/../../source")

##
include("${PROJECT_LIB_DIR}/ubinos_base/common/common_config.cmake")

include("${PROJECT_LIB_DIR}/ubinos_base/common/common_ubinos_local_pre.cmake")

project(${PROJECT_TARGET_NAME} NONE)

##
include("${PROJECT_LIB_DIR}/ubinos_base/common/common_ubinos_local_post.cmake")
