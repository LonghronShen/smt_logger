cmake_minimum_required(VERSION 3.0.0)

# use local repository if defined
if (DEFINED ENV{LOCAL_REPOSITORY})
  set(CMAKE_PREFIX_PATH $ENV{LOCAL_REPOSITORY})
endif()

# use toolchain if possible
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

set(project_name "smt-logger")
project(${project_name}-project C CXX)

if(WIN32 OR WIN64)
    add_compile_definitions("WIN32_LEAN_AND_MEAN" "_CRT_SECURE_NO_WARNINGS" "NOMINMAX")
    if(MSVC)
        add_compile_options("/source-charset:utf-8" "/EHsc" "/Zc:threadSafeInit-")

        if(NOT CMAKE_BUILD_TYPE)
            add_compile_options("/MT")
        else()
            add_compile_options("/MTd")
        endif()

        set(CompilerFlags
            CMAKE_CXX_FLAGS
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL
            CMAKE_CXX_FLAGS_RELWITHDEBINFO
            CMAKE_C_FLAGS
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL
            CMAKE_C_FLAGS_RELWITHDEBINFO)
        foreach(CompilerFlag ${CompilerFlags})
            string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
            set(${CompilerFlag} "${${CompilerFlag}}" CACHE STRING "msvc compiler flags" FORCE)
            message("MSVC flags: ${CompilerFlag}:${${CompilerFlag}}")
        endforeach()
    endif()
else()
    if(UNIX)
        if(APPLE)
            add_compile_options("-m64" "-fPIC" "-march=native")
            set(CMAKE_MACOSX_RPATH 1 CACHE STRING "CMAKE_MACOSX_RPATH" FORCE)
        else()
            add_compile_options("-fPIC" )
            if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
                add_compile_options("-m64" "-march=westmere")
            endif()
        endif()
    endif()
endif()

include(external/InitializeExternalComponents.cmake)

add_subdirectory(source)
add_subdirectory(example)
add_subdirectory(tests)
