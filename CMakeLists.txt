cmake_minimum_required(VERSION 3.5)

project(QSBDGuiTest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()
add_subdirectory("../Big-Data-IC" ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS PrintSupport REQUIRED)
find_package(Qt5 COMPONENTS Svg REQUIRED)
find_package(Qt5 COMPONENTS QuickWidgets REQUIRED)
#find_package(Qt5 COMPONENTS Quick REQUIRED)

#find /usr/lib/x86_64-linux-gnu -name "*Config.cmake" |
#  sed 's/^.*\/Qt5//; s/Config.cmake$//; /^\s*$/d' |
#  sort | pr -t -3

if(ANDROID)
  add_library(QSBDGuiTest SHARED
    main.cpp
    src/mainwindow/mainwindow.cpp
    src/mainwindow/mainwindow.h
    src/view/view.h
    src/view/view.cpp
    src/model/model.h
    src/model/model.cpp
    src/controller/controller.h
    src/controller/controller.cpp
    src/qcustomplot/qcustomplot.h
    src/qcustomplot/qcustomplot.cpp
    src/csvdialog/csvdialog.h
    src/csvdialog/csvdialog.cpp
    src/sketchmenudialog/sketchmenudialog.h
    src/sketchmenudialog/sketchmenudialog.cpp
    src/kmedoids/kmedoids.hpp
    src/dbscan/dbscan.h
    src/dbscan/kdtree.h
    src/dbscan/kdtree.cpp
    src/kmeans/kmeans.h
  )

  add_library(qmlviewtest SHARED
    ../test/qmlviewtest.cpp
    ../src/qmlview/qmlview.h
    ../src/qmlview/qmlview.cpp
  )
else()
  add_executable(QSBDGuiTest
    main.cpp
    src/mainwindow/mainwindow.cpp
    src/mainwindow/mainwindow.h
    src/view/view.h
    src/view/view.cpp
    src/model/model.h
    src/model/model.cpp
    src/controller/controller.h
    src/controller/controller.cpp
    src/qcustomplot/qcustomplot.h
    src/qcustomplot/qcustomplot.cpp
    src/csvdialog/csvdialog.h
    src/csvdialog/csvdialog.cpp
    src/sketchmenudialog/sketchmenudialog.h
    src/sketchmenudialog/sketchmenudialog.cpp
    src/kmedoids/kmedoids.hpp
    src/dbscan/dbscan.h
    src/dbscan/kdtree.h
    src/dbscan/kdtree.cpp
    src/kmeans/kmeans.h
  )

  add_executable(qmlviewtest
    test/qmlviewtest.cpp
    src/qmlview/qmlview.h
    src/qmlview/qmlview.cpp
  )
endif()


target_include_directories(QSBDGuiTest PRIVATE src)
target_include_directories(QSBDGuiTest PRIVATE "../Big-Data-IC/src")
target_include_directories(QSBDGuiTest PRIVATE "../Big-Data-IC/thirdparty")
target_link_libraries(QSBDGuiTest PRIVATE Qt5::QuickWidgets Qt5::Widgets Qt5::PrintSupport Qt5::Svg nlohmann_json csv_parser pthread QSBD_STREAM_MAKER QSBD_QUANTILE_QUADTREE QSBD_GK_FACTORY QSBD_KLL_FACTORY QSBD_DCS_FACTORY QSBD_Q_DIGEST_FACTORY QSBD_UTILS)
#qt5_import_plugins(QSBDGuiTest INCLUDE Qt5::QSvgPlugin)

target_include_directories(qmlviewtest PRIVATE src)
target_include_directories(qmlviewtest PRIVATE "../Big-Data-IC/src")
target_include_directories(qmlviewtest PRIVATE "../Big-Data-IC/thirdparty")
target_link_libraries(qmlviewtest PRIVATE Qt5::QuickWidgets Qt5::Widgets Qt5::PrintSupport Qt5::Svg nlohmann_json csv_parser pthread QSBD_STREAM_MAKER QSBD_QUANTILE_QUADTREE QSBD_GK_FACTORY QSBD_KLL_FACTORY QSBD_DCS_FACTORY QSBD_Q_DIGEST_FACTORY QSBD_UTILS)

