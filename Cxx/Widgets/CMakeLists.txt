PROJECT (Widgets)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 6.0)
  SET(KIT_LIBS vtkHybrid vtkWidgets)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)
foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

# Testing
SET(KIT Widgets)

SET(NEEDS_ARGS
  CheckerboardWidget
  OrientationMarkerWidget
  Slicer2D
  RectilinearWipeWidget
)
INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)
ADD_TEST(${KIT}-OrientationMarkerWidget ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestOrientationMarkerWidget ${DATA}/Bunny.vtp)

ADD_TEST(${KIT}-RectilinearWipeWidget ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestRectilinearWipeWidget ${DATA}/Gourds2.jpg ${DATA}/Ox.jpg)

ADD_TEST(${KIT}-CheckerboardWidget ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestCheckerboardWidget ${DATA}/Gourds2.jpg ${DATA}/Ox.jpg)

ADD_TEST(${KIT}-Slider2D ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestSlider2D -E 25)
