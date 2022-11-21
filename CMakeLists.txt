cmake_minimum_required(VERSION 3.12)
project(SourceTil CXX)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_LINK_FLAGS "-coverage -lgcov")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -fPIC -O0")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")


include(GNUInstallDirs)
include_directories(include)

# Common sources
add_library(${PROJECT_NAME}_objs OBJECT
	src/calculation.cpp
	include/calculation.hpp
	include/component.h
	include/logacceptor.h
	include/logsender.h
	include/logwriter.h
	include/serializer.h
)

# The Service
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs )

# Tests include sector
include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG release-1.12.1
)
# For Win: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Unit Tests
add_subdirectory(test)

if(DEFINED ENV{PREFIX})
	message(STATUS "Set install prefix: $ENV{PREFIX}")
	file(TO_CMAKE_PATH "$ENV{PREFIX}" PREFIX_PATH)
	set(CMAKE_INSTALL_PREFIX ${PREFIX_PATH})
endif()


install(
	TARGETS ${PROJECT_NAME}
	DESTINATION ${CMAKE_INSTALL_BINDIR} 
	COMPONENT ${PROJECT_NAME}
)

install(
	FILES ${CONFIGS_FILES} 
	DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/${PROJECT_NAME} 
	COMPONENT ${PROJECT_NAME}
)
