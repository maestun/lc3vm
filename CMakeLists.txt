# 
cmake_minimum_required(VERSION 3.0.0)

# 
project(alis VERSION 0.1.0)

# SDL2 dependency
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Alis Virtual Machine: list of platform-independent files to compile
set(ALIS_VM_SRCS
    alis/depack/asm.c
    alis/addnames.c
    alis/alis.c
    alis/debug.c
    alis/escnames.c
    alis/main.c
    alis/opcodes.c
    alis/opernames.c
    alis/platform.c
    alis/script.c
    alis/storenames.c
    alis/utils.c
    alis/vram.c
    )

# Host Frontend: list of platform-dependent files to compile
set(ALIS_HOST_SRCS
    alis/sys/sdl2/sys_sdl2.c
    )

# Testing
# include(CTest)
# enable_testing()

# Produce executable
add_executable(alis 
               ${ALIS_VM_SRCS} 
               ${ALIS_HOST_SRCS}
               )

# SDL2 dependency
target_link_libraries(alis ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
