PROJECT (RenderMan)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkRendering vtkHybrid)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)
include(${WikiExamples_SOURCE_DIR}/CMake/RequiresVersion.cmake)

set(VERSION_MIN "6.0")
Requires_Version(PolyDataRIB ${VERSION_MIN} ALL_FILES)

foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

# Testing
SET(KIT RenderMan)
INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
