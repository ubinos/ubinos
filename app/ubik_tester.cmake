set(INCLUDE__APP                                                                TRUE)
set(APP__NAME                                                                   "ubik_tester")

get_filename_component(_tmp_source_dir "${CMAKE_CURRENT_LIST_DIR}/ubik_tester" ABSOLUTE)

file(GLOB_RECURSE _tmp_sources
    "${_tmp_source_dir}/*.c"
    "${_tmp_source_dir}/*.cpp"
    "${_tmp_source_dir}/*.S"
    "${_tmp_source_dir}/*.s")

set(PROJECT_APP_SOURCES ${PROJECT_APP_SOURCES} ${_tmp_sources})


