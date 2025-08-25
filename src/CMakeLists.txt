file(GLOB SRC_FILES
        "*.cpp"
        "*/*.cpp"
)
add_executable(stcc ${SRC_FILES}
        AstBuilder.cpp
        AstBuilder.h
        Program.cpp
        Program.h
        Type.cpp
        Type.h
        LlvmBuilder.cpp
        LlvmBuilder.h
        error.cpp
        error.h
        RuntimeLibs.cpp
        RuntimeLibs.h
        IdentifierManager.cpp
        IdentifierManager.h
)

target_link_libraries(stcc PRIVATE LLVM)
target_link_libraries(stcc PRIVATE ${LIBEDIT_LIBRARIES} ${LLVM_LIBS} cxxopts)

target_include_directories(stcc PRIVATE /usr/include/antlr4-runtime)
target_link_libraries(stcc PRIVATE /usr/lib/libantlr4-runtime.so)