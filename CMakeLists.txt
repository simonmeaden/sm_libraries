cmake_minimum_required(VERSION 3.5)
cmake_policy(VERSION 3.5)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0076 NEW)
#cmake_policy(SET CMP0079 NEW)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_INSTALL_PREFIX)
   set(CMAKE_INSTALL_PREFIX /usr/local)
endif()

# The project version number.
set(SMWIDGETS_VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(SMWIDGETS_VERSION_MINOR   1   CACHE STRING "Project minor version number.")
set(SMWIDGETS_VERSION_PATCH   0   CACHE STRING "Project patch version number.")
set(SMWIDGETS_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
mark_as_advanced(SMWIDGETS_VERSION_MAJOR SMWIDGETS_VERSION_MINOR SMWIDGETS_VERSION_PATCH SMWIDGETS_VERSION)

project(SMLibraries
        VERSION     0.1.0
        DESCRIPTION "Various of my widgets and non-widget stuff."
        LANGUAGES   CXX C
        )

set(CMAKE_DEBUG_POSTFIX d)

#set(WIDGET_HEADER_FILES
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/exspinbox.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/hexformatdelegate.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/abstractlabelledwidget.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/abstractlabelledspinbox.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/labelledspinbox.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/labelledexspinbox.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/labelleddoublespinbox.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/labelledcombobox.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/labelledlineedit.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/labelledtextfield.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/labelledwidgets.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/extabwidget.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/sm_widgets_global.h
#   )
set(EXTRA_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/ExTabWidget
   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/ExSpinBox
   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/LabelledComboBox
   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/LabelledDoubleSpinBox
   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/LabelledExSpinBox
   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/LabelledSpinBox
   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/LabelledLineEdit
   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/LabelledTextField
)
#set(WIDGET_HEADER_FILES_P
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/private/extabwidget_p.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/private/clockwidget.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/private/loginwidget.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/sm_widgets/private/simplecrypt.h
#)
#set(WIDGET_SOURCE_FILES
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/exspinbox.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/extabwidget.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/hexformatdelegate.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/abstractlabelledwidget.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/abstractlabelledspinbox.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/labelledspinbox.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/labelledexspinbox.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/labelleddoublespinbox.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/labelledcombobox.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/labelledlineedit.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/labelledtextfield.cpp
#   )
#set(WIDGET_SOURCE_FILES_P
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/private/extabwidget_p.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/private/clockwidget.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/private/loginwidget.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/private/simplecrypt.cpp
#)

# required libraries
# Make certain the project is set BEFORE find_package
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#==== Qt 5 core gui and widgets ==================================
include("CMakeLists.qt5.in")
#==== DOxygen ====================================================
include("CMakeLists.doxy.in")
#====GoogleTest ==================================================
#include("CMakeLists.gtest.in")
#==== end of standard includes====================================

set(MIN_YAMLCPP_VERSION 0.6.0)
find_package(yaml-cpp ${MIN_YAMLCPP_VERSION} REQUIRED CONFIG)
set(MIN_QYAMLCPP_VERSION 0.1.0)
find_package(qyamlcpp ${MIN_QYAMLCPP_VERSION} REQUIRED CONFIG)

add_library(sm_widgets STATIC "")
target_sources(sm_widgets
   PUBLIC

      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/sm_widgets_global.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/abstractlabelledwidget.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/exspinbox.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/hexformatdelegate.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/labelledspinbox.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/labelledexspinbox.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/labelleddoublespinbox.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/labelledcombobox.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/labelledlineedit.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/labelledtextfield.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/labelledwidgets.h>
#      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/loginwidget.h>
#      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/extabwidget.h>
#      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/simplecrypt.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/extendedcolordialog.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/x11colors.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/CircularBuffer.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/sm_widgets/circularbuffer.h>

      $<INSTALL_INTERFACE:include/sm_widgets/sm_widgets_global.h>
      $<INSTALL_INTERFACE:include/sm_widgets/abstractlabelledwidget.h>
      $<INSTALL_INTERFACE:include/sm_widgets/exspinbox.h>
      $<INSTALL_INTERFACE:include/sm_widgets/hexformatdelegate.h>
      $<INSTALL_INTERFACE:include/sm_widgets/labelledspinbox.h>
      $<INSTALL_INTERFACE:include/sm_widgets/labelledexspinbox.h>
      $<INSTALL_INTERFACE:include/sm_widgets/labelleddoublespinbox.h>
      $<INSTALL_INTERFACE:include/sm_widgets/labelledcombobox.h>
      $<INSTALL_INTERFACE:include/sm_widgets/labelledlineedit.h>
      $<INSTALL_INTERFACE:include/sm_widgets/labelledtextfield.h>
      $<INSTALL_INTERFACE:include/sm_widgets/labelledwidgets.h>
#      $<INSTALL_INTERFACE:include/sm_widgets/loginwidget.h>
#      $<INSTALL_INTERFACE:include/sm_widgets/extabwidget.h>
      $<INSTALL_INTERFACE:include/sm_widgets/extendedcolordialog.h>
      $<INSTALL_INTERFACE:include/sm_widgets/x11colors.h>
      $<INSTALL_INTERFACE:include/sm_widgets/CircularBuffer.h>
      $<INSTALL_INTERFACE:include/sm_widgets/circularbuffer.h>

   PRIVATE
      src/abstractlabelledwidget.cpp
#      src/clockwidget.h
#      src/clockwidget.cpp
#      src/messagewidget.h
#      src/messagewidget.cpp
#      src/loginwidget.cpp
#      src/simplecrypt.cpp
      src/exspinbox.cpp
#      src/extabwidget.cpp
#      src/extabwidget_p.cpp
      src/hexformatdelegate.cpp
      src/labelledcombobox.cpp
      src/labelleddoublespinbox.cpp
      src/labelledexspinbox.cpp
      src/labelledlineedit.cpp
      src/labelledspinbox.cpp
      src/labelledtextfield.cpp
      src/extendedcolordialog.cpp

   )

target_include_directories(sm_widgets
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(sm_widgets Qt5::Core Qt5::Gui Qt5::Widgets)
#target_link_libraries(test_sm_widgets yaml-cpp qyamlcpp sm_widgets)

# Install target
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/sm_widgets)


install(TARGETS sm_widgets
    EXPORT sm_widgets-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/sm_widgets DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT sm_widgets-targets
    FILE
        sm_widgetsTargets.cmake
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)

message("Install directory : " ${INSTALL_CONFIGDIR})

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/sm_widgetsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
   ${CMAKE_CURRENT_LIST_DIR}/cmake/sm_widgetsConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/sm_widgetsConfig.cmake
   INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, config version and custom find modules
install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/cmake/FindSMWidgetsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/sm_widgetsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/sm_widgetsConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

