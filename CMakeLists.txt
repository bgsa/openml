cmake_minimum_required(VERSION 3.0)

include (GenerateExportHeader)

PROJECT(OpenML)

SET(MAJOR_VERSION 1)
SET(MINOR_VERSION 0)
SET(PROJECT_VERSION ${MAJOR_VERSION}.${MINOR_VERSION})

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

message(STATUS "Building ${PROJECT_NAME} ...")

find_package(OpenCL   REQUIRED)
#find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)
#set(MOC_HEADERS	${CMAKE_SOURCE_DIR}/OpenML.Shared/)
#qt5_wrap_cpp(moc_sources ${CMAKE_SOURCE_DIR})

set(APOLLO_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../apollo/src)
include_directories(${APOLLO_INCLUDE_DIR})

set(APOLLO_LIB_DIR ${CMAKE_SOURCE_DIR}/../apollo/x64/Release)
link_directories(${APOLLO_LIB_DIR})

file(GLOB HEADERS "OpenML.Shared/*.h")	
file(GLOB SOURCES "OpenML.Shared/*.cpp")

if (WIN32)
    add_definitions(-DDEBUG -DAPI_EXPORT -DMAJOR_COLUMN_ORDER -DOPENGL -D_CRT_SECURE_NO_WARNINGS -DWINDOWS)
endif()
if (UNIX OR LINUX)
    add_definitions(-DDEBUG -DAPI_EXPORT -DMAJOR_COLUMN_ORDER -DOPENGL -D_CRT_SECURE_NO_WARNINGS -DUNIX)
endif()

if(BUILD_SHARED_LIBS)
	if (WIN32)
		list(APPEND SOURCES "OpenML.Win32/dllmain.cpp")
	endif()

	add_library(${PROJECT_NAME} SHARED ${SOURCES})
else()
	add_library(${PROJECT_NAME} STATIC ${SOURCES})
endif()

# Enable C++11 long long for compilers that are capable of it
if(NOT ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} STRLESS 3.1 AND ";${CMAKE_CXX_COMPILE_FEATURES};" MATCHES ";cxx_long_long_type;")
	target_compile_features(${PROJECT_NAME} PUBLIC cxx_long_long_type)
endif()

if (WIN32)
	target_compile_definitions(${PROJECT_NAME} PRIVATE WINDOWS=1)
endif()

if ( (NOT ${MAJOR_COLUMN_ORDER}) AND (NOT ${MAJOR_ROW_ORDER}))
	target_compile_definitions(${PROJECT_NAME} PRIVATE MAJOR_COLUMN_ORDER=1)
else()
	if ( ${MAJOR_COLUMN_ORDER} )
		target_compile_definitions(${PROJECT_NAME} PRIVATE MAJOR_COLUMN_ORDER=1)
	else()
		target_compile_definitions(${PROJECT_NAME} PRIVATE MAJOR_ROW_ORDER=1)
	endif()
endif()	

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS ON)

#target_link_libraries(${PROJECT_NAME} apollo.lib Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} apollo.lib)

MESSAGE(STATUS "START COMPLETED!" )