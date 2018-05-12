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

MESSAGE(STATUS "Building ${PROJECT_NAME} ...")

FILE(GLOB HEADERS "OpenML.Shared/*.h")	
FILE(GLOB SOURCES "OpenML.Shared/*.cpp")
	
if(BUILD_SHARED_LIBS)
	if (WIN32)
		list(APPEND SOURCES "OpenML.Win32/dllmain.cpp")
	endif()

	add_library(${PROJECT_NAME} SHARED ${SOURCES})
else()
	add_library(${PROJECT_NAME} STATIC ${SOURCES})
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS ON)

# Enable C++11 long long for compilers that are capable of it
if(NOT ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} STRLESS 3.1 AND ";${CMAKE_CXX_COMPILE_FEATURES};" MATCHES ";cxx_long_long_type;")
	target_compile_features(${PROJECT_NAME} PUBLIC cxx_long_long_type)
endif()

if (WIN32)
	#target_compile_definitions(${PROJECT_NAME} PRIVATE WINDOWS=1 API_EXPORT=1)
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

MESSAGE(STATUS "COMPLETED !" )