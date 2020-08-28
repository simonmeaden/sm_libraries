add_executable(smwidgets_test
      src/main.cpp
      src/mainwindow.cpp
      src/mainwindow.h
   )

target_link_libraries(smwidgets_test sm_widgets Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Quick)
