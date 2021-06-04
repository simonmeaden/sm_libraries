if (CMAKE_BUILD_TYPE STREQUAL Release)
  find_package(Doxygen REQUIRED)

  if (DOXYGEN_FOUND)
    if (${QT_MAJOR_VERSION} STREQUAL "5")
      set(DOXYGEN_TAGFILES
        "/usr/share/doc/qt5/qtquick/qtquick.tags"
        "/usr/share/doc/qt5/qtxmlpatterns/qtxmlpatterns.tags"
        "/usr/share/doc/qt5/qtqmltest/qtqmltest.tags"
        "/usr/share/doc/qt5/qtwebsockets/qtwebsockets.tags"
        "/usr/share/doc/qt5/qtconcurrent/qtconcurrent.tags"
        "/usr/share/doc/qt5/qtscxml/qtscxml.tags"
        "/usr/share/doc/qt5/qtlocation/qtlocation.tags"
        "/usr/share/doc/qt5/qtwebchannel/qtwebchannel.tags"
        "/usr/share/doc/qt5/qtquick3d/qtquick3d.tags"
        "/usr/share/doc/qt5/qtxml/qtxml.tags"
        "/usr/share/doc/qt5/qtnfc/qtnfc.tags"
        "/usr/share/doc/qt5/qtbluetooth/qtbluetooth.tags"
        "/usr/share/doc/qt5/qtgui/qtgui.tags"
        "/usr/share/doc/qt5/qtprintsupport/qtprintsupport.tags"
        "/usr/share/doc/qt5/qtsvg/qtsvg.tags"
        "/usr/share/doc/qt5/qtwidgets/qtwidgets.tags"
        "/usr/share/doc/qt5/qtqmlmodels/qtqmlmodels.tags"
        "/usr/share/doc/qt5/qtlabscalendar/qtlabscalendar.tags"
        "/usr/share/doc/qt5/qtplatformheaders/qtplatformheaders.tags"
        "/usr/share/doc/qt5/qtopengl/qtopengl.tags"
        "/usr/share/doc/qt5/qtquickcontrols1/qtquickcontrols1.tags"
        "/usr/share/doc/qt5/qtspeech/qtspeech.tags"
        "/usr/share/doc/qt5/qtpositioning/qtpositioning.tags"
        "/usr/share/doc/qt5/qtsensors/qtsensors.tags"
        "/usr/share/doc/qt5/qtquickcontrols/qtquickcontrols.tags"
        "/usr/share/doc/qt5/qttestlib/qttestlib.tags"
        "/usr/share/doc/qt5/qtcore/qtcore.tags"
        "/usr/share/doc/qt5/qtserialbus/qtserialbus.tags"
        "/usr/share/doc/qt5/qtsql/qtsql.tags"
        "/usr/share/doc/qt5/qtremoteobjects/qtremoteobjects.tags"
        "/usr/share/doc/qt5/qtnetworkauth/qtnetworkauth.tags"
        "/usr/share/doc/qt5/qtwebengine/qtwebengine.tags"
        "/usr/share/doc/qt5/qt3d/qt3d.tags"
        "/usr/share/doc/qt5/qtnetwork/qtnetwork.tags"
        "/usr/share/doc/qt5/qtqml/qtqml.tags"
        "/usr/share/doc/qt5/qmake/qmake.tags"
        "/usr/share/doc/qt5/qtdbus/qtdbus.tags"
        "/usr/share/doc/qt5/qtqmlworkerscript/qtqmlworkerscript.tags"
        "/usr/share/doc/qt5/qtlabsplatform/qtlabsplatform.tags"
        "/usr/share/doc/qt5/qtgraphicaleffects/qtgraphicaleffects.tags"
        "/usr/share/doc/qt5/qtquicktimeline/qtquicktimeline.tags"
        )
    elseif (${QT_MAJOR_VERSION} STREQUAL "6")
      set(DOXYGEN_TAGFILES
        "/usr/share/doc/qt6/qtquick/qtquick.tags"
        "/usr/share/doc/qt6/qtqmltest/qtqmltest.tags"
        "/usr/share/doc/qt6/qtconcurrent/qtconcurrent.tags"
        "/usr/share/doc/qt6/qtscxml/qtscxml.tags"
        "/usr/share/doc/qt6/qtquick3d/qtquick3d.tags"
        "/usr/share/doc/qt6/qtxml/qtxml.tags"
        "/usr/share/doc/qt6/qtgui/qtgui.tags"
        "/usr/share/doc/qt6/qtprintsupport/qtprintsupport.tags"
        "/usr/share/doc/qt6/qtlottieanimation/qtlottieanimation.tags"
        "/usr/share/doc/qt6/qtsvg/qtsvg.tags"
        "/usr/share/doc/qt6/qtshadertools/qtshadertools.tags"
        "/usr/share/doc/qt6/qtwidgets/qtwidgets.tags"
        "/usr/share/doc/qt6/qtqmlmodels/qtqmlmodels.tags"
        "/usr/share/doc/qt6/qtopengl/qtopengl.tags"
        "/usr/share/doc/qt6/qtquickcontrols/qtquickcontrols.tags"
        "/usr/share/doc/qt6/qttestlib/qttestlib.tags"
        "/usr/share/doc/qt6/qtcore/qtcore.tags"
        "/usr/share/doc/qt6/qtsql/qtsql.tags"
        "/usr/share/doc/qt6/qtnetworkauth/qtnetworkauth.tags"
        "/usr/share/doc/qt6/qt3d/qt3d.tags"
        "/usr/share/doc/qt6/qtnetwork/qtnetwork.tags"
        "/usr/share/doc/qt6/qtqml/qtqml.tags"
        "/usr/share/doc/qt6/qmake/qmake.tags"
        "/usr/share/doc/qt6/qtdbus/qtdbus.tags"
        "/usr/share/doc/qt6/qtlabsplatform/qtlabsplatform.tags"
        "/usr/share/doc/qt6/qdoc/qdoc.tags"
        "/usr/share/doc/qt6/qtquicktimeline/qtquicktimeline.tags"
        )
    endif()

    set(DOXYGEN_WITH_APIDOC YES)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_QHP YES)
    set(DOXYGEN_GENERATE_XML NO)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_GENERATE_LATEX NO)

    set(DOXYGEN_SOURCE_BROWSER YES)
    set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/include)
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs)
    set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    set(DOXYGEN_PROJECT_NAME "SM Libraries")

    set(DOXYGEN_GENERATE_QHP YES)
    if (DOXYGEN_GENERATE_QHP EQUAL 1)
      set(DOXYGEN_QHP_NAMESPACE "uk.org.smelecomp.www")
      set(DOXYGEN_QHP_VIRTUAL_FOLDER  "smlibraries-0.1.0")
      set(DOXYGEN_QHG_LOCATION "/usr/bin/qhelpgenerator")
      set(DOXYGEN_QCH_FILE "SMLibraries.qch")
      set(DOXYGEN_QHG_LOCATION "/usr/bin/qhelpgenerator")
    endif()
    set(DOXYGEN_GENERATE_TAGFILE smlibraries.tags)

    set(DOXYGEN_EXCLUDE_PATTERNS
      */googletest-src/*   # This eliminates googletest from documentation
      */*autogen/*         # This eliminates moc generated files from documentation
      )
    set(DOXYGEN_PREDEFINED DOXYGEN_WORKING)
    set(DOXYGEN_ALIASES
      ${DOXYGEN_ALIASES}
      "accessor=\\par Access functions:^^"
      "prop=\\par Property:^^"
      "notifier=\\par Notifier signal:^^"
      "license=\\par License : ^^"
      #     "license{1}=\\par License : ^^"
      "reimplements=\\par Reimplements : ^^"
      "from=\\par From : "
      "notprop=\\par Notifier for "
      )

    # Set the Doxygen input and output directories in the Doxyfile
    #  configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    include(FindDoxygen)
    doxygen_add_docs(
      docs
      #    USE_STAMP_FILE
      ALL
      WORKING_DIRECTORY ${DOXYGEN_INPUT_DIR}
      COMMENT "Generate HTML/Qhp documentation"
      )

  endif()

endif()
