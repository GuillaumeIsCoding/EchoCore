cmake_minimum_required(VERSION 3.25)

project(EchoCore
    VERSION 0.0.1
    HOMEPAGE_URL "https://github.com/GuillaumeIsCoding/Echo"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)              # right now with c++ 23
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ================================================================================================
# CMake Settings
# ================================================================================================

if(NOT CMAKE_CONFIGURATION_TYPES)
    # Single-config generator (Make, Ninja)
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
    endif()
else()
    # Multi-config generator (Visual Studio, Xcode)
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release)
    endif()
    
    # Set the default configuration for Visual Studio
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set(CMAKE_VS_STARTUP_PROJECT ${PROJECT_NAME})
    
    # You can also set this to make Release the default in Visual Studio IDE
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

# ================================================================================================
# Options
# ================================================================================================

option(ECHO_BUILD_TESTS "Build tests" ON)
option(ECHO_BUILD_EXAMPLES "Build examples" OFF)
option(ECHO_INSTALL "Generate install target" ON)

# ================================================================================================
# Dependencies
# ================================================================================================

include(FetchContent)

find_package(fmt QUIET)

if (fmt_FOUND)
    message(STATUS "Packaged version of fmt will be used.")
else()
    message(STATUS "Bundled version of fmt will be downloaded and used.")

    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 12.0.0
    )

    FetchContent_MakeAvailable(fmt)
endif()

find_package(spdlog QUIET)

if (spdlog_FOUND)
    message(STATUS "Packaged version of spdlog will be used.")
else()
    message(STATUS "Bundled version of spdlog will be downloaded and used.")

    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.16.0
    )

    FetchContent_MakeAvailable(spdlog)
endif()
    
# ================================================================================================
# Target Configuration
# ================================================================================================

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(EXAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)

file (GLOB_RECURSE SOURCES
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/*.c"
    "${SOURCE_DIR}/*.cc"
)

file (GLOB_RECURSE HEADERS
    "${SOURCE_DIR}/*.hpp"
    "${SOURCE_DIR}/*.h"
)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
add_library(Echo::Core ALIAS ${PROJECT_NAME})

# ================================================================================================
# Target Properties
# ================================================================================================

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src    
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        fmt::fmt
        spdlog::spdlog
)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp")
    target_precompile_headers(${PROJECT_NAME} PUBLIC include/pch.hpp)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME "EchoCore"
    EXPORT_NAME "Core"
    DEBUG_POSTFIX "d"
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

if(MSVC)
    # Ensure Visual Studio IntelliSense uses C++23
    target_compile_options(${PROJECT_NAME} PRIVATE /std:c++latest)
    
    # For IntelliSense to recognize it in the IDE
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC
    target_compile_options(${PROJECT_NAME} PRIVATE -std=c++23)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Clang
    target_compile_options(${PROJECT_NAME} PRIVATE -std=c++2b)
endif()

# ================================================================================================
# Compiler Settings
# ================================================================================================

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        $<$<CONFIG:Debug>:ECHO__DEBUG>
        $<$<CONFIG:Release>:ECHO__RELEASE>
        ECHO_CORE_BUILDING_SHARED
    INTERFACE
        ECHO_CORE_LINKING_SHARED
)

# ================================================================================================
# Tests
# ================================================================================================

if(ECHO_BUILD_TESTS)
    # include(CTest)
    # enable_testing()
    
    # # Trouver ou télécharger EchoTest
    # find_package(Catch2 3 QUIET)
    
    # if (Catch2_FOUND)
    #     message(STATUS "Packaged version of Catch2 will be used.")
    # else()
    #     message(STATUS "Bundled version of Catch2 will be downloaded and used.")
        
    #     FetchContent_Declare(
    #         Catch2
    #         GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    #         GIT_TAG v3.10.0
    #     )
        
    #     FetchContent_MakeAvailable(Catch2)
        
    #     # Ajouter le module pour discover tests
    #     list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    # endif()
    
    # include(Catch)

    # find_package(FakeIt QUIET)

    # if (FakeIt_FOUND)
    #     message(STATUS "Packaged version of FakeIt will be used.")
    # else()
    #     message(STATUS "Bundled version of FakeIt will be downloaded and used.")

    #     FetchContent_Declare(
    #         FakeIt
    #         GIT_REPOSITORY https://github.com/eranpeer/FakeIt.git
    #         GIT_TAG 2.4.1
    #     )
        
    #     FetchContent_MakeAvailable(FakeIt)
    # endif()
    
    # # Collecter tous les fichiers de test
    # file(GLOB_RECURSE TEST_SOURCES "${TEST_DIR}/*.cpp")
    
    # if(TEST_SOURCES)
    #     add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
        
    #     target_link_libraries(${PROJECT_NAME}_tests
    #         PRIVATE
    #             Echo::Core
    #             Catch2::Catch2WithMain
    #             FakeIt::FakeIt-catch
    #     )
        
    #     target_include_directories(${PROJECT_NAME}_tests
    #         PRIVATE
    #             ${CMAKE_CURRENT_SOURCE_DIR}/include
    #     )
        
    #     # Découvrir automatiquement les tests Catch2
    #     catch_discover_tests(${PROJECT_NAME}_tests)
        
    #     message(STATUS "Tests enabled: ${PROJECT_NAME}_tests")
    # else()
    #     message(WARNING "No test files found in ${TEST_DIR}")
    # endif()
endif()

# ================================================================================================
# Examples
# ================================================================================================

if(ECHO_BUILD_EXAMPLES)
    if(EXISTS "${EXAMPLE_DIR}")
        file(GLOB EXAMPLE_SOURCES "${EXAMPLE_DIR}/*.cpp")
        
        foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
            get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
            add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
            
            target_link_libraries(${EXAMPLE_NAME}
                PRIVATE
                    Echo::Core
            )
            
            message(STATUS "Example added: ${EXAMPLE_NAME}")
        endforeach()
    endif()
endif()

# ================================================================================================
# Documentation
# ================================================================================================

# TODO: Ajouter la génération de documentation avec Doxygen

# ================================================================================================
# Install
# ================================================================================================

if (ECHO_INSTALL)
    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)
    
    set(TARGETS_TO_INSTALL ${PROJECT_NAME})

    set(DEPS_TO_INSTALL "")
    set(DEPS_PUBLIC_HEADER "")

    if (NOT fmt_FOUND)
        list(APPEND DEPS_TO_INSTALL fmt)
        list(APPEND DEPS_PUBLIC_HEADER "include/fmt")
    endif()
    if (NOT spdlog_FOUND)
        list(APPEND DEPS_TO_INSTALL spdlog)
    endif()

    install(TARGETS ${TARGETS_TO_INSTALL} ${DEPS_TO_INSTALL}
        EXPORT EchoCoreTarget
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        PUBLIC_HEADER DESTINATION ${DEPS_PUBLIC_HEADER}
    )

    install(DIRECTORY ${INCLUDE_DIR}/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
    )

    install(EXPORT EchoCoreTarget
        FILE EchoCoreTarget.cmake
        NAMESPACE Echo::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/EchoCore
    )

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/EchoConfigConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion 
    )

    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/EchoCoreConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/EchoCoreConfig.cmake"
        @ONLY
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/EchoCoreConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/EchoCoreConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/EchoCore
    )

endif()
