file(GLOB SRC_FILES
        "*.cpp"
        "*/*.cpp"
)
add_executable(llvm_ir_gen ${SRC_FILES}
        AstBuilder.cpp
        AstBuilder.h
        Program.cpp
        Program.h
        Type.cpp
        Type.h
        error.cpp
        error.h)

target_link_libraries(llvm_ir_gen PRIVATE LLVM)

target_include_directories(llvm_ir_gen PRIVATE /usr/include/antlr4-runtime)
target_link_libraries(llvm_ir_gen PRIVATE /usr/lib/libantlr4-runtime.so)
