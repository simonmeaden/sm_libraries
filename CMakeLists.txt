cmake_minimum_required(VERSION 2.8.2)
cmake_policy(VERSION 2.8.2)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0054 NEW)
#cmake_policy(SET CMP0079 NEW)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_INSTALL_PREFIX)
   set(CMAKE_INSTALL_PREFIX /usr/local)
endif()

project(SMLibraries
        VERSION     0.1.0
        DESCRIPTION "Various of my widgets and non-widget stuff."
        LANGUAGES   CXX C
        )

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
   ${CMAKE_BINARY_DIR}/../../../${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
   ${CMAKE_BINARY_DIR}/../../../${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
   ${CMAKE_BINARY_DIR}/../../../${CMAKE_INSTALL_BINDIR})
set(INCLUDE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../include/sm_libraries)
set(INCLUDE_OUTPUT_DIRECTORY_P ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../include/sm_libraries/private)

# Make certain the project is set BEFORE find_package
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#==== Qt 5 core gui and widgets ==================================
include("CMakeLists.qt5.in")   # Qt5
include("CMakeLists.doxy.in")  # DOxygen
include("CMakeLists.gtest.in") # GoogleTests
#==== end of standard includes====================================

set(CMAKE_DEBUG_POSTFIX d)

# The project version number.
set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   1   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

set(WIDGET_HEADER_FILES
   exspinbox.h
   hexformatdelegate.h
   abstractlabelledwidget.h
   abstractlabelledspinbox.h
   labelledspinbox.h
   labelledexspinbox.h
   labelleddoublespinbox.h
   labelledcombobox.h
   labelledlineedit.h
   labelledtextfield.h
   labelledwidgets.h
   abstractlogindialog.h
   extabwidget.h
   sm_widgets_global.h
   collection.h comment.h emitter.h node.h parse.h qyamlcpp.h
   )
set(EXTRA_FILES QYamlCpp)
set(WIDGET_HEADER_FILES_P
   private/extabwidget_p.h
)
set(WIDGET_SOURCE_FILES_P
   private/extabwidget_p.cpp
)
set(WIDGET_SOURCE_FILES
   exspinbox.cpp
   extabwidget.cpp
   hexformatdelegate.cpp
   abstractlabelledwidget.cpp
   abstractlabelledspinbox.cpp
   labelledspinbox.cpp
   labelledexspinbox.cpp
   labelleddoublespinbox.cpp
   labelledcombobox.cpp
   labelledlineedit.cpp
   labelledtextfield.cpp
   )

set(CORE_HEADER_FILES
   sm_widgets_global.h
   )
set(CORE_HEADER_FILES_P
   )
set(CORE_SOURCE_FILES
   )
set(HEADER_ONLY_FILES
   private/circularbuffer.h
   CircularBuffer.h
   )

add_custom_target(sm_widgets_p SOURCES private/circularbuffer.h)
add_library(sm_widgets STATIC
   "${WIDGET_HEADER_FILES};${WIDGET_HEADER_FILES_P};${WIDGET_SOURCE_FILES};${WIDGET_SOURCE_FILES_P};${HEADER_ONLY_FILES}"
   )
#add_library(sm_core STATIC
#   "${CORE_HEADER_FILES}"#;${CORE_HEADER_FILES_P};${CORE_SOURCE_FILES};${CORE_SOURCE_FILES_P}"
#   )

# This sets up the '*_global.h' library define
target_compile_definitions(sm_widgets PRIVATE SM_WIDGETS_LIBRARY)
#target_compile_definitions(sm_core PRIVATE SM_CORE_LIBRARY)


set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set_target_properties(sm_widgets
  PROPERTIES
    CXX_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE 1
  )
#set_target_properties(sm_core
#   PROPERTIES
#     CXX_EXTENSIONS OFF
#     POSITION_INDEPENDENT_CODE 1
#   )

# required libraries
find_library(yamlcpp NAMES yaml-cpp REQUIRED)
#find_library(qyamlcpp MAMES qyamlcpp REQUIRED HINT ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
#find_library(sm_widgets MAMES sm_widgets HINT ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

#target_link_libraries(sm_core Qt5::Core Qt5::Gui)
#target_include_directories(sm_core PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}
#)

target_link_libraries(sm_widgets Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Quick yaml-cpp)# qyamlcpp)
target_link_libraries(sm_widgets)
target_include_directories(sm_widgets PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${INCLUDE_OUTPUT_DIRECTORY}/.. # workspace/build/include
)

# creates an include/sm_widgets directory next to the lib/lib64 directory
add_custom_command(
   TARGET sm_widgets
   PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${INCLUDE_OUTPUT_DIRECTORY})
# copies include files into the include directory
#file(REMOVE ${WIDGET_HEADER_FILES} ${HEADER_ONLY_FILES} ${EXTRA_FILES}
#    DESTINATION ${INCLUDE_OUTPUT_DIRECTORY}
#)
file(COPY ${WIDGET_HEADER_FILES} ${HEADER_ONLY_FILES} ${EXTRA_FILES}
    DESTINATION ${INCLUDE_OUTPUT_DIRECTORY}
)

#set(DOXYGEN_EXCLUDE_PATTERNS
#   ${DOXYGEN_EXCLUDE_PATTERNS}
#   */circular_buffer.h   # This eliminates circular_buffer from documentation
#)
#message("BLOCKED : " ${DOXYGEN_EXCLUDE_PATTERNS})


add_subdirectory(tests)
add_subdirectory(examples)
