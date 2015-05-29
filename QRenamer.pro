#-------------------------------------------------
#
# Project created by QtCreator 2014-01-13T18:58:57
#
#-------------------------------------------------

QT       += concurrent core gui quickwidgets

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRenamer
TEMPLATE = app

win32{
RC_FILE = pics/QRenamer.rc
}

#Release:DESTDIR  = ../../Qt_apps
INCLUDEPATH += ui

SOURCES += main.cpp\
        ui/MainWindow.cpp \
    utility/stringUtility.cpp \
    workerThreads/renameFileThread.cpp \
    workerThreads/addDirThread.cpp \
    workerThreads/scanDirThread.cpp \
    model/fileNameModel.cpp \
    modelProxy/sortAndFilterFile.cpp \
    ui/filterDialog.cpp \
    ui/numberStep.cpp \
    utility/quickCloseSignal.cpp \
    model/fileModelItem.cpp

HEADERS  += ui/MainWindow.hpp \
    utility/stringUtility.hpp \
    workerThreads/renameFileThread.hpp \
    workerThreads/addDirThread.hpp \
    workerThreads/scanDirThread.hpp \
    model/fileNameModel.hpp \
    utility/initializer.hpp \
    modelProxy/sortAndFilterFile.hpp \
    ui/filterDialog.hpp \
    globalconst.hpp \
    ui/numberStep.hpp \
    utility/quickCloseSignal.hpp \
    model/fileModelItem.hpp

FORMS    += ui/MainWindow.ui \
    ui/filterDialog.ui \
    ui/numberstep.ui

RESOURCES += \
    pics.qrc \
    qml.qrc \
    js.qrc
