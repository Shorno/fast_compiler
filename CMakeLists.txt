cmake_minimum_required(VERSION 3.16)
project(fast_compiler)
# Set C standard
set(CMAKE_C_STANDARD 99)

# Find required packages
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# If flex/bison not found automatically, specify paths
if(WIN32 AND NOT FLEX_FOUND)
    set(FLEX_EXECUTABLE "C:/tools/winflexbison/win_flex.exe")
    set(BISON_EXECUTABLE "C:/tools/winflexbison/win_bison.exe")
endif()

# Generate lexer
FLEX_TARGET(Lexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)

# Generate parser
BISON_TARGET(Parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)

# Ensure parser is built before lexer (lexer needs parser.tab.h)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

# Create executable
add_executable(compiler
        main.c
        ast.c
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Lexer_OUTPUTS}
)

target_include_directories(compiler PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}    # ast.h etc.
        ${CMAKE_CURRENT_BINARY_DIR}    # parser.tab.h
)

# Include directories
target_include_directories(compiler PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# For Phase 2 (when you add symbol table)
# add_executable(compiler
#     main.c
#     ast.c
#     symbol_table.c
#     ${BISON_Parser_OUTPUTS}
#     ${FLEX_Lexer_OUTPUTS}
# )
