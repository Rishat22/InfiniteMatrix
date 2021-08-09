cmake_minimum_required(VERSION 3.5)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    project(InfiniteMatrix VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project(InfiniteMatrix)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(project_sources
    main.cpp
    matrix.h
    )

add_executable(InfiniteMatrix ${project_sources} )

target_include_directories(InfiniteMatrix
    PUBLIC "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(InfiniteMatrix PRIVATE
        /W4
    )
else ()
    target_compile_options(InfiniteMatrix PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS InfiniteMatrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
