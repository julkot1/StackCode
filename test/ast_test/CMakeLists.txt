function(add_llvm_ir_test TARGET_NAME)
    add_executable(${TARGET_NAME} ${ARGN})
    target_link_libraries(${TARGET_NAME}
            PRIVATE
            gtest_main
            LLVM
            edit
    )
    target_include_directories(${TARGET_NAME} PRIVATE /usr/include/antlr4-runtime)
    target_link_libraries(${TARGET_NAME} PRIVATE /usr/lib/libantlr4-runtime.so)
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endfunction()

add_llvm_ir_test(example_test IfTest.cpp)
