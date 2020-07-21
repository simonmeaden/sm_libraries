message("Output include dir" ${INCLUDE_OUTPUT_DIRECTORY})

set(APP_SOURCE_FILES
   simplecrypt.cpp
   mainwindow.cpp
   )
set(APP_HEADER_FILES
   simplecrypt.h
   mainwindow.h
   )

find_library(sm_widgets NAMES sm_widgets REQUIRED HINT ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(test_smwidgets
   ${APP_SOURCE_FILES} ${APP_HEADER_FILES}
   )

target_link_libraries(test_smwidgets Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Quick yaml-cpp sm_widgets)
target_include_directories(test_smwidgets PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${INCLUDE_OUTPUT_DIRECTORY}/.. # workspace/build/include
)

# creates an include/sm_widgets directory next to the lib/lib64 directory
add_custom_command(
   TARGET test_smwidgets
   PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${INCLUDE_OUTPUT_DIRECTORY})
# copies include files into the include directory
file(COPY ${HEADER_FILES}
    DESTINATION ${INCLUDE_OUTPUT_DIRECTORY}
)
