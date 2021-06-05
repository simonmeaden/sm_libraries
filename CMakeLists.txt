cmake_minimum_required(VERSION 3.5)

project(SMLibraries
        VERSION     0.1.0
        DESCRIPTION "Various of my widgets and non-widget stuff."
        LANGUAGES   CXX C
)

set(MIN_YAMLCPP_VERSION 0.6.0)
find_package(yaml-cpp REQUIRED)

if (${QT_MAJOR_VERSION} STREQUAL "5")
  find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets REQUIRED)
elseif (${QT_MAJOR_VERSION} STREQUAL "6")
  find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets REQUIRED)
endif()

set(SMWIDGETS_EXTRAS
  include/sm_widgets/labelledwidgets.h
  include/sm_widgets/LabelledComboBox
  include/sm_widgets/LabelledDoubleSpinBox
  include/sm_widgets/LabelledExSpinBox
  include/sm_widgets/LabelledLineEdit
  include/sm_widgets/LabelledSpinBox
  include/sm_widgets/LabelledTextField
  )
set(QYAMLCPP_EXTRAS
  include/qyamlcpp/QYamlCpp
  )

add_library(smlibraries STATIC
    src/abstractlabelledspinbox.cpp
    src/abstractlabelledwidget.cpp
    src/exspinbox.cpp
    src/extendedcolordialog.cpp
    src/hexformatdelegate.cpp
    src/labelledcombobox.cpp
    src/labelleddoublespinbox.cpp
    src/labelledexspinbox.cpp
    src/labelledlineedit.cpp
    src/labelledspinbox.cpp
    src/labelledtextfield.cpp
    src/sm_widgets_global.h
    src/x11colors.cpp
  )

add_library(SMLibraries::smlibraries ALIAS smlibraries)

target_include_directories(smlibraries
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Handle library documentation using OOxygen and helpgenerator.
add_subdirectory("docs")

add_subdirectory("examples")

target_compile_options(smlibraries PRIVATE -Werror)

target_compile_features(smlibraries PRIVATE cxx_std_17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

target_link_libraries(smlibraries
  PUBLIC
    Qt::Core Qt::Gui Qt::Widgets
    yaml-cpp
)

include(GNUInstallDirs)

install(TARGETS smlibraries
    EXPORT smlibraries-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
#This is required so that the exported target has the name SMLibraries and not smlibraries
set_target_properties(smlibraries PROPERTIES EXPORT_NAME SMLibraries)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT smlibraries-targets
  FILE
    SMLibrariesTargets.cmake
  NAMESPACE
    SMLibraries::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/smlibraries
)

#Create a ConfigVersion.cmake file
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/SMLibraries)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/SMLibrariesConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/SMLibrariesConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/SMLibrariesConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/SMLibrariesConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/SMLibrariesConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
export(EXPORT smlibraries-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/SMLibrariesTargets.cmake
    NAMESPACE SMLibraries::)

# install additional files
set(INSTALL_INCLUDE_DIR "include")
install(FILES ${SMWIDGETS_EXTRAS}
  DESTINATION ${INSTALL_INCLUDE_DIR}/sm_widgets
  CONFIGURATIONS Release
  )
install(FILES ${QYAMLCPP_EXTRAS}
  DESTINATION ${INSTALL_INCLUDE_DIR}/qyamlcpp
  CONFIGURATIONS Release
  )

#Register package in the User Package Registry
export(PACKAGE SMLibraries)



