cmake_minimum_required (VERSION 3.8)

project (EmpireMake)

    SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
    SET (CMAKE_CXX_FLAGS                "-Wall")
    SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
    SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

include_directories("./src")

if (MSVC)
	include_directories("E:\\Soft\\packages\\Vcpkg.Nuget.1.5.0\\vcpkg_bin\\packages\\libpq_x86-windows\\include")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
	include_directories(UNIX "/usr/include/postgresql/")
	set(CMAKE_CXX_STANDARD 17)
endif()

file(GLOB hedgehogs "src/*.cpp" "./src/**/*.cpp" "./src/**/**/*.cpp" "src/*.h" "./src/**/*.h" "./src/**/**/*.h")
add_executable(${PROJECT_NAME} ${hedgehogs})