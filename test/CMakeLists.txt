
file(GLOB CHILD_TEST_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */CMakeLists.txt)

foreach(subdir ${CHILD_TEST_DIRS})
    get_filename_component(dir ${subdir} DIRECTORY)
    add_subdirectory(${dir})
endforeach()
