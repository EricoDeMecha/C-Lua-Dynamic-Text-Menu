cmake_minimum_required(VERSION 3.25)
project(MProject)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_C_STANDARD 17)

add_executable(test
        utils.h
        utils.c
        mainDS.c
        stack/stack.c
        stack/stack.h
        pair/pair.c
        pair/pair.h
        minimumStack/minstack.h
        minimumStack/minstack.c
        )

set_target_properties(test PROPERTIES LINKER_LANGUAGE C)

# menuTree project
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

# works with conan version 1.59.0
conan_cmake_configure(REQUIRES
        sqlite3/3.40.0
        lua/5.4.4
        GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})

add_executable(menuTree
        menuTree/menuTree.h
        menuTree/menuTree.c mainMenuTree.c)
set_target_properties(menuTree PROPERTIES LINKER_LANGUAGE C)

find_package(SQLite3 REQUIRED)
if(SQLite3_FOUND)
    message("sqliteFound")
    include_directories(${SQLite3_INCLUDE_DIRS})
    target_link_libraries(menuTree PRIVATE ${SQLite3_LIBRARIES})
endif ()

find_package(lua REQUIRED)
if(lua_FOUND)
    message("Lua 51 Found")
    include_directories(${lua_INCLUDE_DIRS})
    target_link_libraries(menuTree PRIVATE ${lua_LIBRARIES})
endif()



